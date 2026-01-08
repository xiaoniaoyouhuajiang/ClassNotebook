# C++教程

## 参考材料&项目

博客&文章

* [An overview of c++ stl containers](https://embeddedartistry.com/blog/2017/08/02/an-overview-of-c-stl-containers/)
* [MS的现代C++教程](https://learn.microsoft.com/en-us/cpp/cpp/?view=msvc-170)





## C++基础

* language constructs
  * 什么是左值右值
  * 
* memory manager



### 左值和右值

左值和右值最早来源于C的赋值表达式；

```C
E1 = E2;
```

此时左值在赋值表达式左边，它是对对象的引用（什么是对象， 简单理解就是内存中存储一块区域）；

上述表达式中；显然E1是左值，E2是右值，，那么"E1 = E2"呢？



再看一个例子：

```c++
// what we can do:
int n;
n = 1;

// what we can't do:
1 = n;
```

为啥第二个case不行呢？ -> 因为**字面量是个右值**。换句话说，因为”1“在内存中并没有被占位。



```cpp
int m, n;
m = n;
```

显然在这里，n**这个表达式**单独拿出来是左值；但在m=n这个表达式中，n是右值；



![image-20221203191417119](E:\topics\C++的强大\statics\image-20221203191417119.png)



![image-20221203163717077](E:\topics\C++的强大\statics\image-20221203163717077.png)

* 首先要了解什么是 [value categories](https://en.cppreference.com/w/cpp/language/value_category)

每个C++表达式都有两项独立属性：类型；值类别/值范畴，这个值范畴就是value categories，即上图中给到的几个类别。







#### lvalue

* 有标识符，可取地址
* non-const，可放在“=”运算符的左侧
* const
* ex:
  * 变量，函数名
  * 左值对应对象的成员
  * **返回**左值引用的表达式： ++x; x=1; cout << ' '
  * **字符串**字面量



#### rvalue

* 不能去地址

就是临时对象



#### xvalue（新的）







### language constructs

左值和右值第一次出现在《the tour of c++》是在71页，Essential Operations这个章节里，让我们快速过一遍。





## STL

编程者常用的容器有：

* 动态阵列
* 队列
* 栈
* 链接表
* 关联集合

C++的容器可被分为4种类型：

* 序列容器
* 序列容器适配器
* 关联式容器
* 无序关联式容器



### 序列容器

实际上就是线性表的实现，STL的序列容器类型包含：

* array代表静态连续数组
* vector代表动态连续数组
* forward_list代表单链表
* deque代表双端队列

