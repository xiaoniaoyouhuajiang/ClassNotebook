# 模块分析

项目的程序结构分析**有时候**可以起到帮助开发者梳理项目内部结构的作用。

我会以下面项目作为分析的对象：

* Rust
  * cargo-modules
* c/c++
  * unity build
  * 
* doxygen



## 实际案例

### cargo-modules



### amalgamation

关于代码合并，可以看看sqlite的一篇文章：

https://www.sqlite.org/amalgamation.html

下面我列出一些简单的引用内容：

> 超过 100 个单独的源文件被连接成一个名为 "sqlite3.c" 的单个大型 C 代码文件，并被称为 "合并文件"。合并文件包含应用程序嵌入 SQLite 所需的一切。
>
> 将所有 SQLite 代码合并到一个大文件中可以使 SQLite 更容易部署——只需跟踪一个文件。而且因为所有代码都在一个翻译单元中，编译器可以更好地进行过程间和内联优化，从而生成的机器代码比原来快 5%到 10%。
>
> 

通过sqlite提供的内容，我们了解到，“合并”后的项目有这些变化：

* 更高的性能，这是代码内联后带来的性能提升，代价是更大的二进制产物
* 更高的编译效率

可以用的工具有很多（就像sqlite用Makefile代码来完成）：

* 通过定制化的CMake，比如https://github.com/sakra/cotire
* https://github.com/vinniefalco/Amalgamate



## 代码静态分析





## 算法