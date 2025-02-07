# candle-cuda-op

本文是CUDA相关代码的OP



## GPU编程概览



### rust的build.rs

#### 1. **什么是 `build.rs`？**

`build.rs` 是 Rust 项目的构建脚本（build script），它是一个可选的 Rust 程序，用于在编译主项目之前执行一些自定义的构建逻辑。它通常用于：

- 生成代码（例如通过 `bindgen` 生成 FFI 绑定）。
- 编译和链接本地库（例如 C/C++ 库）。
- 设置环境变量（通过 `cargo:rustc-env` 指令）。
- 执行其他构建任务（例如下载资源或运行脚本）。

`build.rs` 文件通常位于项目的根目录，与 `Cargo.toml` 同级。

------

#### 2. **`build.rs` 的执行时机**

`build.rs` 在以下情况下会被执行：

1. **首次构建**：当你第一次运行 `cargo build` 时，`build.rs` 会被编译并执行。
2. **文件变化**：如果 `build.rs` 本身或其依赖的文件发生变化（通过 `cargo:rerun-if-changed` 指定），它会重新执行。
3. **清理后构建**：运行 `cargo clean` 后，下次构建时会重新执行 `build.rs`。

------

#### 3. **`build.rs` 的输出指令**

`build.rs` 通过打印特定的指令与 Cargo 交互。以下是一些常用的指令：

| 指令                             | 作用                                                         |
| :------------------------------- | :----------------------------------------------------------- |
| `cargo:rerun-if-changed=<path>`  | 指定文件或目录，如果它们发生变化，`build.rs` 会重新执行。    |
| `cargo:rustc-env=<VAR>=<VALUE>`  | 设置编译时的环境变量，可以在主代码中通过 `std::env::var` 读取。 |
| `cargo:rustc-link-search=<path>` | 添加库的搜索路径，用于链接本地库。                           |
| `cargo:rustc-link-lib=<lib>`     | 指定要链接的库名称。                                         |
| `cargo:warning=<message>`        | 打印警告信息，显示在构建输出中。                             |

------

#### 4. **`build.rs` 的工作流程**

以下是一个典型的 `build.rs` 工作流程：

1. **读取配置**：从 `Cargo.toml` 或环境变量中读取配置。
2. **生成代码**：例如通过 `bindgen` 生成绑定文件。
3. **设置环境变量**：通过 `cargo:rustc-env` 设置编译时的环境变量。
4. **输出指令**：通过 `println!` 输出指令，与 Cargo 交互。



## 如何编译

实验过程中出现过一个无法编译cuda代码的问题，如果直接使用

```shell
cargo build --release --features cuda
```

出现类似:

https://github.com/huggingface/candle/issues/353

的问题，可以通过修改compute_cap环境变量编译成功（原因尚未定位，实验显卡2060S）：

```shell
CUDA_COMPUTE_CAP=80 cargo build --release --features cuda
```



### 编译细节

candle框架中最核心的部分是tensor以及其op的定义部分，这些都在`candle-core`这个模块下，但是框架中的cuda代码都在candle-kernels中，所以我们需要先搞清楚，框架是如何串联两者获得GPU backend的加速能力的。

在candle-core中是通过：



#### custom-op

```rust
impl candle::CustomOp1 for Sigmoid {
#[cfg(feature = "cuda")]
    fn cuda_fwd()
}
```



#### op-以avgpool2d为例

op代表的实际上是普通op,以`AvgPool2D`为例：

调用关系分解如下：

Tensor.avg_pool2d -> tensor.avg_pool2d_with_stride -> storage().avg_pool2d()



接下来看Storage的分派代码：

```rust
    pub(crate) fn avg_pool2d(
        &self,
        layout: &Layout,
        kernel_size: (usize, usize),
        stride: (usize, usize),
    ) -> Result<Self> {
        match self {
            Storage::Cpu(storage) => {
                let storage = storage.avg_pool2d(layout, kernel_size, stride)?;
                Ok(Self::Cpu(storage))
            }
            Self::Cuda(storage) => {
                let storage = storage.avg_pool2d(layout, kernel_size, stride)?;
                Ok(Self::Cuda(storage))
            }
            Self::Metal(storage) => {
                let storage = storage.avg_pool2d(layout, kernel_size, stride)?;
                Ok(Self::Metal(storage))
            }
        }
    }
```



