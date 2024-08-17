# rust学习
## rust应用场景
* 高性能数据结构
* C++的替代场景

## 语言的核心特性

### 语言设计
迷惑的点：
* 总结&和*符号
* 可变变量的引用和可变引用有啥区别
* 字符串的复杂性如何体现
* rust中智能指针的使用场景
* crate的详细解释，模块树的层级结构
* 如何为一个项目实现多个模块文件
* 什么是semver trick
* 为什么迭代器比普通循环更快
* rust的trait和go的interface的区别
* rust的core::mem::ManuallyDrop如何使用
* 如何实现栈上的数组
* 如何实现allocator
* rust的union和struct的区别
* usize的使用场景一般是什么
* 枚举类

解惑：
* ＆和＊：&在rust中是借用（&expr或&mut expr，不考虑expr & expr）以及被借用的指针类型（&type, &mut type, &'a type, &'a mut type），而*就是解引用(*expr)以及裸指针（Raw pointer）（*const type, *mut type）。值得注意的是，使用println!去打印对象，会自动的完成解引用；想要加强对所有权的理解，可以看一些reddit以及stackoverflow中的例子，确认理解了问题的正解之后；再在一些项目中使用debugger去观察对象在断点处的状态，最后再读下Rust程序语言设计中的引用与借用，便能够理解
* 首先回顾很重要的一点就是同一时间，可变引用只能有一个。回到问题，不管是可变变量还是可变引用，它们都有在对应的作用域内改变指向对象的能力，因此可变引用只能为可变对象创建
* 首先要明确只存在一种字符串类型：`str`，而它通常以被借用的形式出现，而最常用的str的容器则是标准库中的String，String是类似于`Vec`的动态堆字符串类型，而`str`是不可变的utf8字节序列，由于其大小不可知，我们通常使用`&str`。两者的关系可归为`Vec<T>`和`&[T]`。str实际存储的位置可能是：
    * 二进制文件中的某处：通常存的是字符串的字面量，比如"foo"
    * String变量中
    * 栈中
* 标准库中智能指针有这些类型，我们分开讨论：
    * Box<T>：本质是实现了`Deref`和`Drop`两个关键trait的结构体，可以用来创建递归数据结构以及管理数据结构（容器类型）；
        * Deref：解引用的实现，注意实现deref方法时，输出的是其想要输出目标**的引用**，另外一方面可以使用Type关键字指定输出引用的类型，从而实现强制类型转换。注意，`Deref`可以用于重载不可变引用，但是也存在着用于重载不可变引用的`DerefMut`
        * Drop: 对象离开作用域时必须执行的函数。drop函数不能显式调用，因此如果需要提前清理值，可以使用`std::mem::drop`
    * Rc<T>：
* 在进入代码级别的作用域管理前，必须得先明确`crate`和`crate根`的概念，`crate根`是package的**接口文件**，package的作用可以是library，也可以是executable-file，而它们向外暴露的实体是二进制产物，另一方面它们在rust文件中也有**明确的**表征，即`lib.rs`和`main.rs`。在这些共识之下，crates根代表的实际就是这些个关键文件。优先讲crate根是因为我们关注一个语言的模块系统经常以`文件组织`作为切入点，这符合直觉。而`crate`是:
    * 编译产物，在第一点中提到二进制产物也能够称为`crate`，这里要提到rust编译器的工作模式：rust总是使用单个源文件作为输入来开启编译过程。你肯定能猜到，这些源文件就是第一点中的`crate根`，但另一方面，这些关键的二进制产物同样是`crate`，这也是为什么容易搞不清楚，从使用的角度说，就更能明确为何一个package**必须有一个crate（0 lib crate +  N bin crate 或者 1 lib crate + n bin crate。$N \in [1,\infty], n \in [0, \infty]$**。
    * 一种特殊的模块，就叫"crate模块"。这也符合直觉，任何系统的模块存在都是为了crate服务的，编译也从crate对应的文件出发，因此它们是根，即crate根
    * rust中有几个关键字可以用来管理作用域：
        * mod: 其语法为`mod <Module Name> {...}`，`mod`代表module，即我们在各类编程语言中最熟悉的模块，需要注意，模块与rust文件的关系是mod块嵌入在不同文件中，所以一个rust文件可以有多个模块，mod的详细使用方法可以在下一点中找到
        * pub: 将符号导出为可由外部模块导入的，即公有。可以导出的内容有函数，模块，结构体，枚举类以及字段
        * use: 用于将其他crate的内容导入
