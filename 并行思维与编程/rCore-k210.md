# rCore-k210

本教程主要讲在ubuntu系统下如何用k210跑rust构建的系统rCore，其中包括的内容有：

* 硬件准备(k210 + USB线)
* rust环境安装
* qemu环境安装(optional)
* k210固件toolchain安装 + 开发环境搭建(optional)
* 通过kflash烧录一个demo固件到k210(optional)
* 将ch1-dev分支的固件烧录到开发板



## 一些坑

toolchain官网没有ubuntu的版本，需要去github release处下载：
https://github.com/kendryte/kendryte-gnu-toolchain/releases

```shell
// 解压后除了配置环境变量，还需要配置LD_LIBRARY_PATH，否则编译会报错：

export PATH=$PATH:/opt/riscv/bin:/opt/kendryte-toolchain/bin
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/kendryte-toolchain/bin
export LD_LIBRARY_PATH

```



cd build之后，如果之前没有成功配置(cmake有error)，先把build下所有文件删掉，再重新：

```shell
cmake .. -DPROJ=hello_world -DTOOLCHAIN=/opt/kendryte-toolchain/bin

python3 -m pip install kflash
sudo usermod -a -G dialout $(whoami)

sudo -E python3 -m kflash -p /dev/ttyUSB0 -t hello_world.bin

```



rCore构建的帮助命令

```shell
// 查看rust已有的toolchain以及target
rustup show

// 在特定目录下切换rust的toolchain
rustup override set nightly-2024-05-01-x86_64-unknown-linux-gnu

// 现在本地分支并将其上游分支映射为chi-dev
git checkout -b ch1 origin/ch1-dev
```

