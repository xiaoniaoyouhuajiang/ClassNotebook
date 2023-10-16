# container
这份文档相当于是hpds（high performance data structure）代码仓的内容介绍，在工作中我们会遇到很多不同的场景，不同场景下使用什么样的数据结构最高效是一个很有研究价值的问题；同时另一个问题是我们能不能使用C/C++等语言帮助我们实现这些数据结构的高效实现，然后暴露出对外接口。

那么第一步是要找到有意义的问题，然后再解决，我们的问题主要从这些源采集：
* 问答网站
    * stackoverflow
* benchmark
    * 各种blog
* code
    * github gist
    * github/gitlab..

落到编码层面，一个具体的实现通常需要考虑两方面的问题：
* 数据结构本身的结构（算法层面）
* 实现上的trick，比如simd，或者是代码可读性（工程层面）

值得注意的是，不少的代码仓并不会对构造对象做详尽的benchmark，这种情况下，我会尽可能的补充合适的benchmark snippet，并对结果进行分析

## 场景采集
### code
#### go-bitmap
需要学习的代码是[bitmap](github.com/kelindar/bitmap)

用GO（goasm）语言实现的向量化bitmap



#### static_vector

> A dynamically-resizable vector with fixed capacity and embedded storage

https://github.com/gnzlbg/static_vector



#### jemalloc

一种内存分配器(malloc)

https://github.com/jemalloc/jemalloc



#### scattered

Scattered container store each type's data member sequentially for all objects

https://github.com/gnzlbg/scattered



#### [Annoy](https://github.com/spotify/annoy#annoy)



#### plf-lib
PLF是一系列用C++实现的数据结构头文件库，[请看](plflib.org)

### 问答网站
### benchmark
#### c++ container benchmark
这篇博文来自[博文](baptiste-wicht.com)

[代码](github.com/wichtounet/articles/blob/master/src/vector_list_update_1/bench.cpp)

