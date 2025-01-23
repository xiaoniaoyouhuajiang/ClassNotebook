## 零拷贝的语境

很多人喜欢造概念，零拷贝这个词，我们经常能听到。

但是当我们坐下来严肃地讨论相关的内容时，我们必须得明确上下文。



从数据迁移的角度考虑，零拷贝不一定是真的“完全不需要进行内存的拷贝”，而是避免拷贝所有数据，从而占用了更少的资源（时间资源，或者是其他的）



在到更加具体的场景当中，我们使用json文件存储数据，当我们进行“零拷贝反序列化”，我们一定会把数据从磁盘中（假如json数据没有格式错误）load到一段内存中，但这离将数据转换为runtime（比如Python解释器中）的数据结构（某一个PyOjbect）还是有一定距离的，假如说，前面分配的内存中，某一个字段的值和PyObject中对应字段的值是完全一致的，那我们只需要让后者指向前者的内存地址，就可以去利用它。从这个角度来说，我们就算是避免了/完成零拷贝反序列化。



放到Rust语境下，这必然涉及到一个相关概念：生命期。现在，我们来展开



## 相关技术

### Cow(copy on write)

先贴个维基百科的链接：https://en.wikipedia.org/wiki/Copy-on-write



#### overview

通过维基百科，先建立一个基础的认识：

cow是一种资源管理技术，其内涵是只有当需要修改资源时，才会对原数据进行拷贝。

这很显然主要是为了节省资源。（还记得我们讲到UnionFs的时候涉及到的内容吗？没错，那也是一项实际应用）



#### Rust视角

假想存在这么一种类型，他一定很复杂，因为需要考虑到它生命期/所有权相关的设计。

简言之，就是可选所有权



#### 实例代码

```rust
#[test]
fn test_cow_with_copy() {
    let slice = [0, -1, 2];
    let mut input = Cow::from(&slice);
    println!("{:?}", slice.as_ptr());
    println!("{:?}", input.as_ptr());
    println!("{:?}", *&slice[1] as *const i32);
    println!("{:?}", *&input[1] as *const i32);
    abs_all(&mut input);
    println!("{:?}", slice.as_ptr());
    println!("{:?}", input.as_ptr());
    println!("{:?}", *&slice[1] as *const i32);
    println!("{:?}", *&input[1] as *const i32);
}

#[test]
fn test_cow_without_copy() {
    let slice = [0, 1, 2];
    let mut input = Cow::from(&slice);
    println!("{:?}", slice.as_ptr());
    println!("{:?}", input.as_ptr());
    println!("{:?}", *&slice[1] as *const i32);
    println!("{:?}", *&input[1] as *const i32);
    abs_all(&mut input);
    println!("{:?}", slice.as_ptr());
    println!("{:?}", input.as_ptr());
    println!("{:?}", *&slice[1] as *const i32);
    println!("{:?}", *&input[1] as *const i32);
}
```



#### 原理&优化点

Cow类型：

```rust
pub enum Cow<'a, B> where
    B: 'a + ToOwned + ?Sized,
{
    Borrowed(&'a B),
    Owned(<B as ToOwned>::Owned),
}
```





当Cow类型触发`to_mut`时，会有：

```rust
    #[stable(feature = "rust1", since = "1.0.0")]
    pub fn to_mut(&mut self) -> &mut <B as ToOwned>::Owned {
        match *self {
            Borrowed(borrowed) => {
                *self = Owned(borrowed.to_owned());
                match *self {
                    Borrowed(..) => unreachable!(),
                    Owned(ref mut owned) => owned,
                }
            }
            Owned(ref mut owned) => owned,
        }
    }
```



从而，当触发to_owned时，就会有全局内存分配器完成内存的拷贝，我们示例代码中，是一个slice，从而，最终会调用：

```rust
#[cfg(not(no_global_oom_handling))]
impl<T: Copy> ConvertVec for T {
    #[inline]
    fn to_vec<A: Allocator>(s: &[Self], alloc: A) -> Vec<Self, A> {
        let mut v = Vec::with_capacity_in(s.len(), alloc);
        // SAFETY:
        // allocated above with the capacity of `s`, and initialize to `s.len()` in
        // ptr::copy_to_non_overlapping below.
        unsafe {
            s.as_ptr().copy_to_nonoverlapping(v.as_mut_ptr(), s.len());
            v.set_len(s.len());
        }
        v
    }
}
```



