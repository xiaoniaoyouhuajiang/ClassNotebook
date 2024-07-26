# 用户态NVM驱动
vroom是使用Rust实现的用户态的驱动程序，本身作为一个Proof of concept
跟这个相关的程序还包括redox操作系统的nvme驱动：
gitlab.redox-os.org/redox-os/drivers/-/tree/master/storage/nvmed

## 项目初衷
传统的Linux IO API或者是异步API没办法实现最低延迟或者最高吞吐量（因为它们的iO是基于内核的IO路径），而SPDK则提供了解决该问题的一套方案。vroom和它类似，但使用rust实现。

## 背景介绍
PCIe Gen 5.0 NVMe SSDs,理论上该设备可以做到一百万IOPS，而Linux的常规文件读写API，使用了pread和pwrite,其实没有办法真正发挥出它们的能力，看论文cidrdb.org/cidr2020/papers/p16-haas-cidr20.pdf,标题是如何在DBMS中最大化地利用NVMe

首先我们梳理出Linux OS可能带来的影响效率的因素：
* OS buffering(page cache, O_DIRECT)
* io interface(pread/pwrite, libaio, io_uring)
* file_system（ext4,btrfs,xfs,f2fs，对于直接写块设备而言）