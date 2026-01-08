# candle-nn设计

## candle-nn编码指导



### 加载预训练模型

下面这段代码是`trocr`的example中的模型加载过程

```rust
let vb = {
    let model = match args.model {
        Some(model) => std::path::PathBuf::from(model),
        None => {
            let (repo, branch) = args.which.repo_and_branch_name();
            api.repo(hf_hub::Repo::with_revision(
                repo.to_string(),
                hf_hub::RepoType::Model,
                branch.to_string(),
            ))
            .get("model.safetensors")?
        }
    };
    println!("model: {:?}", model);
    unsafe { VarBuilder::from_mmaped_safetensors(&[model], DType::F32, &device)? }
};
```

显然我们需要重点关注的对象是`VarBuilder`以及`safetensors`



#### Safetensors

问题：我们如何将Safetensors文件转换为内存中的数据？



首先，内存中的存储对象是MmapedSafetensors：

```rust
pub struct MmapedSafetensors {
    safetensors: Vec<yoke::Yoke<SafeTensors_<'static>, memmap2::Mmap>>,
    routing: Option<HashMap<String, usize>>,
}
```



反序列化过程请看代码：

```rust
pub unsafe fn multi<P: AsRef<Path>>(paths: &[P]) -> Result<Self> {
    let mut routing = HashMap::new();
    let mut safetensors = vec![];
    for (index, p) in paths.iter().enumerate() {
        let p = p.as_ref();
        let file = std::fs::File::open(p).map_err(|e| Error::from(e).with_path(p))?;
        let file = memmap2::MmapOptions::new()
            .map(&file)
            .map_err(|e| Error::from(e).with_path(p))?;
        let data = yoke::Yoke::<SafeTensors_<'static>, memmap2::Mmap>::try_attach_to_cart(
            file,
            |data: &[u8]| {
                let st = safetensors::SafeTensors::deserialize(data)
                    .map_err(|e| Error::from(e).with_path(p))?;
                Ok::<_, Error>(SafeTensors_(st))
            },
        )?;
        for k in data.get().0.names() {
            routing.insert(k.to_string(), index);
        }
        safetensors.push(data)
    }
    Ok(Self {
        safetensors,
        routing: Some(routing),
    })
```





#### VarBuilder

```rust
// 能覆盖大多数场景的VarBuilder
pub type VarBuilder<'a> = VarBuilderArgs<'a, Box<dyn SimpleBackend + 'a>>;

pub trait Backend: Send + Sync {
    type Hints: Default;

    /// Retrieve a tensor with some target shape.
    fn get(
        &self,
        s: Shape,
        name: &str,
        h: Self::Hints,
        dtype: DType,
        dev: &Device,
    ) -> Result<Tensor>;

    fn contains_tensor(&self, name: &str) -> bool;
}

pub trait SimpleBackend: Send + Sync {
	...
}

impl Backend for Box<dyn SimpleBackend + '_> {
    type Hints = crate::Init;
    fn get(
        &self,
        s: Shape,
        name: &str,
        h: Self::Hints,
        dtype: DType,
        dev: &Device,
    ) -> Result<Tensor> {
        self.as_ref().get(s, name, h, dtype, dev)
    }

    fn contains_tensor(&self, name: &str) -> bool {
        self.as_ref().contains_tensor(name)
    }
}

pub struct VarBuilderArgs<'a, B: Backend> {
    data: Arc<TensorData<B>>,
    path: Vec<String>,
    pub dtype: DType,
    _phantom: std::marker::PhantomData<&'a B>,
}
```

首先梳理一下，模型权重数据的源头可以有很多种，最简单的，就是将权重存储在一个文件当中，还有可能存储在一个bucket当中。对于candle而言，它需要实现从不同介质的数据到candle tensor的载入/映射逻辑。由于介质不一定相同，他一定需要一种用于分发不同载入逻辑的**Type**，在源码中，这个类型/Trait就是Bacnkend，同时，我们后面会看到这个类型也是存储数据的实际类型，换句话说，**Backend的类型直接决定了它会如何被载入**。

而VarBuilderArgs中的_phantom就是起到标识不同分发逻辑的作用，而VarBuilder是作为最常用的VarBuilderArgs的一种分发（自然还有其他的可能），其Backend为SimpleBackend，SimpleBackend也是一种Trait，因此它也有分发的对象（具体的结构体），比如npz格式，safetensor格式等。

