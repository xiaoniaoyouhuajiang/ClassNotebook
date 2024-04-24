# 系统数据采集道与术
本文档用于记录系统（主要是linux）的数据采集方案，包括:
* OS内可以获取的子部件数据（/proc, intel的RAPL）
* 性能计数器（perf event, PAPI, hwloc等能力）
* 通过DBI获取的指令级别的数据（比如reuse distance）
* bmc获取的数据（通过ipmitool或其他专用通道，不细究）

主要是记录工作中见到的或者使用到的技术，前两点可以通过psutil以及perf event获取，路径已打通

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

