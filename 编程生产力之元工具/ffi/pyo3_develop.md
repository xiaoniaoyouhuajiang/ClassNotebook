# pyo3_develop

该文档是围绕Pyo3库的架构进行编写的，编写的主要动机为：

* 学习ffi/binding相关的技术
* 争取PR



## Architecture

参考链接：https://github.com/PyO3/pyo3/blob/main/Architecture.md

原理上，PyO3同样基于Python的CAPI工作。目前，PyO3由六个部分组成：

* low-level的C-API binding
  * pyo3-ffi模块和src/ffi
* 对Python对象的Binding
  * src/instance.rs和src/types
* PyClass以及相关功能
  * src/pycell和src/pyclass.rs
* 用以简化使用过程的过程宏定义
  * src/impl_, pyo3-macros, pyo3-macros-backend
* build.rs和pyo3-build-config



### C-API封装

pyo3-ffi包含了对C-API的封装，事实上，有自动生成对CAPI的封装工具（比如py-spy中介绍的），单pyo3项目是手动完成该工作的，因为：

* 能够更好地控制如何将 C 语言规范适配到 Rust 中
* 更好地支持多个Python版本（仅通过以个文件集合）

ffi设计的哲学是：堆cpython/Include文件结构尽可能简单地进行包装

目前，项目组通过issue1289来追踪适配最新版本的Python（3.13）进度

条件编译选项如`#define Py_LIMITED_API`在代码中通过`#[cfg(Py_LIMITED_API)]`这样的方式来表达



#### Py_LIMITED_API/abi3

一般情况下，Python的扩展是不能“跨版本”使用的，比如基于Pyhon3.5的C-API的扩展不能被python3.8使用，但在[PEP384](https://peps.python.org/pep-0384/)中，提出了一种稳定的ABI方案。下面就来挖一挖这个提升方案的内容。



> abi为什么不兼容

abi不兼容的最主要原因自然是C对象内存结构布局的变化



> 解决方法

限制扩展模块可以使用的C API，这些API是人工挑选的稳定的API以及数据结构。扩展模块通过#define Py_LIMITED_API可以确保codebase中只有稳定的API，比如Numpy1.20版本开始支持稳定的API，从而提高二进制分发的兼容性。



#### 代码实例

下面来看一个例子把

首先，我们看几种常见的rust代码模型：

> ```rust
> unsafe extern "C" {
>     #[cfg(all(Py_3_9, not(PyPy)))]
>     pub fn PyInterpreterState_Get() -> *mut PyInterpreterState;
>     ...
> }
> ```

extern "C"允许我们与动态链接库中的C函数进行交互,比如：

```rust
use std::os::raw::c_int;

#[no_mangle]
pub extern "C" fn add(a: c_int, b: c_int) -> c_int {
    a + b
}
```

编译成so后就能够被C/Python调用



那么，rust到底如何与CPython的代码交互呢？

首先我们回顾一下CPython项目的目录结构中的Include:

* Include
  * cpython ：私有API，它们中的可能是一些备选项
  * internal:
  * 其他文件，比如object.h：这些是python的公共API，你可以在Python的文档中找到它们，它们中的基本都是stable的，而不稳定的API就放在cpython下面了

我们看到pyo3-ffi/src下的lib.rs

```rust
...
// "Limited API" definitions matching Python's `include/cpython` directory.
#[cfg(not(Py_LIMITED_API))]
mod cpython;
```

注意到，当不使用Limited API这个条件进行编译，你才能够将mod cpython中的内容包含进来



假如我们正使用Python进行超大整数的运算，我们可以在CPython的源码中找到背后的算法，它一定要通过某个C-API的调用才能完成计算。像这样的例子，你可以找到很多很多，pyo3中非ffi的crate这个时候就很有可能调用来C-API中提供的函数，比如下面这个例子：

```rust
// src/conversions/std/num.rs
    fn into_pyobject(self, py: Python<'py>) -> Result<Self::Output, Self::Error> {
        #[cfg(not(Py_3_13))]
        {
            let bytes = self.to_le_bytes();
            unsafe {
                Ok(ffi::_PyLong_FromByteArray(
                    bytes.as_ptr().cast(),
                    bytes.len(),
                    1,
                    $is_signed.into(),
                )
                .assume_owned(py)
                .downcast_into_unchecked())
            }
        }
```

这时候我们去找对应的ffi代码：

```rust
unsafe extern "C" {
    #[cfg_attr(PyPy, link_name = "_PyPyLong_FromByteArray")]
    pub fn _PyLong_FromByteArray(
        bytes: *const c_uchar,
        n: size_t,
        little_endian: c_int,
        is_signed: c_int,
    ) -> *mut PyObject;
}
```

这就意味着，当代码库中其它部分要调用_PyLong_FromByteArray函数时，使用pyo3完成的二进制扩展通过python进程链接的cpython动态库找到这个符号并进行调用，我们将这个过程更详细地描述一下：

* Python进程启动，动态加载了libpython3.12.so
* 当runtime有调用该函数的代码时，Rust通过动态链接器：ld.so查找符号，找到就可以完成调用过程

所以ABI兼容在这个语境下便是，pyo3-ffi代码中的函数符号能够匹配链接的动态库，聪明的你肯定也意识到如果你要编译这个扩展，编译器一定要能够找到CPython代码完成链接

所以我们可以以pyo3-ffi中的examples为例来看看官方实践：

* 仅使用pyo3-ffi
* 使用maturin完成依赖配置
* 使用pytest完成测试



#### 正确性

为了保证ffi中的代码定义能够和Python解释器有效联动，可以看到在根目录下有一个crate叫"pyo3-ffi-check"，就是用来进行有效性检查的。



### objects-Binding

Python的诸多内置类型，比如dict, list的bindings可以在`src/types`中找到，
