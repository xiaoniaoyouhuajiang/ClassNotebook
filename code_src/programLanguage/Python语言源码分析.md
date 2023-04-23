# Python语言源码分析

## 编译与基础



获得python源码：git clone

从源代码编译参考：Python3.7源码剖析 ------- 手把手教你windows编译Python - 艾欧尼亚的文章 - 知乎
https://zhuanlan.zhihu.com/p/351541371

C,GO,C++直接将源码编译为特定平台上的可执行二进制文件，而JAVA和.NET CLR则编译为虚拟机专用的语言，轻松实现代码跨平台。Cpython runtime在第一次执行代码的时候，也有编译的过程，编译后的结果是字节码，它们将被存储在.pyc文件中并作为执行的缓存。Cpython中的compiler是纯C语言实现的。

compiler可被分为两种类型：

* self-hosted:以bootstrapping技术作为支撑，编译器自身是编译语言实现的，比如GO语言。
* source-to-source:靠另一个已经有编译器的语言实现

当一个新的语言被实现时，需要一个软件来编译实现好的编译器，所以一般都是依赖于一个成熟的编程语言。GO语言一开始的编译器由C来实现，接着用GO语言自身重写了GO语言的编译器（自举），经过编译后，GO语言便拥有了由自身实现的编译器。

而对Python而言，Python保留了C的编译器实现，同时一些标准库：sockets,ssl,os,wxpython沿用了C的API，也有一个Python自己解释自己的实现：Pypy



## grammar

Python的词法解析，类型系统/数据模型以及执行模型，依赖系统（the import system）的内容，可以在docs.python.org/3/reference中找到，这就是Python的官方文档。这部分的内容也可以在Cpython的doc > reference中找到。

#### 一个例子

> doc/reference/compound_stmts.rst

比如说，这个文档就定义了python中statement的定义，以"with"的定义为例（讲解参考之一：https://dbader.org/blog/python-context-managers-and-with-statement），with的作用是声明一个上下文管理器。

上面提供的文档都是**人类可读的内容**

而提供给机器的定义可以在grammar/grammar中找到，这部分的内容暂时略过，会涉及到语法结构的记录方法，但不是我目前关注的重点。


## C语言的简单讲解
C语言和python的一个巨大区别是C preprocessor。

### C的预处理器(C Preprocessor)
C预处理器对源码处理后生成的文件会被编译器拿去处理，预处理器的主要目的是在源码文件中做文本替换,在遇到#if之后会做一些基本的条件判断。

#### 让我们首先看看#include
#include是用来将一个文件的源码载入到当前源文件中的语句，举个例子，看下Cpython的/_multiprocessing/semaphore.c文件，最顶部

```c
#include "multiprocessing.h"
```
这个语句会让预处理器拉取`multiprocessing.h`文件内容并放到这个文件中的输出文件中。其中，包含文件是否有<>决定了预处理器的处理次序，有<>则会优先搜索系统包含的文件。


## 配置与输入

让我们回顾一下如何执行Python代码：

* Python -c "<what you want to execute(python code)>"
* python -m  <module>
* python <file contain python code>
* cat <file> | file
* 开启repl并输入指令
* 调用C API


对于Python解释器而言，执行代码需要用到：

* 一个可以执行的python模块
* 状态：比如环境变量
* 配置：可选的或可用的

python code在被执行前，会先建立一个Cpython runtime

runtime的配置被定义为三种数据结构

* PyPreConfig 用于初始化配置-PyPreConfig
* PyConfig 用于runtime的配置-PyConfig
* Cpython解释器的编译完成的配置

这三种数据结构都被定义在Include/cpython/initconfig.h中。

#### Pre-Initialization Configuration
PyPreConfig的三个主要函数：
* 设置Python内存分配器
* 设置LC_CTYPE分配数
* 设置UTF-8模式

PyPreConfig类型包含的字段都是整形，与PyPreConfig相关的文件有两个：

> Python/initconfig.c
> 该文件在系统环境下将配置load进系统环境中并与字符命令合并
> Include/cpython/initconfig.h
> 该文件则定义了初始化配置的数据结构

#### 运行时配置的数据结构
前面也提到运行时配置的数据结构被设置在pyConfig结构体中，其中包括：
* runtime flags：包括debug/optimized等
* 运行模式：包括script file, stdin, module
* 扩展选项，用-X <option>来进行指定
* 运行时的环境变量

#### 使用命令行方法来设置运行时
具体有哪些办法可以参考链接（docs.python.org/3/using/cmdline.html）

举个例子，python有一种运行模式称作verbose模式，主要被用于Debug

```python
# 打印被载入运行时的模块
./python -v -c "print('hello world')"
```
运行上面的命令，你会看到几百行的输出，包括使用到的第三方模块以及任何系统环境中的东西

运行时的配置加载逻辑被封装在initconfig.c文件中的config_parse_cmdline()中