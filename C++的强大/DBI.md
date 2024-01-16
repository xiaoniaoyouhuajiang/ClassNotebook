# Dynamic binary instrumentation
讲解关于动态打桩工具的道与术

## 概述

### 参考的材料

* Optimizing performance Using Dynamic Code Generation
* [Optimizing Performance Using Dynamic Code Generation](https://mediatum.ub.tum.de/doc/1614897/1614897.pdf)



### 是什么
已知的比较有名气的动态打桩工具有：
* pin
* valgrind
* dynamorio
* qemu

比较新的工具
* triton
* qbdi

### 为什么
* 更精细的调试技术
* 深化对CPU执行指令过程的理解
* 最大化分析程序运行的状态：性能、能耗

### 一些应用
#### Dynamic Binary Visualization
youtube上有相关的介绍，略


### 怎么做

#### 用QBDI上手实践

准备一个简单的动态库，比如实现一个算法的c++代码，将代码编译成so文件：

```shell
g++ -c -fPIC demo.cpp -o demo.o
g++ -shared -Wl,-soname,mylib.so -o mylib.so demo.o

# 查看so中的动态符号
nm -D mylib.so
```

#### 了解QBDI的原理

#### LLVM-BASED优化理论基础
通俗来说，程序执行本身的执行有两种策略

在程序执行时的编译成为Just In Time compilation。在程序执行之前则称为Ahead of TIME compilation。然而，有一种将机器码转移成高级别代码表示的技术，称为反编译/lifting，将机器码转换为相同的或者是不同的CPU架构一般称为binary rewriting，



##### 透明动态重写



![image-20240114185835248](/statics/image-20240114185835248.png)



#### 了解LLVM-BASED的二进制优化工具：Rellume



