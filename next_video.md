# next video
## 视频改进点
制作视频的时候，需要考虑这些内容：
* 观众视角下的内容重要性分布,每个视频规划出重点，次重点
* 视频外壳（资源公布/片头/场景切换/内容分段）
* 垂直领域（编程，编程语言，C++ AND Python，底层/硬核）：特别是C++和编程语言/Python，这两个起码要沾边，底层感觉有可能是流量关键
* 扩展边界（创建微信群）
* 整活视频（视频的新颖性，）
* 系列的连续性
* 个人原则：简单暴力

简言之，垂直关键词是：<编程语言>;编程;<底层软件>(GDB/CPython/);<新颖软件>(/gpt)

创作原则：要是干货/要有意义

## 使用平板写文档（已完成）
备注：**使用时最好将termux设置为平板的自启动应用**
### 在markdown文档中快速插入截图
涉及的几项关键技术：
* termux对平板资源的访问设置，需要使用命令`termux-setup-storage`，便可以访问`/storage/emulated/0`，从而可以访问`/storage/emulated/0/DCIM/Screenshots`
* 关键一步，为了方便引用，`ln -s .. target`
* code-server中用md语法插入即可

![test](/screen_shot/Screenshot_20230728_011756_Edge.jpg)

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
![draw-io](/screen_shot/Screenshot_20230727_161615_Edge.jpg)

### 更深入地了解Termux
访问wiki.termux.com/wiki/FAQ

## 开发环境迁移
### 用移动硬盘结合Linux iso创造移动开发环境（已完成）
* 简述目的
    * 随身携带的开发环境
    * 简述原理
* 硬件准备
    * 移动硬盘/磁盘盒+SSD
    * 一块20G以上的普通U盘（可选）
* 软件准备
    * virtual-box
    * 需要安装的linux iso
    * disk-genius
    * disk-info（可选）
    * rufus（可选）
* 流程

## 语言的模块系统

### python的import机制(已完成)
* import基本方法
* 相对导入和绝对导入

### 有网可以不用下载直接import？详解importlib
* 如何通过http import（重点）
* importlib的机制（重点）

### Python知名项目的模块/文件结构分析
* 编程语言的模块系统
* setup.py如何"编译"出.so文件
* 混合项目的文件组织结构

### Cython项目的打包与发布
* Python项目的文件打包与发布规范
* Cython文件的导入，包装，组织结构
* Cython释放GIL

### 了解容器与镜像
关键词：
* 开发环境；容器技术
* crun
* 最小化镜像体积

详情看《元工具》的容器章节

## 基于大语言模型开发助手机器人

## 并发与并行

### 异步编程库asyncio的分析

### asyncio vs uvloop

### 性能工程：SIMD与多线程模型

### 多核背景下的算法



### 远程开发：使用frp连接自己电脑

### 使用docker结合lxc-rootfs做可迁移开发环境

## language binding

## 开发必备网络知识

## 软件性能工程

## 大片系列：《一个知识区UP主的自白》
