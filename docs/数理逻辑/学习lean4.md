# 学习Lean4

学习Lean4可以给你带来什么？

1. **深入理解数学和逻辑**：Lean 4提供了一个严格的逻辑和数学框架，可以帮助你进行精确的推理和证明。
2. **提高编程技能**：Lean 4作为一种具有依赖类型的严格纯函数式语言，可以帮助你提高编程技能，特别是在函数式编程方面。
3. **参与开源项目**：通过参与Lean 4的开源项目，你可以与其他开发者合作，共同推动项目的发展，同时也能够提升自己的技术能力和社区影响力。
4. **创造自己的人工智能助手**：结合LLM（大型语言模型）和其他AI技术，你可以利用Lean 4创造自己的AI助手。例如，你可以设计一个智能体（AI Agent），它能够理解自然语言输入，执行复杂的数学证明，并提供交互式的学习体验。
5. **教育和研究**：Lean 4及其相关教程适用于教育与研究，可以帮助数学、计算机科学和逻辑学的学生和教师进行形式化的定理证明教学。



## 前期准备

### 安装elan和lake

```shell
wget -q https://raw.githubusercontent.com/leanprover-community/mathlib4/master/scripts/install_debian.sh && bash install_debian.sh ; rm -f install_debian.sh && source ~/.profile
```



### 安装mathlib

```shell
#使lean环境变量生效
source ~/.bash_profile
cd ~/your_src
git clone https://github.com/leanprover-community/mathematics_in_lean.git

```



## overview

### lean4到底是什么

Put simply, Lean is a tool for building complex expressions in a formal language known as *dependent type theory*.