下面通过lldb调试，看到avg_pool2d所指向的函数签名在cuda_backend的mod.rs当中：

```rust
impl BackendStorage for CudaStorage {
    ...
    fn avg_pool2d(&self, l: &Layout, k: (usize, usize), stride: (usize, usize)) -> Result<Self> {
        let device = self.device().clone();
        let slice = Pool2D {
            w_k: k.0,
            h_k: k.1,
            w_stride: stride.0,
            h_stride: stride.1,
            op: PoolOp::Avg,
        }
        .map(&self.slice, &device, l)?;
        Ok(Self { slice, device })
    }
}
```



我们看到Pool2D{..}.map()，这是计算实际发生的地方，同样在cuda_backend模块中:

```rust
// Pool2D定义
struct Pool2D {
    w_k: usize,
    h_k: usize,
    w_stride: usize,
    h_stride: usize,
    op: PoolOp,
}

// MAP1实现
impl Map1 for Pool2D {
    fn f<T: DeviceRepr + WithDType + ValidAsZeroBits>(
        &self,
        inp: &CudaSlice<T>,
        dev: &CudaDevice,
        inp_l: &Layout,
    ) -> Result<CudaSlice<T>> {
        // Input shape: (b_size, c, h, w)
        let inp = &inp.slice(inp_l.start_offset()..);
        let shape = inp_l.shape();
        let dims = shape.dims();
        let ds = if dims.len() == 4 {
            [dims, inp_l.stride()].concat()
        } else {
            crate::bail!("unexpected input shape for pool {dims:?}")
        };
        let el = shape.elem_count();
        let out_w = (dims[2] - self.w_k) / self.w_stride + 1;
        let out_h = (dims[3] - self.h_k) / self.h_stride + 1;
        let dst_el = out_w * out_h * dims[0] * dims[1];
        let cfg = LaunchConfig::for_num_elems(dst_el as u32);
        let kname = match self.op {
            PoolOp::Max => "max_pool2d",
            PoolOp::Avg => "avg_pool2d",
        };
        let func = dev.get_or_load_func(&kernel_name::<T>(kname), kernels::CONV)?;
        // SAFETY: Set later by running the kernel.
        let out = unsafe { dev.alloc::<T>(dst_el) }.w()?;
        let ds = dev.htod_copy(ds).w()?;
        let params = (
            el,
            self.w_k,
            self.h_k,
            self.w_stride,
            self.h_stride,
            &ds,
            inp,
            &out,
        );
        // SAFETY: ffi.
        unsafe { func.launch(cfg, params) }.w()?;
        Ok(out)
    }
}

```



显然，Map1是一种trait，被定义在cuda_backend的utils.rs中：

```rust
pub trait Map1 {
    fn f<T: DeviceRepr + WithDType + ValidAsZeroBits>(
        &self,
        src: &CudaSlice<T>,
        dev: &CudaDevice,
        layout: &Layout,
    ) -> Result<CudaSlice<T>>;

    fn map(&self, s: &S, d: &CudaDevice, l: &Layout) -> Result<S> {
        let out = match s {
            S::U8(s) => S::U8(self.f(s, d, l)?),
            S::U32(s) => S::U32(self.f(s, d, l)?),
            S::I64(s) => S::I64(self.f(s, d, l)?),
            S::BF16(s) => S::BF16(self.f(s, d, l)?),
            S::F16(s) => S::F16(self.f(s, d, l)?),
            S::F32(s) => S::F32(self.f(s, d, l)?),
            S::F64(s) => S::F64(self.f(s, d, l)?),
        };
        Ok(out)
    }
}
```



同样地也有Map2 trait，和Map1的区别在于Map1的“算子”参数不一致，比如Map2:

```rust
fn map(&self, s1: &S, l1: &Layout, s2: &S, l2: &Layout, d: &CudaDevice) -> Result<S> {
    let out = match (s1, s2) {
        (S::U8(s1), S::U8(s2)) => S::U8(self.f(s1, l1, s2, l2, d)?),
		...
    };
    Ok(out)
}
```



