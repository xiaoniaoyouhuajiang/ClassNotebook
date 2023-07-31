# next video
## 使用平板写文档
备注：**使用时最好将termux设置为平板的自启动应用**
### 在markdown文档中快速插入截图
涉及的几项关键技术：
* termux对平板资源的访问设置，需要使用命令`termux-setup-storage`，便可以访问`/storage/emulated/0`，从而可以访问`/storage/emulated/0/DCIM/Screenshots`
* 关键一步，为了方便引用，`ln -s .. target`
* code-server中用md语法插入即可

![test](/storage/dcim/Screenshots/Screenshot_20230728_011756_Edge.jpg)

### 使用git做版本管理
添加ssh公钥：
```shell
ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
cat ~/.ssh/id_rsa.pub
```

一般的工作流如下：
* git config --global user.email "xx"
* git config --global user.name "xx"
* git add .
* git commit -m "xx"
* git pull origin main
* git push origin
中间出现问题记得要授权

### 使用drawio工具画图
![draw-io](/storage/dcim/Screenshots/Screenshot_20230727_161615_Edge.jpg)

## 开发环境迁移

### 用Bootable USB结合Linux iso创造移动开发环境

### 通过bocker了解docker

#### 了解btrfs
简言之是"Better FS",具备这些特性:
* 

### 深入介绍容器技术
了解Docker我认为最终要的几个关键词：
* Namespaces
* 联合文件系统
* runc
* linux control group
* 内核能力

#### Namespaces
Docker使用linux namespace技术来实现容器间的资源隔离

|Namespace|syscall|隔离内容|
|---|---|---|
|PID|CLONE_NEWPID|隔离用户的进程|
|UTS|CLONE_NEWUTS|使每个容器有独立的hostname和domain name，使其在网络上可以被视为独立节点|
|IPC|CLONE_NEWIPC|保证容器间的进程交互，信号量，消息队列，共享内存的相互隔离|
|network|CLONE_NEWNET|实现网络隔离，每个net namespace有独立的network devices,ip addresses, ip routing tables,/proc/net目录|
|Mount|CLONE_NEWNS|每个namespace的容器在/proc/mounts的信息中只包含namespace的mount point|
User|CLONE_NEWUSER|允许每个容器有不同的user和group id

一个问题：要**区分不同的shell环境，关键是哪一个namespace的隔离在起作用（系统变量）**

#### 联合文件系统
unionFS是一种分层，轻量级并且高性能的文件系统，它对文件系统的修改作为一次次提交来层层叠加，同时可以将不同目录挂载到同一个虚拟文件系统下。我们知道Docker镜像可以通过分层来继承，不同的Docker容器可以共享基础文件系统层，再加上自己独有的改动层，大大提高存储效率。Docker支持的联合文件系统包括：
aufs,btrfs,vfs,devicemapper, overlay2

联合文件系统的核心特性：
* copy-on-write

要查看当前docker所使用的文件系统可以：
```shell
docker info | grep 'Storage Driver'
```
Docker容器存在的一个很大问题是：镜像体积在多次提交后变得过于膨胀，该怎么去面对和解决这个问题呢？
首先，为什么一般我们在交互式窗口中使用yum这类的包管理器仅仅是装了一个小工具或者库之后，体积的膨胀却超出了软件体积本身呢？

大家先得掌握一个命令:
```shell
docker istory <image-id>
```
这个命令能够看到镜像的提交历史，其中SIZE那一列的增长最终都会作用到镜像本身，因为在某一个layer提交之后的layer，其删除的磁盘空间实际仍在之前的layer被保留着。

那如何解决这个问题？我们给自己设置一个目标：制作一个满足自己需求的最小容器，其实有几种方法可以实现这个目标：
* from scratch
* 

#### runc
容器运行时（container runtime）是

#### data container


### 远程开发：使用frp连接自己电脑

### 使用lxc-rootfs做可迁移开发环境

## 开发必备网络知识

## 软件性能工程

## 更深入地了解Termux
### FAQ
访问wiki.termux.com/wiki/FAQ