因此，candle源码中定义了很多其他文件，如"npy.rs"等用于实现从文件到数据的转换逻辑。



现在我们把目光聚焦在数据实际所在的位置，我们需要留意VarBuilderArgs中用于存储数据的字段，另外我们专注于对Safetensor对象的转换：

```rust
struct TensorData<B: Backend> {
    backend: B,
    pub device: Device,
}

impl SimpleBackend for candle::safetensors::MmapedSafetensors {
    fn get(
        &self,
        s: Shape,
        name: &str,
        _: crate::Init,
        dtype: DType,
        dev: &Device,
    ) -> Result<Tensor> {
        let tensor = self.load(name, dev)?.to_dtype(dtype)?;
        if tensor.shape() != &s {
            Err(candle::Error::UnexpectedShape {
                msg: format!("shape mismatch for {name}"),
                expected: s,
                got: tensor.shape().clone(),
            }
            .bt())?
        }
        Ok(tensor)
    }

    fn contains_tensor(&self, name: &str) -> bool {
        self.get(name).is_ok()
    }
}
```

可以看到，要通过VarBuilder获取tensor，可以通过`MmapedSafetensors.load(name)`的方法



再来关注，当VarBuilder初始化的同时，会发生什么？

```rust
pub unsafe fn from_mmaped_safetensors<P: AsRef<std::path::Path>>(
    paths: &[P],
    dtype: DType,
    dev: &Device,
) -> Result<Self> {
    let tensors = candle::safetensors::MmapedSafetensors::multi(paths)?;
    Ok(Self::from_backend(Box::new(tensors), dtype, dev.clone()))
}
```

可以看到是通过MmapedSafetensors::multi方法，具体的载入逻辑可以回到Safetensors小节去看。



#### Yoke:零拷贝反序列化

这部分内容，请参考同目录下的单独文章*Zero-Copy*。



### 从模型中加载张量

现在，我们讨论如何从SimpleBackend的一种实现`MmapedSafetensors`中加载某一个layer的张量：

```rust
impl SimpleBackend for candle::safetensors::MmapedSafetensors {
    fn get(
        &self,
        s: Shape,
        name: &str,
        _: crate::Init,
        dtype: DType,
        dev: &Device,
    ) -> Result<Tensor> {
        let tensor = self.load(name, dev)?.to_dtype(dtype)?;
        if tensor.shape() != &s {
            Err(candle::Error::UnexpectedShape {
                msg: format!("shape mismatch for {name}"),
                expected: s,
                got: tensor.shape().clone(),
            }
            .bt())?
        }
        Ok(tensor)
    }

    fn contains_tensor(&self, name: &str) -> bool {
        self.get(name).is_ok()
    }
}
```



还是回到trocr的例子中：

```rust
let mut model = trocr::TrOCRModel::new(&encoder_config, &decoder_config, vb)?;
```

上文中，我们构造了基于mmap映射内存的vb对象，这一个语句中，则是通过一个具体的transformer对象来调用MmapedSafetensors中的值。



#### 推理过程

```rust
// trocr model在初始化过程创建encoder和decoder以及
let encoder = TrOCREncoder::new(encoder_cfg, vb.clone())?;
let decoder = TrOCRForCausalLM::new(decoder_cfg, vb)?;

// 以Encoder的forward过程为例，Encoder初始化过程如下
let vb_v = vb.pp("encoder");
let embeddings = Embeddings::new(cfg, false, vb_v.pp("embeddings"))?;
...

// Embeddings对象的构造（参考下文）
...

// 以embedding的forward过程为例
let encoder_xs = model.encoder().forward(&image)?;
```



Embeddings的构造过程

```rust
pub fn new(cfg: &Config, use_mask_token: bool, vb: VarBuilder) -> Result<Self> {
    let hidden_size = cfg.hidden_size;
    let cls_token = vb.get((1, 1, hidden_size), "cls_token")?;
    let mask_token = if use_mask_token {
        Some(vb.get((1, 1, hidden_size), "mask_token")?)
    } else {
        None
    };
    let patch_embeddings = PatchEmbeddings::new(cfg, vb.pp("patch_embeddings"))?;
    let num_patches = patch_embeddings.num_patches;
    let position_embeddings =
        vb.get((1, num_patches + 1, hidden_size), "position_embeddings")?;
    Ok(Self {
        cls_token,
        mask_token,
        patch_embeddings,
        position_embeddings,
        hidden_size,
    })
}
```



