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
* rust作用域的层级结构
* 如何为一个项目实现多个模块文件
* rust的trait和go的interface的区别
* rust如何实现栈上的数组
* rust如何实现allocator

解惑：
* ＆和＊：&在rust中是借用（&expr或&mut expr，不考虑expr & expr）以及被借用的指针类型（&type, &mut type, &'a type, &'a mut type），而*就是解引用(*expr)以及裸指针（Raw pointer）（*const type, *mut type）。值得注意的是，使用println!去打印对象，会自动的完成解引用；想要加强对所有权的理解，可以看一些reddit以及stackoverflow中的例子，确认理解了问题的正解之后；再在一些项目中使用debugger去观察对象在断点处的状态，最后再读下Rust程序语言设计中的引用与借用，便能够理解
* 首先回顾很重要的一点就是同一时间，可变引用只能有一个。回到问题，不管是可变变量还是可变引用，它们都有在对应的作用域内改变指向对象的能力，因此可变引用只能为可变对象创建
* 首先要明确只存在一种字符串类型：`str`，而它通常以被借用的形式出现，而最常用的str的容器则是标准库中的String
* 标准库中智能指针有这些类型，我们分开讨论：
    * Box<T>：本质是实现了`Deref`和`Drop`两个关键trait的结构体，可以用来创建递归数据结构以及管理数据结构（容器类型）；
        * Deref：解引用的实现，注意实现deref方法时，输出的是其想要输出目标**的引用**，另外一方面可以使用Type关键字指定输出引用的类型，从而实现强制类型转换。注意，`Deref`可以用于重载不可变引用，但是也存在着用于重载不可变引用的`DerefMut`
* 在进入代码级别的作用域管理前，必须得先明确`crate`和`crate根`的概念，`crate根`是package的**接口文件**，package的作用可以是library，也可以是executable-file，而它们向外暴露的实体是二进制产物，另一方面它们在rust文件中也有**明确的**表征，即`lib.rs`和`main.rs`。在这些共识之下，crates根代表的实际就是这些个关键文件。优先讲crate根是因为我们关注一个语言的模块系统经常以`文件组织`作为切入点，这符合直觉。而`crate`是:
    * 编译产物，在第一点中提到二进制产物也能够称为`crate`，这里要提到rust编译器的工作模式：rust总是使用单个源文件作为输入来开启编译过程。你肯定能猜到，这些源文件就是第一点中的`crate根`，但另一方面，这些关键的二进制产物同样是`crate`，这也是为什么容易搞不清楚，从使用的角度说，就更能明确为何一个package**必须有一个crate（0 lib crate +  N bin crate 或者 1 lib crate + n bin crate。$N \in [1,\infty], n \in [0, \infty]$**。
    * 一种特殊的模块，就叫"crate模块"。这也符合直觉，任何系统的模块存在都是为了crate服务的，编译也从crate对应的文件出发，因此它们是根，即crate根
    * rust中有几个关键字可以用来管理作用域：
        * mod: 其语法为`mod <Module Name> {...}`，

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


### vscode