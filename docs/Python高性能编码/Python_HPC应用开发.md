# Python HPC应用开发

该系列的主题是介绍，详解Python开发高性能扩展的流程，案例

相关工具链:

* pybind11
* build system(cmake/scikit-build/..)
* cython
* test(pytest, gtest)



案例：

* Dlib
* pybind11_example
* thinc
* torch
* xtensor
* cytoolz





## pybind11开发案例：Dlib

### Dlib介绍

官方文档：http://dlib.net/ml.html

Dlib包含了广泛应用的机器学习算法。所有的设计都是高度模块化的，快速执行。包含干净和现代的c++ API，使用起来简单。它被广泛应用于机器人、嵌入式设备、移动电话和大型高性能计算环境。



Dlib有python实现的wrapper，这将是我们介绍的重点。



### Pybind11介绍

pybind11是一个轻量级的头文件库，它在Python中公开c++类型，反之亦然，主要用于创建现有c++代码的Python Binding。它的目标和语法与出色的Boost相似。Python库，作者David Abrahams:通过使用编译时内省推断类型信息来最小化传统扩展模块中的样板代码。



### 在WSL1上构建Dlib

下面是通用的构建流程

* git clone Dlib
* 通过HWINFO查下你所使用的CPU是否有AVX指令；（https://www.hwinfo.com, 以及显卡啥的）
* 构建(linux cmake项目构建流程)
  * cd Dlib; 
  * mkdir build;
  * cmake .. -DUSE_AVX_INSTRUCTIONS=1;
  * cmake --build .



运行UT

```shell
cd dlib/test
mkdir build
cd build
cmake ..
cmake --build . --config Release
./dtest --runall
```



python安装

python setup.py develop

再在python的test目录下跑下UT:

pytest



### 看下构建的流程细节

* setup.py中的一些细节
* CMakeLists.txt中的细节



## python,cpp混合调试方案

**本方案适用于VSCODE + linux的编程环境**

Visual Studio有更加成熟的混合调试模式



简单来说，要做的事情有：

* 打断点（Python, CPP的源码）
* 暴露Python进程的PID
* 修改launch.json
* 添加Python解释器
* -g 编译，生成SO，附带调试符号
* debug:start！



## 什么地方需要混编

什么地方需要高性能

* 任意软件的热点函数
* 编码器，压缩软件
* 内存开销大的软件，如GUI
* 自动微分，深度学习编译器后端
* 图形渲染器



其他

* 控制部件，如GPU
* 操作系统相关，如控制Cgroup，控制syscall



要点：

* 对混编感兴趣，需要深入学习CPP编程
* 如果对开发的软件性能至关重要，每个点都要把握，可以完全用CPP，毕竟CPP本身的抽象能力就非常强
* 把握要点：很多时候高性能组件都与业务强相关，将时间投入到正确的地方
* 多关注运行时的**下游**



值得关注的混编项目：

* 性能测试 - pytest-benchmark

* 压缩算法 - borg, fastparquet, lzhw
* 常用算法 - More Itertools, pdsa, cytoolz, CPPItertools
* 符号计算 - sage
* 深度学习 - MetaNN



## cython代码如何使用

### 像py文件一样导入pyx

![image-20221109233716294](E:\topics\Python高性能编码\statics\image-20221109233716294.png)

![image-20221109233930149](E:\topics\Python高性能编码\statics\image-20221109233930149.png)



如图，如果我希望从**enter_exp.py**中将**my_matrix.pyx**文件以模块的形式导入并引用其中的对象，我该怎么做呢？

事实上，你只需要。。

示例代码：

```python
# enter_exp.py文件
import pyximport

pyximport.install(language_level=3)
from my_matrix import Matrix
```



### 魔法的背后

想了解Python到底如何导入.so文件吗？

活用debugger和code navigator，我们自己来找答案：

将find_and_load的import琐碎细节忽略掉，我们很快能锁定魔法的入口：

![image-20221109234527747](E:\topics\Python高性能编码\statics\image-20221109234527747.png)



PyxLoader会引用load_module方法，事实上这就是我们今天的主角：

![image-20221109234736216](E:\topics\Python高性能编码\statics\image-20221109234736216.png)

通过214，216行我们能发现，对pyx模块的loading过程实际上是先执行build_module，完成pyx -> c -> so的过程；

再通过**废弃的方法imp.load_dynamic**，给到模块名字符与so文件的路径，将目标导入的。。



### 不一样的python runtime能否导入呢？

![image-20221109235058711](E:\topics\Python高性能编码\statics\image-20221109235058711.png)



## Dlib Matrix解析