观察出，有几个比较重要的调用：

* vb.clone()
* vb.pp(s：ToString)
* `get<S: Into<Shape>>(&self, s: S, name: &str) -> Result<Tensor>`



`get`调用非常重要，因为这是提取权重过程真正发生的位置。下面进行逐一分解



##### clone

```rust
impl<B: Backend> Clone for VarBuilderArgs<'_, B> {
    fn clone(&self) -> Self {
        Self {
            data: self.data.clone(),
            path: self.path.clone(),
            dtype: self.dtype,
            _phantom: self._phantom,
        }
    }
}
```

在我们讲述的场景中：

`vb.data -> Arc<TensorData<Backend>>` ，所以当拷贝发生时，我们可以理解为这其实是对mmap内存段的又一个引用



##### push_prefix

```rust
impl<B: Backend> VarBuilderArgs<'_, B> {
	pub fn push_prefix<S: ToString>(&self, s: S) -> Self {
        let mut path = self.path.clone();
        path.push(s.to_string());
        Self {
            data: self.data.clone(),
            path,
            dtype: self.dtype,
            _phantom: std::marker::PhantomData,
        }
    }
}
```

可以看出，其实pp就是往path中新增一些字符前缀



##### get

以Embedding模块中的mask_token为例：

```rust
vb.get((1, 1, hidden_size), "mask_token")?
```



```rust
// vb的get方法
pub fn get_with_hints_dtype<S: Into<Shape>>(
    &self,
    s: S,
    name: &str,
    hints: B::Hints,
    dtype: DType,
) -> Result<Tensor> {
    let path = self.path(name);
    self.data
        .backend
        .get(s.into(), &path, hints, dtype, &self.data.device)
}

// Backend的get方法
impl SimpleBackend for candle::safetensors::MmapedSafetensors {
    fn get(
        &self,
        s: Shape,
        name: &str,
        _: crate::Init,
        dtype: DType,
        dev: &Device,
    ) -> Result<Tensor> {
        let tensor = self.load(name, dev)?.to_dtype(dtype)?;
        if tensor.shape() != &s {
            Err(candle::Error::UnexpectedShape {
                msg: format!("shape mismatch for {name}"),
                expected: s,
                got: tensor.shape().clone(),
            }
            .bt())?
        }
        Ok(tensor)
    }

    fn contains_tensor(&self, name: &str) -> bool {
        self.get(name).is_ok()
    }
}

// MmaoedSafetensors的get方法
    pub fn get(&self, name: &str) -> Result<st::TensorView<'_>> {
        let index = match &self.routing {
            None => 0,
            Some(routing) => {
                let index = routing.get(name).ok_or_else(|| {
                    Error::CannotFindTensor {
                        path: name.to_string(),
                    }
                    .bt()
                })?;
                *index
            }
        };
        Ok(self.safetensors[index].get().0.tensor(name)?)
    }
```



这里，通过safetensors crate的`tensor`方法，我们能够得到TensorView对象：

```rust
    pub fn tensor(&self, tensor_name: &str) -> Result<TensorView<'data>, SafeTensorError> {
        if let Some(index) = &self.metadata.index_map.get(tensor_name) {
            if let Some(info) = &self.metadata.tensors.get(**index) {
                Ok(TensorView {
                    dtype: info.dtype,
                    shape: info.shape.clone(),
                    data: &self.data[info.data_offsets.0..info.data_offsets.1],
                })
            } else {
                Err(SafeTensorError::TensorNotFound(tensor_name.to_string()))
            }
        } else {
            Err(SafeTensorError::TensorNotFound(tensor_name.to_string()))
        }
    }
```

可以看到，SafeTensor对象中有一个Metadata字段，贮存了TensorInfo数组，这里面包含了内存区域中的一小块用于存储该tensor的偏移量：

```rust
#[derive(Debug, Deserialize, Serialize, Clone)]
pub struct TensorInfo {
    /// The type of each element of the tensor
    pub dtype: Dtype,
    /// The shape of the tensor
    pub shape: Vec<usize>,
    /// The offsets to find the data within the byte-buffer array.
    pub data_offsets: (usize, usize),
}
```

注意到，TensorView当中的data是一个byte slice



