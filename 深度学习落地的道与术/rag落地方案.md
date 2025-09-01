# rag落地方案

## 概览

### 目标

希望通过rag能做到：

* 一套基于隐式结构知识的

* 多源异构文档的管理，关键信息的自动提炼

* 大范围信息连接器

<br>

## graph-rag探索（调研阶段）

我们将调研的结果记录在此，当前的预研内容概括:

* 底层技术选型
  
  * query + 持久化：helixdb
  
  * 私有大模型部署：luminal/mistral.rs/vllm
- 实验构建目标&数据源
  
  - code assistant + github repository(text,code..)
  
  - 经济deep researcher：经济/货币新闻（具体来源待定）

- 图识别/建模（构建）策略&提取算法
  
  - 使用综合能力较强的llm进行**识别/建模**等复杂任务的agent，其提示词设计依托于schema设计/建模原则的确立
  
  - 使用Mcp来完成关系提取&验证：
    
    - 特化模型，如三元组特化模型：[SciPhi/Triplex · Hugging Face](https://huggingface.co/SciPhi/Triplex)
    
    - 代码静态分析工具：tree-sitter

- schema设计原则

### Helix-db实践

使用Helix-db在本地部署了数据库实例，记录一些关键内容。

1.使用helixql(helixdb自创的一种schema定义和query模型定义的查询语言，语法细节见https://docs.helix-db.com/documentation/hql/hql)构建数据库实例的定义：

```cypher
// schema.hx
N::Folder {
    name: String,
    extracted_at: Date DEFAULT NOW
}

N::File {
    name: String,
    extension: String,
    text: String,
    extracted_at: Date DEFAULT NOW
}

N::Entity {
    entity_type: String,
    start_byte: I64,
    end_byte: I64,
    order: I64,
    text: String,
    extracted_at: Date DEFAULT NOW
}
...
E::Entity_to_Entity {
    From: Entity,
    To: Entity,
    Properties: {
    }
}

E::Entity_to_EmbededCode {
    From: Entity,
    To: EmbededCode,
    Properties: {
    }
}

V::EmbededCode {
    vector: [F64]
}


// queries.hx
// Create Files
QUERY createSuperFile(root_id: ID, name: String, extension: String, text: String) => 
    root <- N<Root>(root_id)
    file <- AddN<File>({name:name, extension:extension, text:text})
    AddE<Root_to_File>()::From(root)::To(file)
    RETURN file

QUERY createFile(folder_id: ID, name: String, extension: String, text: String) => 
    folder <- N<Folder>(folder_id)
    file <- AddN<File>({name:name, extension:extension, text:text})
    AddE<Folder_to_File>()::From(folder)::To(file)
    RETURN file

// Get Files
QUERY getAllFiles() => 
    files <- N<File>
    RETURN files::!{text}

QUERY getFile(file_id: ID) => 
    file <- N<File>(file_id)
    RETURN file::!{text}
```

<br>

2.使用helix compile创建得到编译好的rust文件（helixql -> rust），文件名为queries.rs，结合helix-db内部的helix-container(bin crate)，能够得到一个可执行文件，该文件可理解为helix-db的数据库实例（暴露了数据库服务，默认端口6969），它会创建并管理持久化的数据库文件（默认路径在~/.helix/data下，也可以自己指定）**data.mdb**

* 查看数据库实例可以使用`helix status`（注意这是cli工具，并非container）

<br>

3.使用graph construction工具，我选择使用helixdb提供的codebase-index([GitHub - HelixDB/codebase-index](https://github.com/HelixDB/codebase-index/tree/main))工具，使用本地embedding（基于fastembed-rs）工具将示例项目的vector和基于tree-sitter创建的graph塞进了实例管理数据中（只要在src目录下cargo run即可，项目默认使用的是gemini提供的embedding api，我没有KEY所以替换成了本地实现的embedding function）

<br>

4.最后使用dashboard（[GitHub - HelixDB/helix-dashboard](https://github.com/HelixDB/helix-dashboard)）启动前后端，即可将数据渲染到浏览器上，下面为参考：

![dashboard](/Users/wangjiajie/software/ClassNotebook/statics/helixdb-dashboard.png)

### 图的自动化构建

<br>

评估哪一个方法更好需要围绕着具体的**benchmark**和已经成熟的**商业化工具**进行评估，我会优先考虑调研在**软件开发**助理和**自动交易系统/deep researcher**两个领域的技术方案。我在此列举出我调研中了解到一些可借鉴的点:

* 逻辑密集型/复杂任务:**分解**目标为细粒度步骤，对于其中最复杂最容易出错的步骤看是否有专用工具/检测助手可以帮助**检验**阶段性成果（self-verification pipeline）
  
  * IMO论文指出多步骤结合验证专家的状态机session（参考https://github.com/yb235/Gemini-IMO-math-Agent）
  
  * 其他模式提示词：https://iamholumeedey007.medium.com/prompt-engineering-patterns-for-successful-rag-implementations-b2707103ab56
  
  * claude团队提出：在超长上下文任务中，可以将子任务的结论进行压缩/compact提供给**继任者**

* 图构建系统
  
  * HippoRAG2-图构建:
    
    * 使用llm对输入数据进行**ner**/**三元组提取**
    
    * 将向量嵌入图中：三元组中的实体会被向量化，三元组本身也会作为一个**事实**被向量化，同时原始文本也会向量化并被嵌入到文本块本身所代表的节点
    
    * **图构造**：事实边连接；文本块-包含实体连接（宏观 -> 微观）；同义词（基于向量的knn算法）边
    
    * 缓存设计
  
  * HippoRAG2-混合检索：
    
    * 用户问题向量化 -> 在事实嵌入库中进行相似度搜索 -> 得到相关事实列表
    
    * 基于dspy模版结合llm（例如llama3-70B）进行相关事实的筛选，如果没有筛选出相关的事实，则降级为标准向量检索
    
    * 基于personal page rank算法：以上一步筛选出的事实中的实体节点作为种子，赋予其较高初始权重，并将相关的文本块/篇章权重也进行增大，最终得到各个篇章得分
  
  * aider：应该使用tree-sitter这样的**专业领域工具**辅助构建特定输入格式的内容（提一下，从软件开发的角度来说应该在前期简化输入数据的自由度）
  
  * graphiti：
  
  * 

### schema设计原则

先调研：

* （kg+llm）领域综述：https://arxiv.org/pdf/2306.08302

* 最前沿的kg builder:[GitHub - getzep/graphiti: Build Real-Time Knowledge Graphs for AI Agents](https://github.com/getzep/graphiti)

* 通用设计：[GitHub - TuGraph-family/chat2graph: Chat2Graph: Graph Native Agentic System.](https://github.com/TuGraph-family/chat2graph)

* benchmark sota：[GitHub - OSU-NLP-Group/HippoRAG: [NeurIPS&#39;24] HippoRAG is a novel RAG framework inspired by human long-term memory that enables LLMs to continuously integrate knowledge across external documents. RAG + Knowledge Graphs + Personalized PageRank.](https://github.com/OSU-NLP-Group/HippoRAG)

## ADK探索

### 简介

ADK是google提出的一套开发agent系统的框架，设计动机是让agent的开发流程和软件开发流程对齐。我之所以研究adk是因为我认为google实际上是人工智能领域走在最前沿的公司，希望通过follow这家公司的动作来研究最优秀的助理设计方法。

<br>

### A2A协议

简单来说，A2A协议是google提出的让agent之间互相交流的一套协议。

### adk-agent

从adk-samples项目中以具体的agent设计作为案例研究adk构建agent的方式。

## 记录问题
