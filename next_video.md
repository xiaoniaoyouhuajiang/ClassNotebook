# next video
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


### 了解容器与镜像

详情看《元工具》的容器章节

## 基于大语言模型开发助手机器人

## 性能工程：SIMD与多线程模型

### 多核背景下的算法



### 远程开发：使用frp连接自己电脑

### 使用docker结合lxc-rootfs做可迁移开发环境

## language binding


## 开发必备网络知识

## 软件性能工程
