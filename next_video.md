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

### 了解容器与镜像
详情看《元工具》的容器章节

### 用Bootable USB结合Linux iso创造移动开发环境

### 远程开发：使用frp连接自己电脑

### 使用lxc-rootfs做可迁移开发环境

## 开发必备网络知识

## 软件性能工程

## 更深入地了解Termux
### FAQ
访问wiki.termux.com/wiki/FAQ