实际上，Cow的内存布局是可以优化的：enum类型有一个tag占用了一个word（size_of::<usize()>）

对于一个slice，一定会有Length和Capacity（Owned类型，Borrowed也会有，只不过需要Padding），从而size_of::<std::borrow::Cow<str>>() == 4

但实际上，当Capacity为0，必定是borrowed，因此信息实际上存在一定的冗余，只需要使用3个word就可以实现Cow相应的功能。



### mmap

在我们使用candle运行trocr的推理代码时，我们必须将模型参数从文件中读取到内存，在candle的一般场景中，mmap系统调用是我们最常使用的加载模型文件的方法。



#### 使用场景&优势

一般这种场景下使用mmap（当然，严谨一点的，性能相关的原因还是需要诸位在工作系统上用fio等存储基准进行测试）:

* **COW**：多个进程访问同一个仅可读的文件，这种情况下，mmap文件共享同一物理内存页，将节省很多内存开销;如果是某一个进程要修改文件，则单独创建拷贝
* 进程内通信：使用mmap对一个文件进行读写，对mmap内存区域使用同步原语来完成通信同步
* **无多余拷贝**：read和write系统调用，必须通过用户态分配的buffer来进行拷贝（mmap不需要从内核态buffer到用户态buffer的拷贝）
* **性能**：读写memory-mapped文件就像访问内存一样简单，没有系统调用 -> 没有上下文切换导致的时间开销
* 内存操作频繁的时候：不用对buffer进行对齐

其他可以参考这一篇内容：https://stackoverflow.com/questions/258091/when-should-i-use-mmap-for-file-access



反例：

* pipes/ttys是特殊的文件类型，mmap不能使用



看了上述介绍你可能会觉得，对于并发的DL模型推理来说，mmap十分适合。

我收集了一些实际场景的讨论/经验贴：

> So it doesn't create an extra copy in RAM and lives in the kernel page cache happily, loading instantly on subsequent runs.

* https://github.com/ggerganov/llama.cpp/issues/91



#### 原理

`mmap` 和 `read` 是两种不同的文件访问方式，它们在内核中的行为有显著差异，尤其是在内存拷贝方面。以下是详细解释：

------

##### 1. **`read` 系统调用的内存拷贝行为**

- **用户空间与内核空间的分离**：在 Linux 中，用户空间和内核空间是隔离的，用户程序不能直接访问内核空间的数据。
- **`read` 的工作流程**：
  1. **内核缓冲区的分配**：当调用 `read` 时，内核会先在**内核空间**中分配一个缓冲区，用于从磁盘读取文件数据。
  2. **数据从磁盘读取到内核缓冲区**：内核通过文件系统将文件数据从磁盘读取到内核缓冲区。
  3. **数据从内核缓冲区拷贝到用户空间**：内核将数据从内核缓冲区拷贝到用户空间提供的缓冲区（即 `read` 的第二个参数 `buf`）。
- **内存拷贝的开销**：`read` 需要进行两次数据拷贝：
  - 第一次：从磁盘到内核缓冲区。
  - 第二次：从内核缓冲区到用户空间缓冲区。
    这种额外的拷贝操作会增加 CPU 和内存的开销，尤其是在处理大文件时。

------

##### 2. **`mmap` 系统调用的内存映射行为**

- **内存映射的核心思想**：`mmap` 通过将文件直接映射到进程的虚拟地址空间，避免了用户空间和内核空间之间的数据拷贝。
- **`mmap` 的工作流程**：
  1. **建立虚拟内存映射**：当调用 `mmap` 时，内核会在进程的虚拟地址空间中创建一个映射区域，将该区域与文件关联。
  2. **按需加载（Lazy Loading）**：文件数据并不会立即加载到内存中，而是通过**缺页中断（Page Fault）**机制按需加载。
     - 当进程访问映射区域的某个页面时，如果该页面尚未加载到内存，会触发缺页中断。
     - 内核处理缺页中断，将文件数据从磁盘读取到物理内存，并更新页表，将虚拟地址映射到对应的物理页。
  3. **直接访问文件数据**：进程可以直接通过指针访问映射区域，数据从磁盘到用户空间的过程不需要额外的拷贝。
