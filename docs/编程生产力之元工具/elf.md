# elf可执行文件相关

## 关于portable

### 意义
* 简单，暴力（表面上）
* 通过合理的牺牲忘掉部署的烦恼
* 在实现上的成本（系统所具备的条件/构造可移植包）做权衡

**注意：由于我的大部分开发内容都在linux上，很多实践操作切换到windows系统下需要自己去探索尝试**



### 关于glibc和musl


## linux分发的最终武器：exodus

### all in one file
```bash
exodus --tarball drrun --output drrun.tgz

scp drrun.tgz user@xx.xx.xx.xx:/home/drrun.tgz

# 另一台计算机
tar -zxf /home/drrun.tgz
```

### 什么是relocatable

我认为等同于`position independent`，和路径无关的代码并不依赖其在内存中的位置



### 原理

下图中的`bin/grep`可执行文件便是exodus产物的输出形式

通过bundles下的hash目录去重现动态链接的寻路过程，而每一个elf文件最终都已conteng-based哈希值的形式存储在/data目录下

```shell
/home/sangaline/.exodus/
├── bin
│   └── grep -> ../bundles/3124cd96.../usr/bin/grep
├── bundles
│   └── 3124cd96...
│       ├── lib64
│       │   └── ld-linux-x86-64.so.2 -> ../../../data/dfd5de26...
│       └── usr
│           ├── bin
│           │   ├── grep
│           │   ├── grep-x -> ../../../../data/7477c1a7...
│           │   └── linker-dfd5de26...
│           └── lib
│               ├── libc.so.6 -> ../../../../data/6d0e1d45...
│               ├── libpcre.so.1 -> ../../../../data/a0862ebc...
│               └── libpthread.so.0 -> ../../../../data/85cb56a5...
└── data
    ├── 6d0e1d45...
    ├── 7477c1a7...
    ├── 85cb56a5...
    ├── a0862ebc...
    └── dfd5de26...

8 directories, 13 files
```


另一方面，如果系统中有：

* C编译器
* musl libc/diet lib

exodus会编译出一个静态链接的launcher



我们先看下如果没有libc，可执行文件会是什么样的：

```shell
#! /bin/bash

current_directory="$(dirname "$(readlink -f "$0")")"
executable="${current_directory}/./grep-x"
library_path="../../lib64:../lib64:../../lib:../lib:../../lib32:../lib32"
library_path="${current_directory}/${library_path//:/:${current_directory}/}"
linker="${current_directory}/./linker-dfd5de2638cea087685b67786050dcdc33aac7b67f5f8c2753b7da538517880a"
exec "${linker}" --library-path "${library_path}" --inhibit-rpath "" "${executable}" "$@"
```

需要明白一个点是，在构造elf文件的过程中，linker这个elf文件的路径会被**硬编码**到header当中，所以需要使用bash来重新指定新的linker，也就是实现一个'wrapper'，这一块的操作，和nix的实现思路有些相似。

可以看到，launcher会首先构造`LD_LIBRARY_PATH`的完整路径，还有可执行文件以及linker的路径。如果使用上述方法将python打包并且移植到新的系统上，很有可能会出现问题：
`Fatal python error: init_fs_encoding: failed to get Python codec of the filesystem encoding`

这个问题出现的原因是：python找不到encodings这个模块，所以无法完成`init_fs_encoding`这个过程，换句话说，**python的执行对其所依赖的文件系统/结构有要求**，这个问题我目前还没找到比较好的解决方法，最好的方式就是看


#### 局限性
大体来说，局限性包括这些：
* 由解释器启动的文件：比如`bash`，`python`，`perl`等，毕竟它们不是elf文件
* CPU架构问题，这个很好理解，属于工具本身就不需要cover的部分，实在需要运行就需要虚拟机，比如QEMU
* glibc和内核版本不兼容：如果编译对象本身所依赖的glibc的版本比目标系统要低，可以在构建系统上使用`file /usr/bin/rm`之类的命令看到该系统所支持的最小版本，诸如`for GNU/Linux 3.2.0`了解到系统所支持的最小的内核版本，出发问题的时候，会出现`FATAL: kernel too old`，这个问题的解决方法就是在较低版本的系统上构建
* 依赖驱动的libs:由于exodus会将所有依赖库都包含到bundle中，随之而来的问题是：为特定驱动程序编译的库只会在拥有相同驱动程序的机器上工作。比如libGLX_indirect.so会根据目标设备来选择链接的对象是`libGLX_mesa.so`或者是`libGLX_nvidia.so`



## build-once run-anywhere: Cosmopolitan

项目地址：https://github.com/jart/cosmopolitan


## AppImage
Appimage是一个开源项目，也是一个打包格式。


## Python的分发方案：
### pyinstaller

应用的打包方案

缺陷：并不能将解释器整个迁移，只能迁移应用

### python-AppImage
链接地址：github.com/niess/python-appimage

### windows

windows下Python有embeddedable方案

### linux
关键是要解决:

* 静态链接
* relocatable问题



#### 最简方案：pypy

pypy当前对于c-extension的支持已经有了很大提升，正如我们之前所说：**python不仅是Cpython**

在linux下使用pypy来迁移应用除了能享受portable的好处之外，还有就是性能的提升。

有一些c-extension的代码在构建的时候会遇到一些问题，这种时候一般切换安装版本可以解决。



#### nix

略（可以参考nix的章节）

#### 使用pyoxidizer完成静态链接
首先，linux下产生一个完全静态链接的Python二进制文件是可行的，使用pyoxidizer需要一个`x86_64-unknown-linux-musl`去使用`musl libc`去进行构建