从safetensor::TensorView到candle::Tensor，有一个转换函数：

```rust
fn convert(view: &st::TensorView<'_>, device: &Device) -> Result<Tensor> {
    match view.dtype() {
        st::Dtype::U8 => convert_::<u8>(view, device),
        st::Dtype::U16 => {
            let conv = |x| Ok(u32::from(x));
            convert_with_cast_::<u16, u32, _>(view, device, conv)
        }
        st::Dtype::U32 => convert_::<u32>(view, device),
        st::Dtype::I32 => {
            let conv = |x| Ok(i64::from(x));
            convert_with_cast_::<i32, i64, _>(view, device, conv)
        }
        st::Dtype::I64 => convert_::<i64>(view, device),
        st::Dtype::BF16 => convert_::<half::bf16>(view, device),
        st::Dtype::F16 => convert_::<half::f16>(view, device),
        st::Dtype::F32 => convert_::<f32>(view, device),
        st::Dtype::F64 => convert_::<f64>(view, device),
        dtype => Err(Error::UnsupportedSafeTensorDtype(dtype)),
    }
}
```



##### 转换

```rust
fn convert_<T: WithDType>(view: &st::TensorView<'_>, device: &Device) -> Result<Tensor> {
    convert_slice::<T>(view.data(), view.shape(), device)
}

fn convert_slice<T: WithDType>(data: &[u8], shape: &[usize], device: &Device) -> Result<Tensor> {
    let size_in_bytes = T::DTYPE.size_in_bytes();
    let elem_count = data.len() / size_in_bytes;
    if (data.as_ptr() as usize) % size_in_bytes == 0 {
        // SAFETY This is safe because we just checked that this
        // was correctly aligned.
        let data: &[T] =
            unsafe { std::slice::from_raw_parts(data.as_ptr() as *const T, elem_count) };
        Tensor::from_slice(data, shape, device)
    } else {
        // XXX: We need to specify `T` here, otherwise the compiler will infer u8 because of the following cast
        // Making this vector too small to fit a full f16/f32/f64 weights, resulting in out-of-bounds access
        let mut c: Vec<T> = Vec::with_capacity(elem_count);
        // SAFETY: We just created c, so the allocated memory is necessarily
        // contiguous and non overlapping with the view's data.
        // We're downgrading the `c` pointer from T to u8, which removes alignment
        // constraints.
        unsafe {
            std::ptr::copy_nonoverlapping(data.as_ptr(), c.as_mut_ptr() as *mut u8, data.len());
            c.set_len(elem_count)
        }
        Tensor::from_slice(&c, shape, device)
    }
}
```



关于Storage的转换便不再赘述，需要关心的是，从&[u8]到&[T]（比如可能是f64）的过程。



### 相关术语

#### backbone

> A backbone is a model used for feature extraction for higher level computer vision tasks such as object detection and image classification. Transformers provides an AutoBackbone class for initializing a Transformers backbone from pretrained model weights, and two utility classes



## 以table transformer推理作为引子

table transformer是huggingface的transformer库中的一个模块，这个库是基于pytorch开发的。

我需要利用table transformer来完成表结构的识别，因此我需要梳理：

* 预/后处理方法
* 计算图结构





### [post-processor] 

最终要输出的目标的大概格式是

```python
[{
    'label': str,
    'score': float,
    'bbox': [float]
}]
```



#### bbox构成

在目标检测任务中，**bbox** 是 **bounding box**（边界框）的缩写。边界框是一个矩形框，用于在图像中标识和定位目标物体的位置。它通常由四个参数定义：

1. **x_min**：边界框左上角的 x 坐标。
2. **y_min**：边界框左上角的 y 坐标。
3. **x_max**：边界框右下角的 x 坐标。
4. **y_max**：边界框右下角的 y 坐标。



####  outputs对象

我们后处理的操作本质都是从outputs对象中提取信息，因此我们需要弄清楚函数中outputs对象的结构

TableTransformerForObjectDetection的输出是一个python class：

其中各参数的释义如下：

参数：

