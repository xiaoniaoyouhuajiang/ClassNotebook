# 系统数据采集道与术
本文档用于记录系统（主要是linux）的数据采集方案，包括:
* OS内可以获取的子部件数据（/proc, intel的RAPL）
* 性能计数器（perf event, PAPI, hwloc等能力）
* 通过DBI获取的指令级别的数据（比如reuse distance）
* bmc获取的数据（通过ipmitool或其他专用通道，不细究）

主要是记录工作中见到的或者使用到的技术，前两点可以通过psutil以及perf event获取，路径已打通

## linker插入
基于PRELOAD中的链接库，在运行时替换elf文件的一些特别的函数，从而能够实现一些钩子，通过钩子去在运行时完成profiling，分析工作。

LLVM相关的元工具中介绍过类似的功能；核心是基于LD_PRELOAD进行偷梁换柱;基于这种方法完成的库工具可称为：`interposition libraries`（基于`LD_PRELOAD`, `DYLD_INSERT_LIBRARIES`）

### 动态库劫持
"劫持"可以理解为劫持者冒充被劫持者的某些函数符号。这么做的目的是在不更改实例程序的elf情况下，改变被劫持符号的行为。

> 链接阶段劫持

该方法不是重点（因为它其实是一种白盒方法，适用性不算广）

> 运行阶段劫持

更改LD_PRELOAD环境变量，可以控制动态库的加载顺序，将劫持者代码所编译的动态库加入该环境变量中，使其提前被加载，后续目标进程进行程序调用，会优先在劫持者动态库中检索，从而实现劫持。

**演示见 insert_test**

这种方法有较大的局限性，在于运行时链接库的符号必须是已知的

代码仓：github.com/HPCToolkit/libmonitor.git
测试钩子：icl.utk.edu/~mucci/monitor

首先最新的代码地址是：
`gitlab.com/hpctoolkit/hpctoolkit/`

HPCtoolkit官方已经将libmonitor合入到主代码仓的模块中；

整个工具的运行逻辑：
* export LD_PRELOAD=/path_to_build/libmonitor.so:/path_to_build/tests/monitor_hook.so
* 

### 注入式方法实现监控
`hpctoolkit`中的组件`hpcrun`就是通过`LD_PRELOAD`来实现在运行时的代码中插入profiling code：

```shell
hpcrun app arg
```
hpcrun会使用异步采样的方法来衡量程序的在CPU上的时间，并且获取每个线程的`call path profile`

## dbi-采集

## ebpf
eBPF全称为`extended Berkeley Packet Filter`，简言之，他可以：
* 扩展内核
* 

### 如何使用该能力
1.用户编写eBPF程序，使用eBPF汇编或者特定的C语言进行开发；
2.使用LLVM/CLang编译器将开发件编译成eBPF字节码；
3.通过bpf系统调用将字节码加载到内核；

ebpf.io是ebpf技术官网，打开后能看到醒目的`Dynamically program the kernel for efficient networking, observability, tracing, and security`
而官网中提到的能力，对于我而言最重要的是：
* observability: 可以自定义`metric`，从各种地方生成可见的数据结构
* tracing & profiling: 将eBPF程序附加到跟踪点，内核以及用户应用程序探针点上，分析系统性能问题

