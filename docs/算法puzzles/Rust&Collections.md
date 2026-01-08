# Rust与数据集合(Collections)

## rust本身

### 困境

在rust中实现各种各样的容器是一个复杂的问题。



#### 概念与问题

##### "根本问题"

对于笔者，好奇的点在于，**切实**地搞清楚：

* 深入地学习数据结构，主要是学些什么(container/collection or algorithm)
* 开发中的问题对所学知识有怎样的依赖
* 能否通过数据结构的知识做出更好的软件



##### 如果一定要谈到“要素”

我没有考过研，但我听说考研的资料里会提到数据结构的三要素，一些资料说是：

* 逻辑结构
* 存储结构
* 算法



##### Abstract data type





#### 生命期

通常我们需要抽象出Node这样的概念，我们需要对他们进行动态内存分配，从而就规避不了节点的内存分配和释放，



#### 所有权问题

```rust
#[test]
fn test_collection_lifetime() {
    let mut v = vec![1i32, 2, 3, 4];
    let tem = v.get(2);
    v[2] += 1;
    // 上述代码不会出错，因为非词法生命周期的存在：
    // https://stackoverflow.com/questions/50251487/what-are-non-lexical-lifetimes
    // 所以想要它报错就注释掉下面的代码
    // println!("{:?}", tem);
}
```



#### 实例：循环引用



### 技术&工具

#### Arc&RefCell





### BTree的正确实现？



#### Arc对象

考虑这么一个需求：

sharable trees

> So I'd like to implement a tree data structure similar to how git works. So the tree consists of nodes where each can have N children. Once initialized, the nodes are immutable. Any changes to the tree would be done by making new parent nodes that point to new children where applicable. The new nodes will reuse the children for nodes that are unchanged.



#### rpds









