# cv

## 条码库rxing

### 你能获得什么

* 基于pyo3的扩展开发的
  
  * 配置-pyproject.toml,Cargo.toml
  
  * maturin构建系统
  
  * 目录结构编排

* 开发模式&细节
  
  * rust胶水层
  
  * python胶水层
  
  * 编译-测试

* CI&pypi发布
  
  * CI.yml
    
    * linter-质量检查
    
    * 代码测试覆盖
    
    * 多平台构建
    
    * release-分发(pypi)
  
  * github-release
  
  * 文档，协议...
  
  * pypi发布细节

* 介绍Rxing本身(zbar，zxing)

* workspace&混合crate
  
  * rxing-detection（图像处理）
  
  * workspace概念

<br>

### 演示

* dm码的解码&qr码编码

* (检测-解码)变形二维码复原-裁剪

* 检测流水线的**性能**

<br>

### 配置目录编排

说说容易出现问题的点：

* python胶水层如何找到动态库

当执行`maturin develop`时，maturin工具会读取`pyproject.toml`中的[tool.maturin]配置，其中最重要的是python-source和module-name，这里的module-name是你所开发的rust lib的名称（cargo.toml中的）

* 需要使用虚拟环境

这样做能保证不出现包污染的同时，可以快速厘清楚开发所需要的第三方包，写到dependencies配置中（当然maturin也会要求你这样做）

* python胶水层和init

我想要更通用的接口设计，所以对于解码，尽管rust胶水层有decode_luma_pixels, decode_image_bytes, decode_from_file_path，但我都在init中将它们统一封装到了decode函数中，希望它更加“万能”，如果你选择像我这样去做，init文件中就需要有一些**分发**和转换的辅助代码，最后通过all暴露简单的decode

* **中间格式**

对于一些在程序中承担“重要中间角色”的复合结构，我们可以像下面这样

```rust
struct PyBitMatrix {
    #[pyo3(get)]
    width: u32,
    #[pyo3(get)]
    height: u32,
    inner_matrix: rxing::common::BitMatrix,
}

//get宏访问想要的内容
#[pyclass(name = "RXingResult")]
#[derive(Clone)]
struct PyRXingResult {
    #[pyo3(get)]
    text: String,
    #[pyo3(get)]
    raw_bytes: Option<Vec<u8>>,
    #[pyo3(get)]
    num_bits: usize,
    #[pyo3(get)]
    result_points: Option<Vec<PyPoint>>,
    #[pyo3(get)]
    barcode_format: String,
    #[pyo3(get)]
    result_metadata: Option<HashMap<String, String>>,
    #[pyo3(get)]
    timestamp: u128,
}


impl From<rxing::common::BitMatrix> for PyBitMatrix {
    fn from(bm: rxing::common::BitMatrix) -> Self {
        PyBitMatrix {
            width: bm.getWidth(),
            height: bm.getHeight(),
            inner_matrix: bm,
        }
    }
}

// 导出
...
    m.add_class::<PyRXingResult>()?;
    m.add_class::<PyPoint>()?;
    m.add_class::<PyBitMatrix>()?;
```



### CI&Pypi&Action

* 介绍pypi
  
  * 注册&登陆
  
  * 管理受信任的项目

* github actions
  
  * 流水线基本配置
    
    * 触发器
    
    * 任务
    
    * 在步骤中使用预设action
    
    * 变量
    
    * matrix
  
  * 测试
    
    * 基准测试
    
    * 集成测试
    
    * mypy静态类型检查
    
    * 安全扫描



### workspace

#### workspace重构

当项目的复杂性越来越高，我们写的代码需要保持模块化来保证它的可维护性，这个时候，功能之间有时候需要明确区分，比如rxing的detection功能，对于一些不需要二维码检测强化的人用户来说，这可能是个累赘，所以我们需要将功能模块进行解耦合，下面是我项目重构的整个过程：

* 准备三份Cargo.toml
  
  * rxing-python-package_a
  
  * rxing-detection-package_b
  
  * rxing-workspace/根目录

* 目录结构调整

* 调整依赖关系

* 测试代码调整-修改引用路径

* CI.yml修改

* 提pr-合并

package_x属于工作区的一个子项目，从rust crate的视角看，它们之间互相是完全独立的，使用worspace的好处在于：你可以通过相对路径的方式去索引依赖package的代码；同时它们可以和工作区公用一些元信息：version, authors, license；共享依赖。




