# candle源码学习

## candle介绍

candle是huggingface提出的深度学习框架，目前已经支持了市场上主流的模型，详情：

https://github.com/huggingface/candle

Candle 的设计理念围绕以下几个核心特性：

1. **简洁的语法**：类似于 PyTorch 的 API 设计，便于快速上手。
2. **多后端支持**：包括优化的 CPU 后端、Mac 的 Accelerate 后端、支持 CUDA 的 GPU 后端，以及 WebAssembly (WASM) 支持，允许模型直接在浏览器中运行。
3. **丰富的预训练模型**：支持多种流行的深度学习模型，涵盖大型语言模型、计算机视觉模型、音频模型和多模态模型。
4. **量化支持**：支持与 llama.cpp 相同的量化技术，可显著降低模型内存占用。
5. **文件格式支持**：支持加载多种格式的模型文件，包括 safetensors、npz、ggml 或 PyTorch 格式。
6. **无服务器部署**：支持轻量级、快速的 CPU 部署。



candle的核心作用：

* 轻量部署/推理
* 消除python栈，忽视掉gil一类的问题



1. **candle-core**：定义了核心操作、设备抽象和 `Tensor` 结构体。
2. **candle-nn**：提供构建神经网络模型所需的工具。
3. **candle-kernels**：包含 CUDA 自定义内核。
4. **candle-datasets**：实现数据集和数据加载器。
5. **candle-transformers**：提供 Transformer 相关的实用工具。
6. **candle-flash-attn**：实现 Flash Attention v2 层。



调试要点：

* rust-analyzer + vscode
* 调CPU backend的
* 围绕官方测试用例
* 应用围绕llama3



## 计划内容

* candle-tensor的设计：
  * ~~dtype~~
  * ~~tensor的统一存储字段：storage~~
  * ~~tensor的构造方法~~
  * ~~内部可变性,内存拷贝设计（内存调试）~~
  * ~~layout字段如何与storage配合~~
  * ~~tensor的indexing实现~~
  * broadcast实现
    * ~~基本思路~~
    * broadcast_binary_op
    * stride变化
  * issue2499问题定位
  * 算子实现（围绕cpu-binary op）
    * 算子注册
    * 模块层次
    * 性能优化相关设计
    * 自定义算子
    * 反向传播（引子）
  * 常见API（view..）
* backpropagation设计
  * 自动微分技术
  * thinc的设计
  * candle的设计
  * julia, pytorch的设计



## 对比其他框架

| Using PyTorch | Using Candle                        |                                                              |
| ------------- | ----------------------------------- | ------------------------------------------------------------ |
| Creation      | `torch.Tensor([[1, 2], [3, 4]])`    | `Tensor::new(&[[1f32, 2.], [3., 4.]], &Device::Cpu)?`        |
| Creation      | `torch.zeros((2, 2))`               | `Tensor::zeros((2, 2), DType::F32, &Device::Cpu)?`           |
| Indexing      | `tensor[:, :4]`                     | `tensor.i((.., ..4))?`                                       |
| Operations    | `tensor.view((2, 2))`               | `tensor.reshape((2, 2))?`                                    |
| Operations    | `a.matmul(b)`                       | `a.matmul(&b)?`                                              |
| Arithmetic    | `a + b`                             | `&a + &b`                                                    |
| Device        | `tensor.to(device="cuda")`          | `tensor.to_device(&Device::new_cuda(0)?)?`                   |
| Dtype         | `tensor.to(dtype=torch.float16)`    | `tensor.to_dtype(&DType::F16)?`                              |
| Saving        | `torch.save({"A": A}, "model.bin")` | `candle::safetensors::save(&HashMap::from([("A", A)]), "model.safetensors")?` |
| Loading       | `weights = torch.load("model.bin")` | `candle::safetensors::load("model.safetensors", &device)`    |