- **内存拷贝的开销**：`mmap` 避免了用户空间和内核空间之间的数据拷贝：
  - 数据从磁盘直接加载到物理内存，并通过页表映射到用户空间。
  - 用户程序可以直接访问映射区域，无需额外的拷贝操作。

------

##### 3. **内核行为的对比**

- **`read` 的内核行为**：
  - 需要在内核空间分配缓冲区。
  - 数据从磁盘到内核缓冲区，再从内核缓冲区到用户空间，涉及两次拷贝。
  - 拷贝操作由内核完成，增加了 CPU 和内存的开销。
- **`mmap` 的内核行为**：
  - 不需要额外的内核缓冲区。
  - 数据从磁盘直接加载到物理内存，并通过页表映射到用户空间。
  - 用户程序可以直接访问映射区域，避免了额外的拷贝操作。





### 擦除

#### dyn：类型擦除

首先了解动态派发和静态派发：

```rust
trait A {
    fn do_something(&self);
}

struct Type1;
impl A for Type1 {
    fn do_something(&self) {
        println!("Type1 doing something");
    }
}

struct Type2;
impl A for Type2 {
    fn do_something(&self) {
        println!("Type2 doing something");
    }
}

fn use_trait<T: A>(item: T) {
    item.do_something();
}

fn main() {
    let t1 = Type1;
    let t2 = Type2;
    use_trait(t1);
    use_trait(t2);
}
```



动态派发：

```rust
trait A {
    fn do_something(&self);
}

struct Type1;
impl A for Type1 {
    fn do_something(&self) {
        println!("Type1 doing something");
    }
}

struct Type2;
impl A for Type2 {
    fn do_something(&self) {
        println!("Type2 doing something");
    }
}

fn use_trait(item: &dyn A) {
    item.do_something();
}

fn main() {
    let t1 = Type1;
    let t2 = Type2;
    use_trait(&t1);
    use_trait(&t2);
}
```



包含dyn关键字声明参数的函数实际在运行时决定了分派的函数，通过dyn，我们可以构造Trait objects，从而我们可以实现：

```rust
struct Service{
    backends: Vec<Box<dyn Backend>>
}
...
let mut backends = Vec::new();
backends.push( Box::new(PositiveBackend{}) as Box<dyn Backend>);
backends.push( Box::new(NegativeBackend{}) as Box<dyn Backend>);
```



当然，这种抽象的代价伴随着性能的损失(类似CPP的虚表，map[method_name])，可以看一下相关的微基准测试：https://medium.com/digitalfrontiers/rust-dynamic-dispatching-deep-dive-236a5896e49b



#### Yoke：生命期擦除

Yoke模块的设计，可以看看https://github.com/unicode-org/icu4x/blob/main/utils/yoke/design_doc.md。

> Similar to how `dyn` enables Rust programs to perform "type erasure": turning compile-time types into "erased" runtime ones, `Yoke` enables Rust programs to perform the analogous "lifetime erasure": turning specific compile-time lifetimes into "erased" runtime ones. This means we don't need lifetime parameters to track data ownership, and that we can carry reference-counted data that can be safely dropped from a cache.

咋一听这个还感觉挺吓人的，虽然这个有好处，比如能够让我们利用cache。



> `Yoke<Y, C>` allows one to "yoke" a zero-copy deserialized object (say, a `Cow<'a, str>`) to the source it was deserialized from, (say, an `Rc<[u8]>`), known as a "cart", producing a type that looks like `Yoke<Cow<'static, str>, Rc<[u8]>>` and can be moved around with impunity.



##### 困境

生命期就是困境，参考exp代码中的zero_copy.rs，使用Yoke的一个前提是cart实现了`stable_deref_trait`



```rust
#[cfg(feature = "stable_deref_trait")]
unsafe impl stable_deref_trait::StableDeref for Mmap {}
```





## 零拷贝反序列化







