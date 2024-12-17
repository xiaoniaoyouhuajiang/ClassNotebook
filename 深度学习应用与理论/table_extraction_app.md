# 表格提取工具研究与实践

出于兴趣，我想研究与表格提取相关的技术（没写制作一个完整的APP是因为这里面涉及的细节有点多，我怕自己把握不住），我先是简单地梳理了一下自己想要的能力到底是什么（算不上需求分析，没那个能力知道吧）：

* 附带截图功能
* 根据表格图片转换为一种中间格式
* 中间格式的输出包括：标准化的图片，markdown代码（以及各种标记语言，当然，首要考虑的是markdown），ASCII输出，单页PDF，Excel格式，Csv格式
* 根据场景生成假表格（输入待定）
* local模型，内存开销尽可能小
* 有可行的迁移方案



## 零碎知识记录

这里记录调研过程中，获得的零碎知识

TATR



## 方法调研

首先需要明确方向，从local模型以及迁移友好这两个角度出发，整个应用推理的workflow应该是领域特化模型的组合而不是靠一个巨大的大模型来支撑（vllm）

举个例子，虽然现在还不了解前沿的算法有哪一些，但是表格内容提取的过程在预想中应该是这样：

表格布局提取 -> Cell内容识别 -> ocr -> 生成内存中间格式 -> 导出成某一种格式



### OCR

#### trocr(Transformer Based OCR)

[模型卡](https://huggingface.co/microsoft/trocr-base-printed)

encoder-decoder模型，图像转换器是一个编码器（encoder），文本转化器是解码器（decoder），而图像编码器的权重来源于`BEiT`，解码器权重来源于`RoBERTa`



#### 推理代码

```rust
// 下列为main函数内容    
let mut tokenizer_dec = {
    let tokenizer_file = match args.tokenizer {
        None => api
            .model(String::from("ToluClassics/candle-trocr-tokenizer"))
            .get("tokenizer.json")?,
        Some(tokenizer) => std::path::PathBuf::from(tokenizer),
    };
    let tokenizer = Tokenizer::from_file(&tokenizer_file).map_err(E::msg)?;
    TokenOutputStream::new(tokenizer)
};
...
// 模型初始化
let mut model = trocr::TrOCRModel::new(&encoder_config, &decoder_config, vb)?;
...
// 图像预处理器
let processor = image_processor::ViTImageProcessor::new(&processor_config);

// 将图像load到device上面
let image = vec![args.image.as_str()];
let image = processor.preprocess(image)?.to_device(&device)?;


```

代码中值得注意的点是：

* 





## 实验过程记录

在完成：

* 安装Transformers

之后，我在本地环境下运行了示例代码

```python
# Python代码
from transformers import AutoImageProcessor, TableTransformerModel
from huggingface_hub import hf_hub_download
from PIL import Image

file_path = hf_hub_download(repo_id="nielsr/example-pdf", repo_type="dataset", filename="example_pdf.png")
image = Image.open(file_path).convert("RGB")

image_processor = AutoImageProcessor.from_pretrained("microsoft/table-transformer-detection")
model = TableTransformerModel.from_pretrained("microsoft/table-transformer-detection")

# prepare image for the model
inputs = image_processor(images=image, return_tensors="pt")

# forward pass
outputs = model(**inputs)

# the last hidden states are the final query embeddings of the Transformer decoder
# these are of shape (batch_size, num_queries, hidden_size)
last_hidden_states = outputs.last_hidden_state
list(last_hidden_states.shape)
```

确认运行成功后，我开始简单地验证模型的效果。



首先我需要弄清楚output变量的内容是什么：

A `transformers.models.table_transformer.modeling_table_transformer.TableTransformerModelOutput` or a tuple of `torch.FloatTensor` (if `return_dict=False` is passed or when `config.return_dict=False`) comprising various elements depending on the configuration ([TableTransformerConfig](https://huggingface.co/docs/transformers/main/en/model_doc/table-transformer#transformers.TableTransformerConfig)) and inputs.

- **last_hidden_state** (`torch.FloatTensor` of shape `(batch_size, sequence_length, hidden_size)`) — Sequence of hidden-states at the output of the last layer of the decoder of the model.
- **decoder_hidden_states** (`tuple(torch.FloatTensor)`, *optional*, returned when `output_hidden_states=True` is passed or when `config.output_hidden_states=True`) — Tuple of `torch.FloatTensor` (one for the output of the embeddings + one for the output of each layer) of shape `(batch_size, sequence_length, hidden_size)`. Hidden-states of the decoder at the output of each layer plus the initial embedding outputs.
- **decoder_attentions** (`tuple(torch.FloatTensor)`, *optional*, returned when `output_attentions=True` is passed or when `config.output_attentions=True`) — Tuple of `torch.FloatTensor` (one for each layer) of shape `(batch_size, num_heads, sequence_length, sequence_length)`. Attentions weights of the decoder, after the attention softmax, used to compute the weighted average in the self-attention heads.
- **cross_attentions** (`tuple(torch.FloatTensor)`, *optional*, returned when `output_attentions=True` is passed or when `config.output_attentions=True`) — Tuple of `torch.FloatTensor` (one for each layer) of shape `(batch_size, num_heads, sequence_length, sequence_length)`. Attentions weights of the decoder’s cross-attention layer, after the attention softmax, used to compute the weighted average in the cross-attention heads.
- **encoder_last_hidden_state** (`torch.FloatTensor` of shape `(batch_size, sequence_length, hidden_size)`, *optional*) — Sequence of hidden-states at the output of the last layer of the encoder of the model.
- **encoder_hidden_states** (`tuple(torch.FloatTensor)`, *optional*, returned when `output_hidden_states=True` is passed or when `config.output_hidden_states=True`) — Tuple of `torch.FloatTensor` (one for the output of the embeddings + one for the output of each layer) of shape `(batch_size, sequence_length, hidden_size)`. Hidden-states of the encoder at the output of each layer plus the initial embedding outputs.
- **encoder_attentions** (`tuple(torch.FloatTensor)`, *optional*, returned when `output_attentions=True` is passed or when `config.output_attentions=True`) — Tuple of `torch.FloatTensor` (one for each layer) of shape `(batch_size, num_heads, sequence_length, sequence_length)`. Attentions weights of the encoder, after the attention softmax, used to compute the weighted average in the self-attention heads.
- **intermediate_hidden_states** (`torch.FloatTensor` of shape `(config.decoder_layers, batch_size, sequence_length, hidden_size)`, *optional*, returned when `config.auxiliary_loss=True`) — Intermediate decoder activations, i.e. the output of each decoder layer, each of them gone through a layernorm.

