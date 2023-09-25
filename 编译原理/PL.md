# Programming Language

## 编译后端技术

### 如何代表程序

将源代码转为AST之后，在解释器去执行之前，代码是否会有更加通用的表达形式呢？

这就是中间表示：用指令的序列来表达程序 ？？：是不是有点像汇编

实际上，虽然汇编语言从开发的角度看很不友好，但从CPU的角度来看，这种指令非常的简单好处理，我们可以将两类代码的抽象语法可视化，这样看

![image-20230924170418193](/home/xiao-sa/software/ClassNotebook/statics/image-20230924170418193.png)

从多个角度来看，这样的程序更好分析



#### control flow graph

什么是CFG呢，举例演示：

```assembly
@main {
	v: int = const 4;
	jmp .somewhere;
	v: int = const 2;
.somewhere:
	print v;
}
```

CFG表示中有一个重要概念，叫基本块（Basic Blocks）。

基本块的概念简单来说就是一串指令，这串指令一旦被执行，就会被顺序地被执行直到最后一个指令。



### MLIR

MLIR项目是一种构建可重用可扩展的编译器中间表示的工具箱，其一大特点是能够显著降低构建特定领域编译器的成本，改进异构硬件的编译水准。

相关内容的Talks可以看这里： https://mlir.llvm.org/



MLIR有很多成功的典型应用，下面拿我感兴趣的一些项目说明一下：

* [Pylir](https://github.com/Pylir/Pylir)：一个Python的AOT编译器
* [Torch-MLIR](https://github.com/llvm/torch-mlir):Torch-MLIR 项目旨在提供从 PyTorch 生态系统到 MLIR 生态系统的一流编译器支持。
* [VAST](https://github.com/trailofbits/vast):C/C++代码的程序分析框架
* [Mojo](https://docs.modular.com/mojo/)：这个名气挺大，LLVM之父想要用来统一AI技术栈的类Python语言
* [HeteroCL](https://github.com/cornell-zhang/heterocl):多平台编译的基础设施



其他的还有这些：

* TPU-MLIR：面向TPU的机器学习编译器
* XLA：在其中充当计算图的转化框架



可能不少人会想到一个项目——TVM，并好奇TVM和MLIR是什么关系。首先TVM是一个用来加速向量计算的编译器，是一个解决在特定硬件上运行机器学习模型的完整的端到端方案，可以将模型编译为特定的硬件设备上的模型文件，然后在部署侧上安装tvm runtime，就可以完成高性能的部署了。在TVM的整个优化流里，自定义了一种中间语言：Relay



#### LLVM的优势

大家或多或少都应该听过LLVM或者说是接触过LLVM相关的生态。我认为LLVM实际上是一种框架，或者是一套编译技术的工具集合，其特点是“可编程”。比方说，RUST，SWIFT，Julia这几门当前比较“新颖”的计算机语言，其后端部分都使用了LLVM-IR，算是使用了这个工具箱，LLVM帮助解决的最大问题是平台兼容性：LLVM库可以以可编程的方式生成机器码，开发者可以使用API来生成IR，然后编译IR，快速执行。

举个例子，大多数的计算机语言都会有函数，全局变量的概念，不少会有CFFI，协程等概念，LLVM有相应的IR，以及相应的metaphors。因此你不需要重新造轮子。

以C语言作类比是一个理解LLVM的不错方法，C是构造系统的一个非常合适的计算机语言，因为C的各种抽象非常接近硬件的API，C语言的表达是完成这些映射的最简表达。但是C语言。。。



LLVM主要用作三种场景：

* 构造AOT编译器（clang）
* 构造JIT编译器(julia, numba)
* 自动代码优化
* 构造DSL（WASM，MLIR）





#### MLIR教程

LLVM 在特定领域语言方面的成功激发了 LLVM 内的新项目来解决它们所产生的问题。最大的问题就在于一些DSL生成LLVM-IR的成本太过于昂贵（必须要在前端下十分大的功夫），为了解决这个问题的一个解决方案便是Multi-Level Intermediate Representaion，即MLIR。



这个教程的overview：

* 如何构建一个玩具语言
* MLIR的核心概念：operations, regions, dialects
* 使用MLIR去表示玩具语言
  * 介绍dialect, operations, ODS, verifications
  * 为常规的operations去绑定特定语义
* 特定优化的高级语言
* 为结构而不是ops写特定的passes
* 降级到LLVM-IR



常见的编译流程图：

![image-20230923174021581](/home/xiao-sa/software/ClassNotebook/statics/image-20230923174021581.png)

AST -> LLVM-IR



Toy Compiler的编译流程：

![image-20230924000621226](/home/xiao-sa/software/ClassNotebook/statics/image-20230924000621226.png)

“Dialect”译为方言，



## compiler principle

### 语言的一些设计

#### enumerations

##### C/C++



##### python







## Create a lang

### Monkey



### Porth

#### 简述

> Stack-based编程语言是指在程序执行期间，所有的变量和操作数都通过一个栈数据结构来传递和处理的编程语言。这些语言的代码通常由一系列指令序列组成，每条指令都会从栈中取出一个或多个参数，并将结果压回栈中。这些指令可以用于执行各种操作，例如算术运算、逻辑运算、函数调用、变量赋值等等。Stack-based编程语言通常被设计为非常简洁和易于理解，因为它们的语法和语义都非常直观。由于栈数据结构的特性，这些语言的执行速度通常很快，并且它们不需要像其他语言一样频繁地进行内存分配和释放操作，因为它们的所有变量和操作数都存储在栈中。一些常见的Stack-based编程语言包括Forth、PostScript、Factor、Joy等等。

然后，Porth很像Forth，也是一门stack-based的语言。





### Python-v1



### Python-v2



