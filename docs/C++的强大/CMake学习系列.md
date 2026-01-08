# CMake学习系列

![image-20221011221044373](E:\topics\C++的强大\pics\image-20221011221044373.png)

## 从项目出发

没有编译系统，一个项目就只是一些文本的集合。CMake给项目带来了秩序，进入项目中，映入眼帘的CMakeLists.txt定义了：

* 哪些需要编译的内容，如何编译
* 哪些要跑的测试
* 哪些要打的包



CMake与平台无关，CMake会生成平台特定的编译工具文件。

当一个开发创建一个项目，他必须思考他的源码与build目录之间的关系，有两种方法：

* In-source Builds

简单来说就是源码和二进制产物在同一个目录下，好处就是简单

* Out-of-source Builds

![image-20221011223423939](E:\topics\C++的强大\pics\image-20221011223423939.png)

另外一种就是分级，除了表面混乱之外，这种构建方法，还能较好地管理不同选项的构建产物，比如debug以及release两种不同版本。

![image-20221011225217618](E:\topics\C++的强大\pics\image-20221011225217618.png)



在unix类系统下进行编译的命令基本上是：

```shell
mkdir build
cd build
cmake -G "Unix Makefiles" ../source
```

我们可以总结一下，一个项目的构建涉及到两个基本步骤：配置与生成。

需要注意的是，每次执行完CMake构建，都会在构建目录下产生CMakeCache.txt，CMake存储了运行的细节，再次运行CMake便能加速项目的生成。



## 实践——最小项目

### 设定CMake版本

> cmake_minimum_required()

这个命令一般是CMakeLists的第一行，这个命令是如此重要，以致于如果某个cmake脚本不带命令，运行时就会报warning，按照字面意思去理解这个命令就OK。

一般情况下，程序员应当考虑3.2为最老版本候选，因为它提供了现代CMake的完整特性



### project()

```cmake
project(projectName
[VERSION major[.minor[.patch[.tweak]]]]
[LANGUAGES languageName ...]
)
```

* projectName是唯一的必须参数
* 使用的语言包括：C,CXX,FORTRAN,ASM,JAVA等。如果使用多种语言，则使用空格来隔开，一些特殊场景下，如果没有任何语言被使用到，就输入LANGUAGES NONE
* 这个命令非常重要的一点在于，检查被允许的语言对应的编译器，确保它们能够正确编译以及链接。
* 如果不使用这个命令，CMake会默认认定用户使用C CXX作为开发语言，并检查相关的编译系统



### 构建可执行文件

```cmake
add_executable(targetName source1 [source2 ...])
```

上面的句子是构建可执行文件的命令。。下章节深入介绍



## 构建目标

```cmake
add_executable(myApp main.cpp)
```

仅靠这个例子，基本不可能掌握到cmake构建目标的机制，我们稍后看一些复杂点的例子

除了可执行文件，开发者需要编译和链接库，



### 定义库

编译库语句是`add_library()`

```cmake
add_library(targetName [STATIC | SHARED | MODULE]
	[EXCLUDE_FROM_ALL]
	source1 [source2 ...]
)
```

下面会通过两个案例来演示通过vs以及cmake创建静态库，动态库，并使用它们；

如上所述，我们能够通过关键字创建三种不同类型的库，分别是：

* STATIC：静态库。windows平台下，产物为targetName.lib；Unix-like系统下一般为libtargetName.a;
* SHARED:动态链接库。windows下，产物为targetName.dll，APPLE平台下，libtargetName.dylib；linux下，libtargetName.so；
* MODULE：运行时动态链接的库；

通过cmake构建的flag：`BUILD_SHARED_LIBS`我们能够省略掉上述的三个关键字

更细致的区别，请看《编译链接》



### 链接目标





## 使用子目录

对于小项目，我们可以把所有文件放到一个目录下，但大部分实际项目不会这么做，我们一般会根据文件类型分类并归档，履出合适的层级关系。Cmake中的`add_subdirectory()`和`include()`就是帮助构建系统完成这件事的命令



### add_subdirectory()

```cmake
add_subdirectory(sourceDir [ binaryDir ] [ EXCLUDE_FROM_ALL ])
```

该命令允许项目将其他目录的内容置入构建过程中，被包含的目录必须有其自身的CMakeLists.txt文件，每当add_subdirectory()被调用的时候就会运行该文件的构建流程，sourceDir可以是相对路径或是绝对路径，如果被包含的子目录在项目的源码树之外通常就会使用绝对路径。

