* 很多语言的模块设计强调了文件系统的参与（比如Python），但是Rust将文件布局和模块层次进行了解耦，因此rust可以实现更加细粒度的隐私控制。使用`mod`去导入其他文件中的模块时，首先调用方一定需要显式地`mod <module>;`，其次可以有两种方法：即`<module>.rs`或者是`<module>/mod.rs`文件，
* semver trick是
* 迭代器是Rust的零成本抽象之一，
* rust的trait和go的interface
* rust的ManuallyDrop
* 参考stackoverflow的27859822问题：
* 如何实现allocator
* struct和union的区别
* usize实际是和计算机系统相关的无符号整数类型，所以表示非负场景的数值都可以用usize，比如数组长度

### 语言内部



#### 标准库

rust的标准库很小巧，这是一个Reddit上的月经话题。

参考文章https://nindalf.com/posts/rust-stdlib/

这里总结了这么设计的一些原因：

* 标准库很难新增代码，因为rust语言的项目原则中[stability as deliverable](https://blog.rust-lang.org/2014/10/30/Stability.html)提到，rust禁止breaking changes。



#### 链接过程&linker
链接器的性能通常是一个比较重要的考虑因素，编译总会有讲obj文件链接在一起的过程，这个过程就是linker在发光发热。

rust使用的链接器是`lld`

rust编译器支持静态/动态地将crate链接起来的方法。


一些要点：
* 智能指针RefCell<T>与内部可变性：内部可变性（Interior mutability）是Rust中的一个设计模式，允许即使有不可变引用时也可以改变数据，这是通常情况下借用规则不允许的，因此需要在数据结构中使用unsafe来模糊可变性和借用规则。
* Rc为引用计数智能指针，它与Python中的PyObject有什么不一样呢？首先Rc<T>用于希望在堆上分配一些供多个部分读取的内存场景，并且不确定谁会最后使用它。

## 练习
一些外部的有趣练习：
* rustlings
* rust-quiz
* lifetimekata
* Rust latam: procedural macros workshop

交互性质的练习：
* oort

### rust练习册-rustlings
```shell
git clone -b 5.6.1 --depth 1 https://github.com/rust-lang/rustlings
cd rustlings
cargo install --locked --force --path .

# 开始
rustlings watch
```
这个练习的好处：
* 有一种读条进步的感觉，比较爽(对于新手)
* 学会使用“rustc --explain EXXXX”
* 熟悉编译器的报错和内容
* 很多题没有标准答案，可以多试试，就当是熟练和建立rust心智模型的过程
* 建议完成时间：4天内
* 其中我认为完成部分的习题有比较大的意义（如果你是一个新手，你直接去做这些内容可能也不太容易一次通过）：
    * vecs/vecs2.rs
    * move_semantics/*
    * enums/enums3.rs
    * strings/*(尤其string4)
    * hashmaps3
    * quiz2.rs
    * error_handling/errors6.rs(知识点：enum;错误传播;map_err)
    * quiz3.rs
    * iterators/iterators2/3.rs
    * smart_pointers/cow1.rs
    * threads/threads3.rs
    * macros/macros3.rs
    * conversions/try_from_into.rs
    * conversions/as_ref_mut.rs

当然我认为rustlings也有些不足（不过这些本来就不是rustlings设计之初考虑的事）:
缺少一些复合型的训练


### 项目学习1-smallvec

#### 项目概况

#### code snippets

```rust
// 用枚举类来构建两种堆分配的错误类型
#[derive(Debug)]
pub enum CollectionAllocErr {
    CapacityOverflow,
    AllocErr {
        layout: Layout,
    },
}
impl core::fmt::Display for CollectionAllocErr {
    fn fmt (&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        write!(f, "Allocation error: {:?}", self)
    }
}
```

### 项目学习2：py-spy
py-spy是一个python profiling项目，配备较多的测试用例，配合rust-toolchains，是个不错的学习项目。建议事不考虑bindings的代码，直接从rust-api下手开始看。另一方面，对profiling/debug领域感兴趣的人也应该学习下这个项目。

#### 关键的数据结构/结构体
* PythonSpy: Python进程监视器，存储全部状态的抽象
* PythonProcessInfo: Python进程的消息存储结构，包含信息有：memory map layout, 解析好的二进制信息（libpython）：这里值得注意的是二进制信息的存储结构是`BinaryInfo`，其中有一个关键字段symbols是内存名称到地址的Map
* InterpreterState：Python解释器的状态机trait，有各个关键版本的impl



#### 实现中的技巧

* 使用read_process_memory获取进程运行时的内部结构（依赖各个OS的syscall，比如linux的[process_vm_readv](https://man7.org/linux/man-pages/man2/process_vm_readv.2.html)），
* 用rust的类型推断结合技巧一copy_struct

![image-20240623142813165](../statics/image-20240623142813165.png)

* 使用binary parser——goblin解析并获取二进制文件的关键符号的内存地址，再使用技巧二尝试从内存中提取出需要的`python结构`，这里一定会存在的问题是ASLR（Address space layout randomization），处理地址空间随机化的方法需要解释下,如果说python解释器是附带符号的，则可以通过Python版本来获取interp_head和_PyRuntime两个变量的地址来获取解释器的地址

首先可以通过`cat /proc/sys/kernel/randomize_va_space`获取机器的策略：

`0` 表示禁用 ASLR。

`1` 表示启用基本随机化。

`2` 表示启用完全随机化。



* 这里存在一个问题，前文提到的`InterpreterState`从何而来？答案是使用`rust-bindgen`来获得Python关键对象的rust结构体，具体分析如下：
  * 生成binding的脚本为位于项目根目录下的`generate_bindings.py`，对应的函数为`extract_bindings`，内部行为可以分解如下：
    * 获取CPython源码
    * checkout到指定的Python版本
    * 运行configure生成`pyconfig.h`
    * 将`Python.h`,`frameobject.h`,`pycore_pystate.h`,`pycore_interp.h`,`pycore_frame.h`作为输入写入到文件`bindgen_input.h`
    * 将`bindgen_input.h`作为输入生成`bindgen_output.rs`，注意这里需要指定一些`whitelist-type`，最后将文件写入到vxx.rs中即可
  * 上述生成的内容实质上为
* 获取call stack的方法是：
  * 从PyInterpreterState中取出所有Python线程
  * 遍历每个线程的PyFrameObject对象，获取call stack
* `top`命令本质是生成一个监控的Iterator，每次iter就是从Python进程中采样（获取调用信息），这个iterator每次进行迭代，实际上就是Sampler中的receiver从一个采样线程中去获取采集到的性能样本。采集的代码如下：

![image-20240623195805572](../statics/image-20240623195805572.png)



#### 依赖py-spy做的有趣的事





### 开发中的实践

这是我学习rust过程中记录下的认为有意义的code snippet

* 实现一个类可以不断输入值来更新时间的早晚
* 使用unsafe实现插桩，完成这些功能
    * 重复运行某一个函数
    * 度量某个函数的运行时间
* 侦测器：筛选出目标进程中满足筛选条件的函数符号

### 实践-使用PyO3创建一个ssh连接池
这个实践有以下的目的：
* 在大量的例子和帮助中学习，熟悉rust
* 了解pyo3的开发模式，为后续写binding, warapper打下基础
* 了解russh的使用方法，机制
* 简单学会使用tokio来完成异步逻辑
* 实现一个并发的，惰性的ssh连接
* 实现文件的传送（file-likt-obj/file）

安装maturin: `pip install maturin`

创建目录（也可以用pyenv创建虚拟环境完成下列步骤）
```
mkdir py_rpc
cd py_rpc
maturin init
```

#### 定义pyo3中的函数
`#[pyfunction]`用于定义一个Python中的函数（调用Rust），

#### 定义pyo3中的class
定义一个wrapper十分简单：
```rust
#[pyclass]
struct MyClass {
    inner: i32
}
```
但wrapper存在一些问题：
* 无法使用lifetime参数：由于pyclass是动态的数据，rust编译器没办法去追踪pyclass本身的生命周期，保证内存安全性的唯一办法是：pyclass不要借用任何短于static生命期的数据。 -> pyclass对象中的每个引用的生命周期>=static
* 一个问题是如果存在这样一个对象，它在rust函数中有自己的owner，同时也能被python解释器访问，需要用到引用计数的智能指针比如`Arc`, `Py`
* 无法使用泛型参数，因为rust编译器会为每个泛型T生成相应的代码，这个生成过程是在编译阶段完成的，最好的解决方法是为pyclass实现一个宏

```rust
use pyo3::prelude::*;

struct GenericClass<T> {
    data: T,
}

macro_rules! create_interface {
    ($name: ident, $type: ident) => {
        #[pyclass]
        pub struct $name {
            inner: GenericClass<$type>,
        }
        #[pymethods]
        impl $name {
            #[new]
            pub fn new(data: $type) -> Self {
                Self {
                    inner: GenericClass {data: data},
                }
            }
        }
    };
}

create_interface!(IntClass, i64);
create_interface!(FloatClass, String);
```

python runtime和rust runtime有很大的差异，所以当我们研究一个抽象的`对象`在两个runtime中如何进行转换时，一定会回顾两个语言本身的设计原则：
* 


#### 关于RPC
定义RPC框架，我们首先想到的就是通信的数据结构以及调用方法，IDL全称为interface design language，很多RPC框架需要使用IDL生成对应的代码（同时IDL很重要的一个特征是不依赖实现语言），因为其中封装了消息收发，结构体编码解码，生成结构体等操作。

```rust
struct Msg{
    tag: String,
    detai: String,
}
```

实现RPC框架，需要定义的内容包括：
* 消息，编码解码的传输层
* message code generator(idl parser + message derive)
* 

我们要做的是thrift RPC框架，使用thrift的好处是：
* 已经有较多知名大企业使用，有保障 

thrift中的数据类型可以分为`基础类型`，`容器类型`，`常量类型`:
值得注意的是容器类型包含map, set, list



### 配套工具

这两个工具真好用：
* cargo：
    * 
* rust-analyzer：
    * 最好的rust老师之一
    * 和VSCODE/NVIM集成度高，新用户可以快速上手调试

## 开发计划

使用rust来开发：
* 串联主要工作流程（三位一体）的小工具
* 网络请求分析工具（格式化目标进程的网络请求参数）
* linux系统调用的追踪与回放工具
* 简化版本的blktrace工具(blk-explorer)
* 多机的硬件性能追踪统计工具
* 联合go开发的hpcrun改版工具
* python第三方库没有覆盖到的性能敏感部分


## IDE

### neovim
为什么要使用neovim来进行rust编程，可以参考这个博客：[博客](https://rsdlt.github.io/posts/rust-nvim-ide-guide-walkthrough-development-debug/)

![图片](../statics/neovim-rust.png)

#### 我的安装流程
```shell
# 确保安装版本 > 0.9.0的neo-vim
pkg install nvim

# linux环境安装nvim：github上有预编译的二进制文件
# 需要自己编译安装，也没有问题，基本只需要gcc(github仓大概300M)
git clone https://github.com/neovim/neovim
git checkout stable
cd neovim && make CMAKE_BUILD_TYPE=RelWithDebInfo

# 安装nerd font和nvchad
注意nerd font需要安装在对应的terminal软件依赖中，比如使用windows terminals登录，则对应的windows系统需要安装相应字体
...
git clone https://github.com/NvChad/NvChad ~/.config/nvim --depth 1 && nvim

# 准备好rust-tools
git clone xx ~/.config/nvim/lua/custom/
```

### vscode