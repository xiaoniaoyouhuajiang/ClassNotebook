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

### 图的自动化构建

<br>

### schema设计原则

先调研：

* （kg+llm）领域综述：https://arxiv.org/pdf/2306.08302

* 最前沿的kg builder:[GitHub - getzep/graphiti: Build Real-Time Knowledge Graphs for AI Agents](https://github.com/getzep/graphiti)

* 通用设计：[GitHub - TuGraph-family/chat2graph: Chat2Graph: Graph Native Agentic System.](https://github.com/TuGraph-family/chat2graph)

* benchmark sota：[GitHub - OSU-NLP-Group/HippoRAG: [NeurIPS&#39;24] HippoRAG is a novel RAG framework inspired by human long-term memory that enables LLMs to continuously integrate knowledge across external documents. RAG + Knowledge Graphs + Personalized PageRank.](https://github.com/OSU-NLP-Group/HippoRAG)

## 记录问题