- `loss`（`torch.FloatTensor`，形状为 `(1,)`，*可选*，当提供 `labels` 时返回）： 总损失作为类别预测的负对数似然（交叉熵）和边界框损失的线性组合。后者定义为 L1 损失和广义尺度不变 IoU 损失的线性组合。
- `loss_dict`（`Dict`，*可选*）： 包含各个损失的字典。适用于日志记录。
- `logits`（`torch.FloatTensor`，形状为 `(batch_size, num_queries, num_classes + 1)`）： 所有查询的分类 logits（包括无对象）。
- `pred_boxes`（`torch.FloatTensor`，形状为 `(batch_size, num_queries, 4)`）： 所有查询的归一化边界框坐标，表示为（中心_x，中心_y，宽度，高度）。这些值在 [0, 1] 范围内归一化，相对于批次中每个单独图像的大小（忽略可能的填充）。可以使用 [`~TableTransformerImageProcessor.post_process_object_detection`] 来检索未归一化的边界框。
- `auxiliary_outputs`（`list[Dict]`，*可选*）： *可选*，仅在激活辅助损失（即 `config.auxiliary_loss` 设置为 `True`）且提供标签时返回。它是包含每个解码器层的上述两个键（`logits` 和 `pred_boxes`）的字典列表。
- `last_hidden_state`（`torch.FloatTensor`，形状为 `(batch_size, sequence_length, hidden_size)`，*可选*）： 模型解码器最后一层的输出隐藏状态序列。
- `decoder_hidden_states`（`tuple(torch.FloatTensor)`，*可选*，当传递 `output_hidden_states=True` 或 `config.output_hidden_states=True` 时返回）： `torch.FloatTensor` 的元组（一个用于嵌入的输出 + 每个层的输出），形状为 `(batch_size, sequence_length, hidden_size)`。解码器在每层的输出加上初始嵌入输出的隐藏状态。
- `decoder_attentions`（`tuple(torch.FloatTensor)`，*可选*，当传递 `output_attentions=True` 或 `config.output_attentions=True` 时返回）： `torch.FloatTensor` 的元组（每层一个），形状为 `(batch_size, num_heads, sequence_length, sequence_length)`。解码器的注意力权重，在注意力 softmax 之后，用于计算自注意力头中的加权平均值。
- `cross_attentions`（`tuple(torch.FloatTensor)`，*可选*，当传递 `output_attentions=True` 或 `config.output_attentions=True` 时返回）： `torch.FloatTensor` 的元组（每层一个），形状为 `(batch_size, num_heads, sequence_length, sequence_length)`。解码器交叉注意力层的注意力权重，在注意力 softmax 之后，用于计算交叉注意力头中的加权平均值。
- `encoder_last_hidden_state`（`torch.FloatTensor`，形状为 `(batch_size, sequence_length, hidden_size)`，*可选*）： 模型编码器最后一层的输出隐藏状态序列。
- `encoder_hidden_states`（`tuple(torch.FloatTensor)`，*可选*，当传递 `output_hidden_states=True` 或 `config.output_hidden_states=True` 时返回）： `torch.FloatTensor` 的元组（一个用于嵌入的输出 + 每个层的输出），形状为 `(batch_size, sequence_length, hidden_size)`。编码器在每层的输出加上初始嵌入输出的隐藏状态。
- `encoder_attentions`（`tuple(torch.FloatTensor)`，*可选*，当传递 `output_attentions=True` 或 `config.output_attentions=True` 时返回）： `torch.FloatTensor` 的元组（每层一个），形状为 `(batch_size, num_heads, sequence_length, sequence_length)`。编码器的注意力权重，在注意力 softmax 之后，用于计算自注意力头中的加权平均值。



在当前处理的场景下，最重要的参数为：

* logits：每个对象的未归一化的概率
* pred_boxes：边框数据

上面两个对象都是torch.tensor类型，其中object的个数为上述tensor的第二维度大小





现在，来看下Python代码：

