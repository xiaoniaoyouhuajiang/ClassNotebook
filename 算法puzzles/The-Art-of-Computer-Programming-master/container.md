# container
这份文档相当于是hpds（high performance data structure）代码仓的内容介绍，在工作中我们会遇到很多不同的场景，不同场景下使用什么样的数据结构最高效是一个很有研究价值的问题；同时另一个问题是我们能不能使用C/C++等语言帮助我们实现这些数据结构的高效实现，然后暴露出对外接口。

那么第一步是要找到有意义的问题，然后再解决，我们的问题主要从这些源采集：
* 问答网站
    * stackoverflow
* benchmark
    * 各种blog
    * paper，以及各类标准算法以及机器学习算法（benchmark-suite）
* code
    * github gist
    * github/gitlab..
* 算法题网
    * exercism
    * project-euler
    * hackerrank

落到编码层面，一个具体的实现通常需要考虑两方面的问题：
* 数据结构本身的结构（算法层面）
* 实现上的trick，比如simd，或者是代码可读性（工程层面）

值得注意的是，不少的代码仓并不会对构造对象做详尽的benchmark，这种情况下，我会尽可能的补充合适的benchmark snippet，并对结果进行分析

## 场景采集
### code

#### go-bitmap
需要学习的代码是[bitmap](github.com/kelindar/bitmap)

用GO（goasm）语言实现的向量化bitmap



#### xsimd

C++的SIMD指令包装器



#### static_vector

> A dynamically-resizable vector with fixed capacity and embedded storage

https://github.com/gnzlbg/static_vector

主要用于：

* 无法进行内存分配的环境，比如没有空余空间的嵌入式环境，只有静态内存空间是可使用的
* 需要在静态内存段中分配具有复杂生命周期的对象
* static_vector的存储内容本身必须位于对象内部？

在其他库中的实现：

* [folly](https://github.com/facebook/folly/blob/main/folly/docs/small_vector.md)
* [boost](https://www.boost.org/doc/libs/1_59_0/doc/html/boost/container/static_vector.html)
* [eastl](https://github.com/questor/eastl/blob/master/fixed_vector.h#L71)
* [llvm](https://llvm.org/doxygen/classllvm_1_1SmallVector.html)

说了这些，可能大家对该数据结构的使用场景还不是特别清楚，我们通过下面例子来深入：

* https://stackoverflow.com/questions/64516180/deciding-to-use-at-runtime-a-booststatic-vector-or-a-stdvector
* 



#### small_vector

https://github.com/gharveymn/small_vector



#### Folly-small_vector

可以看这里

https://zhuanlan.zhihu.com/p/353485606



#### Boost

#### abseil

#### CPP_OPtimizations Diary


#### jemalloc

一种内存分配器(malloc)

https://github.com/jemalloc/jemalloc

#### scalloc
一种多核可扩展的内存分配器


#### llvm-benchmark

https://github.com/s3cur3/llvm-data-structure-benchmarks



#### scattered

Scattered container store each type's data member sequentially for all objects

https://github.com/gnzlbg/scattered



#### [Annoy](https://github.com/spotify/annoy#annoy)



#### plf-lib
PLF是一系列用C++实现的数据结构头文件库，[请看](plflib.org)

#### scal
github.com/cksystemsgroup/scal
对比并行数据结构算法

### 问答网站

#### Hinnant's short_alloc

https://stackoverflow.com/questions/33722907/hinnants-short-alloc-and-alignment-guarantees


#### 对比矩阵乘法

https://stackoverflow.com/questions/51656818/benchmarking-matrix-multiplication-performance-c-eigen-is-much-slower-than

可以看出，numpy这样的工具已经是被高度优化过的了，所以做一些它比较擅长的事情可以获得很好的性能，那很多时候我们的目标就是找到一些工具还没有覆盖的例程（我们之所以这样做不是为了要大幅优化某一种方法，而是借助这个探索的过程来学习profiling中的一些细节并获得一些经验）

#### xtensor对比numpy

https://stackoverflow.com/questions/57407106/xtensor-cant-reach-numpy-performance

### benchmark
#### c++ container benchmark
这篇博文来自[博文](baptiste-wicht.com)

[代码](github.com/wichtounet/articles/blob/master/src/vector_list_update_1/bench.cpp)

#### paper：The Graph based Benchmark Suite

摘要：这是在共享内存的多核系统上完成的一项测试，主要测试的时图的算法。

#### MineBench: A Benchmark Suite for Data Mining Workloads

cucis.ece.northwestern.edu/projects/DMS/publications/NarOzi06A.pdf

#### Poster: The Problem-Based Benchmark Suite(PBBS), V2

cs.umd.edu/~laxman/papers/pbbsv2.pdf
PBBS是一个基于问题的基准测试套件，包括我多个基准测试，以其IO特性为定义基础，只在比较不同算法的实现，重点对比的是并行算法

#### benchmarks
比对不同语言性能的benchmarks，访问地址：
github.com/kostya/benchmarks

### 其他资源
* github上Baptiste Wicht的代码以及博客（特别是articles的文章）
* paper: a study of emerging scale-out workloads on modern hardware
* principar kernel analysis: a tractable methodology to simulate scaled gpu workloads
* 一本书《Handbook of Energy-Aware and Green Computing》
* github搜索 bits of architecture
* Tools for microarchitectural benchmarking