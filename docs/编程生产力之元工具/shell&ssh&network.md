# 我的shell实践

## Python含量最高的shell:xonsh

### 使用xonsh

### 使用xonsh构建执行系统

## libc

### libc在系统当中充当的角色
* libc实现了诸如`strcpy()`的`标准C函数`和`getpid()`这样的`系统调用`;
* 在开发应用程序的过程中，你不能直接使用系统调用：因为这些函数调用不会被linker识别，你必须使用架构特定的汇编代码块，才能进入系统内核，但是`libc`会为你提供这样的调用能力，而很多native语言的编译器在编译过程中就将程序链接了glibc，比如go, rust；而python，本身就链接了libc
* linux中，提供POSIX API的是内核和libc的组合；
* 除了系统调用之外，线程（pthread）和一些时间相关的功能也是基于libc

综上所述，大多数计算机系统要能正常运行，必须得有一个合适的libc库

### 关于glibc和musl libc
Alpine作为最轻量的linux分发版本，所使用的libc库是musl，他和glibc：
* Linux + glibc是最常见的组合，但实际上两者并没有绑定关系
* 安卓不可以直接运行"典型的"linux elf文件，是因为大多数elf文件会链接基于glibc的libc.so，而安卓用于商业用途，不可以使用基于LGPL协议的glibc库，所以安卓使用的是一套基于bionic的运行库(题外话，termux本质就是一个linux容器，上面自带的软件是使用bionic库重新移植后)
* 提到库依赖的问题，为啥主流系统坚持动态依赖库：1.某些开源库的协议只允许自身被动态链接，否则就必须得开源；2.程序不可能静态链接所有库，最基础的即系统提供的基础库


## ssh和shell

### xxh
`Bring your favorite shell wherever you go through the ssh`

每当我们使用ssh连接一台新的机器，我们最习惯的shell配置都会失效，通过xxh你可以解决这个问题，将最喜欢的shell携带到任何地方。

特性：
* 可迁移：提供了一个可迁移的shell，通过文件就可以将功能迁移到新的主机上
* 密封性：将`~/.ssh`目录删除，系统上就像不曾存在过
* 丰富的shell支持：包括xonsh, shell, fish, zsh, osquery

#### 演示

```shell
# 通过网络安装xxh（见下文）
...

# 通过xxh repo安装想要使用的shell,以xonsh为例
xxh +I xxh-shell-xonsh

xxh [ssh arguments] [user@]host[:port] +s xonsh
```


#### xxh实现机制
看一下linux可移植二进制的安装方法:
```shell
mkdir ~/xxh && cd ~/xxh
wget https://github.com/xxh/xxh/releases/download/0.8.12/xxh-portable-musl-alpine-Linux-x86_64.tar.gz
tar -xzf xxh-portable-musl-alpine-Linux-x86_64.tar.gz
./xxh
```
这里我们解释下，xxh提供的portable是如何

甚至于xxh有独立的AppImage包，可以通过下面方式直接安装使用：
```shell
mkdir ~/xxh && cd ~/xxh
wget -O xxh https://github.com/xxh/xxh/releases/download/0.8.12/xxh-x86_64.AppImage
chmod +x xxh && ./xxh
```

### 使用ssh连接一个自定义shell