```python
# 将“目标”的中心以及宽高数据转换为xyxy格式
def box_cxcywh_to_xyxy(x):
    x_c, y_c, w, h = x.unbind(-1)
    b = [(x_c - 0.5 * w), (y_c - 0.5 * h), (x_c + 0.5 * w), (y_c + 0.5 * h)]
    return torch.stack(b, dim=1)

# 将边界框的坐标从相对坐标（在 0 到 1 之间）缩放到图像的实际像素坐标
def rescale_bboxes(out_bbox, size):
    img_w, img_h = size
    b = box_cxcywh_to_xyxy(out_bbox)
    b = b * torch.tensor([img_w, img_h, img_w, img_h], dtype=torch.float32)
    return b

def outputs_to_objects(outputs, img_size, id2label):
    m = outputs.logits.softmax(-1).max(-1)
    pred_labels = list(m.indices.detach().cpu().numpy())[0]
    pred_scores = list(m.values.detach().cpu().numpy())[0]
    pred_bboxes = outputs['pred_boxes'].detach().cpu()[0]
    pred_bboxes = [elem.tolist() for elem in rescale_bboxes(pred_bboxes, img_size)]

    objects = []
    for label, score, bbox in zip(pred_labels, pred_scores, pred_bboxes):
        class_label = id2label[int(label)]
        if not class_label == 'no object':
            objects.append({'label': class_label, 'score': float(score),
                            'bbox': [float(elem) for elem in bbox]})
```



### [config]TableTransformerConfig

```python
    # Copied from transformers.models.detr.configuration_detr.DetrConfig.__init__
    def __init__(
        self,
        use_timm_backbone=True,
        backbone_config=None,
        num_channels=3,
        num_queries=100,
        encoder_layers=6,
        encoder_ffn_dim=2048,
        encoder_attention_heads=8,
        decoder_layers=6,
        decoder_ffn_dim=2048,
        decoder_attention_heads=8,
        encoder_layerdrop=0.0,
        decoder_layerdrop=0.0,
        is_encoder_decoder=True,
        activation_function="relu",
        d_model=256,
        dropout=0.1,
        attention_dropout=0.0,
        activation_dropout=0.0,
        init_std=0.02,
        init_xavier_std=1.0,
        auxiliary_loss=False,
        position_embedding_type="sine",
        backbone="resnet50",
        use_pretrained_backbone=True,
        backbone_kwargs=None,
        dilation=False,
        class_cost=1,
        bbox_cost=5,
        giou_cost=2,
        mask_loss_coefficient=1,
        dice_loss_coefficient=1,
        bbox_loss_coefficient=5,
        giou_loss_coefficient=2,
        eos_coefficient=0.1,
        **kwargs,
    ):
```

下面只讲述关键的参数：

* d_model：layer的个数



### [Module]TableTransformerForObjectDetection

Module组成：

* DETR encoder-decoder model: TableTransformerModel
* class_labels_classifier: Linear layer
* bbox_predictor: TableTransformerMLPPredictionHead



线性映射层不需要过多赘述，在这里的是作为一个**标签分类器**，输出层的神经元个数为num_labels+1（即没有object单独为一个label）。



#### [Module]bbox_predictor

这里bbox_predictor是一个单独的Module，是插在序列输出上的（MLP+sigmoid），其结构非常简单，如下：

```python
class TableTransformerMLPPredictionHead(nn.Module):
    """
    Very simple multi-layer perceptron (MLP, also called FFN), used to predict the normalized center coordinates,
    height and width of a bounding box w.r.t. an image.

    Copied from https://github.com/facebookresearch/table_transformer/blob/master/models/table_transformer.py

    """

    def __init__(self, input_dim, hidden_dim, output_dim, num_layers):
        super().__init__()
        self.num_layers = num_layers
        h = [hidden_dim] * (num_layers - 1)
        self.layers = nn.ModuleList(nn.Linear(n, k) for n, k in zip([input_dim] + h, h + [output_dim]))

    def forward(self, x):
        for i, layer in enumerate(self.layers):
            x = nn.functional.relu(layer(x)) if i < self.num_layers - 1 else layer(x)
        return x
```

其中num_layers为3，而output_dim为4（xyxy）





#### [*Module]TableTransformerModel

>   The bare Table Transformer Model (consisting of a backbone and encoder-decoder Transformer) outputting raw
>
>   hidden-states without any specific head on top.

```python
        # Create backbone + positional encoding
        backbone = TableTransformerConvEncoder(config)
        object_queries = build_position_encoding(config)
        self.backbone = TableTransformerConvModel(backbone, object_queries)

        # Create projection layer
        self.input_projection = nn.Conv2d(backbone.intermediate_channel_sizes[-1], config.d_model, kernel_size=1)

        self.query_position_embeddings = nn.Embedding(config.num_queries, config.d_model)

        self.encoder = TableTransformerEncoder(config)
        self.decoder = TableTransformerDecoder(config)
```



**Forward方法**





##### [Module]TableTransformerConvEncoder



##### [Module]
