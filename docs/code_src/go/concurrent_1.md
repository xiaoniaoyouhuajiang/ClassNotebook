# 为什么并发/并行(concurrency)是困难的

## Race Conditions

```go
package main

import (
	"fmt"
)

func main() {
	var data int
	go func(){
		data++
	}()

	//执行判断前进行睡眠
	// time.Sleep(1 * time.Millisecond)

	if data == 0 {
		fmt.Printf("the value is %v.\n", data)
	}
}

```



这段代码的执行结果一共有3中可能。

通过在"if data == 0"判断语句前加入time.sleep能够改变的只有三种可能性的分布。



## Atomicity

原子操作（atomic operation）代表的是**在一个固定的上下文环境下**的**不可分解的操作**。

```go
i++
```

上面这个操作看似是原子操作，实际上我们能够将该指令分解为：

* 对i的地址进行访问
* 对i的值进行自增
* 存储新的i值

以一个单独进程中的执行序列角度去看这个指令（同时与其他goroutine没有通信关系），他是具备原子性的。

但如果以操作系统的角度看就不是了。



## Memory Access Synchronization

当一个程序是不确定的时候，对一段共享内存的访问的指令可以被称为临界断面-critical section。对之前的程序进行更改:

```go
var data int
go func() { data++}()
if data == 0 {
fmt.Println("the value is 0.")
} else {
fmt.Printf("the value is %v.\n", data)
}
```

在更新后的程序当中，有三个临界断面：

* goroutine
* if statement
* fmt.Printf statement（else分支当中的）

要解决这个问题，我们需要的是内存同步。

首先想到的是加锁：

```go
var memoryAccess sync.Mutex
var value int
go func() {
	memoryAccess.Lock()
	value++
	memoryAccess.Unlock()
}()
memoryAccess.Lock()
if value == 0 {
	fmt.Printf("the value is %v.\n", value)
} else {
	fmt.Printf("the value is %v.\n", value)
}
memoryAccess.Unlock()
```

然而实际上我们这样做仍然无法保证执行序列的一致性。



## Deadlocks, Livelocks, and Starvation

### deadlock

```go
package main
import (
	"fmt"
	"sync"
	"time"
)

type value struct {
	mu sync.Mutex
	value int
}

func main() {
	var wg sync.WaitGroup
	printSum := func(v1, v2 *value) {
		defer wg.Done()
		v1.mu.Lock()
		defer v1.mu.Unlock()

		time.Sleep(2*time.Second)
		v2.mu.Lock()
		defer v2.mu.Unlock()

		fmt.Printf("sum = %v\n", v1.value + v2.value)
	}

	var a, b value
	wg.Add(2)
	go printSum(&a, &b)
	go printSum(&b, &a)
	wg.Wait()
}
```

执行上述程序，将得到：

```shell
fatal error: all goroutines are asleep - deadlock!
```

观察执行流图：

<!-- image missing: image-20210221175604932 (Typora local cache) -->

​	

观察发现，在第一个goroutine执行完对a的访问后（defer了a的解锁操作）想要对b进行访问，但由于goroutine2已经在执行并给b打上了锁，此时由于两个协程互相阻塞且互不相让，整个程序永远都不会终结——我们碰到了死锁。

通过图标我们对整个执行流程有了一个清晰的了解，但我们需要一个更严谨的定义。

出现死锁的条件被称为：Coffman Condition

* 互相排斥

并行的进程们拥有对资源的单一访问权限

* 等待状态

一个并行中的进程拥有了一部分的数据资源，同时他也在等待一个额外的资源

* 不可抢占

一个被占用的资源的释放时机完全被相应进程控制

* 闭环等待

两个进程互相等待对方释放资源

<!-- image missing: image-20210221181623845 (Typora local cache) -->



如果我们能确保这些条件中的任何一条不为真，我们就有机会组织死锁的发生。



### Livelock
