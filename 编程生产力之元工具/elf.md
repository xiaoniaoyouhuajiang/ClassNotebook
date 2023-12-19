# elf可执行文件相关
## linux分发的最终武器：exodus

### all in one file
```bash
exodus --tarball drrun --output drrun.tgz

scp drrun.tgz user@xx.xx.xx.xx:/home/drrun.tgz

# 另一台计算机
tar -zxf /home/drrun.tgz
```

### 什么是relocatable

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

可以看到，launcher会首先构造`LD_LIBRARY_PATH`的完整路径，还有可执行文件以及linker的路径，



## Python的分发方案：
### windows
windows下Python有embeddedable方案

### linux
关键是要解决