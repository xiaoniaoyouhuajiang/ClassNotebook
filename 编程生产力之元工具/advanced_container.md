## 深入容器技术


## 复杂环境的容器技术

### sarus
sarus架构：
![sarus架构](../statics/architecture.svg)
注意看OCI Bundle中包含哪些信息

#### 容器镜像的处理
将tar文件导入为"可管理的oci bundles"依赖的是`Skopeo`，一个泛用性很强的镜像文件处理工具，最终转换为oci镜像路径（一种标准化的表达）。

### apptainer

#### 为何使用apptainer

下面内容摘自https://researchcomputing.princeton.edu/support/knowledge-base/apptainer#apptainer

* [可复现性，一个bundles包含所有软件依赖]An Apptainer image bundles an application together with its software dependencies, data, scripts, documentation, license and a minimal operating system. Software in this form ensures reproducible results. In fact, a DOI can be obtained for an image for publications. As software dependencies continue to grow in complexity, this approach becomes more attractive.
* [所有内容被包含在一个文件]Apptainer images are stored as a single file which makes them easily shareable. You can host your images on the Singularity Cloud Library for others to download. You could also make it available by putting it on a web server (e.g., tigress-web) like any other file.
* [跨系统]An Apptainer image can run on any system that has the same architecture (e.g., x86-64) and binary file format for which the image was made. This provides portability.
* [glibc的ABI问题]Software built on one system with a certain glibc version may not run on a second system with an older glibc. One may also encounter issues with ABI compatibility, for example, with the standard C++ library. These issues can be solved with Apptainer by building the image with an updated base operating system and the corresponding libraries and tools.
* [更接近硬件]Apptainer can be used to run massively-parallel applications which leverage fast InfiniBand interconnects and GPUs. These applications suffer minimal performance loss since Apptainer was designed to run "close to the hardware".
* Bring Your Own Software (BYOS). That is, you don't have to ask the system adminstrators if they are willing to install something for you. You can install whatever you want inside the image and then run it. This is because there is no way to escalate priviledges. That is, the user outside the container is the same user inside so there are no additional security concerns with Apptainer containers.

#### 

#### 执行MPI任务
内容摘自https://apptainer.org/docs/user/main/mpi.html#

apptainer执行MPI任务有两种模式，分别是"Hybrid"和"bind"，区别在于镜像中是否包含MPI软件栈。

hybrid中容器外和容器内都会有运行容器的软件栈，当使用`mpiexec`（或者其他launcher）时，容器外部的mpi进程将会和内部的代码协同工作。整个工作流如下：

![work-flow](../statics/apptainer_mpi_flow.jpg)



### CDI
> CDI is an open specification for container runtimes that abstracts what access to a device, such as an NVIDIA GPU, means, and standardizes access across container runtimes. Popular container runtimes can read and process the specification to ensure that a device is available in a container. CDI simplifies adding support for devices such as NVIDIA GPUs because the specification is applicable to all container runtimes that support CDI.CDI also improves the compatibility of the NVIDIA container stack with certain features such as rootless containers.

Container Device Interface (CDI) 是一个提议的标准，它定义了如何在容器运行时环境中向容器提供设备。这个提议的目的是使得设备供应商能够更容易地将其设备集成到 Kubernetes 集群中，而不必修改 Kubernetes 核心代码。

CDI 插件通常负责：

配置设备以供容器使用（例如，分配设备文件或设置必要的环境变量）。
在容器启动时将设备资源注入到容器中。


#### cuda container
GPU相关的软件栈比较复杂，使用了CUDA技术的软件在部署时通常会面临以下问题：
* 软件支持的CUDA版本和运行系统的版本不对齐
*


#### nvidia container toolkit