这里我们重新看回f的实现，func即是真正的算子，它本质是通过ffi链接了CUDA代码：

```rust
let func = dev.get_or_load_func(&kernel_name::<T>(kname), kernels::CONV)?;
...
// cuda_backend中的device.rs
pub fn get_or_load_func(&self, module_name: &str, ptx: &'static str) -> Result<CudaFunction> {
    if !self.has_func(module_name, module_name) {
        // Leaking the string here is a bit sad but we need a &'static str and this is only
        // done once per kernel name.
        let static_module_name = Box::leak(module_name.to_string().into_boxed_str());
        self.load_ptx(ptx.into(), module_name, &[static_module_name])
            .map_err(|cuda| CudaError::Load {
                cuda,
                module_name: module_name.to_string(),
            })
            .w()?;
    }
    self.get_func(module_name, module_name)
        // Clippy recommends this `ok_or` rather than `ok_or_else` so hopefully the compiler is
        // able to only build the error value if needed.
        .ok_or(CudaError::MissingKernel {
            module_name: module_name.to_string(),
        })
        .w()
}
```



注意到这里，我们通过这个方法获得的是cudarc::driver::CudaFunction，而cudarc实际上是一个ffi库，用于链接cuda代码：https://github.com/coreylowman/cudarc

注意：`get_or_load_func`中kernel_name（avg_pool2d）和数据类型/精度绑定，例子中的是F32，CudaDevice的定义：

```rust
#[derive(Clone)]
pub struct CudaDevice {
    id: DeviceId,
    device: Arc<cudarc::driver::CudaDevice>,
    pub(crate) blas: Arc<cudarc::cublas::CudaBlas>,
    curand: Arc<Mutex<CudaRng>>,
}
```

所以我们可以简单的确认，candle获得CUDA能力的主要途径是依托于cudarc这个crate的。



关于`impl CudaDevice`有一些需要注意的地方，这里很容易弄混实际的调用链路：你通过candle自身定义的CudaDevice找不到`load_ptx`以及`has_func`这样的方法，实际上这是因为这一段代码：

```rust
impl std::ops::Deref for CudaDevice {
    type Target = Arc<cudarc::driver::CudaDevice>;

    fn deref(&self) -> &Self::Target {
        &self.device
    }
}
```

- **`type Target = Arc<cudarc::driver::CudaDevice>`**：
  - 指定解引用后的目标类型为 `Arc<cudarc::driver::CudaDevice>`。
- **`fn deref(&self) -> &Self::Target`**：
  - 实现 `deref` 方法，返回 `self.device` 的引用。
  - 这样，当对 `CudaDevice` 实例解引用时，实际上会返回 `self.device`。



假设 `cudarc::driver::CudaDevice` 有一个方法 `do_something`，可以通过以下方式调用：

```rust
let cuda_device = CudaDevice { ... };
cuda_device.do_something(); // 自动解引用为 cudarc::driver::CudaDevice
```



那么，CudaDevice.device在什么时候初始化的呢？它是如何链接到Cuda生成的机器码的呢？这实际上来源于测试用例构造的`Device:new_cuda(0)`

```rust
// candle-core的lib.rs中
pub fn new_cuda(ordinal: usize) -> Result<Self> {
    Ok(Self::Cuda(crate::CudaDevice::new(ordinal)?))
}

// 所以我们要看lib.rs中的CudaDevice从哪里来，注意到
#[cfg(feature = "cuda")]
pub mod cuda_backend;
```

由于使用了`pub`，这意味着cuda_backend中定义的内容在candle-core中是全局可见的，从而，所有谜题都解开了，CudaDevice对象的构建就是：

```rust
    fn new(ordinal: usize) -> Result<Self> {
        let device = cudarc::driver::CudaDevice::new(ordinal).w()?;
        let blas = cudarc::cublas::CudaBlas::new(device.clone()).w()?;
        let curand = cudarc::curand::CudaRng::new(299792458, device.clone()).w()?;
        Ok(Self {
            id: DeviceId::new(),
            device,
            blas: Arc::new(blas),
            curand: Arc::new(Mutex::new(CudaRng(curand))),
        })
    }
```

