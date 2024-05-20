# linter & editor
原本想把这个章节加入到`元工具.md`文件中，但这样元工具文档的文本内容有点太多了，于是决定将该章节给独立出来

本文主要用做记录开发过程中使用一些编辑器来优化开发工作流的体验

## 编辑器

### vscode
我的主力编辑器，一开始用的都是jb家的编辑器（因为公司有购买专业版，奔着薅羊毛的心态），发现有很多地方不太符合我的需求，比如远程服务器开发，所以还是切回来了（哭..）,本文中的大部分内容都会围绕vscode及其插件开展

#### 问题集合
* debug的时候提示：could not find this file：一般是因为文件实际做了链接，使用源文件的路径即可
* 

### nvchad(neovim)
我的大部分开发工作都转移到了linux，在这样的终端环境下，非图形化界面的编辑器很重要，并且他必须具备以下几个特性：
* 容易安装，不至于有大量的安装依赖，或者有portable版本（满足）
* 满足开发需求，包括：
    * 可以安装开发语言的language server protocol实现（其实这个包含下面的所有了，满足）
    * linter
    * debugger
* 编辑器本身的功能必须保证（太满足了）

neovim的缺陷在于：学习成本，所以是否要学习neovim以及其相应的软件生态，完全取决于个人的权衡

#### 学习内容
* nvchad的操作习惯
* 了解nvchad的配置系统
* 实践如何安装lsp
* 实践如何开发

## linter

### pylint
pylint是python开发者用的最多的linter（大概吧），而且我们开发的项目也有相关的门禁，所以就讲讲这个工具把

一个.pylintrc模板：
```ini
[MASTER]
init-hook = "from pylint.config import find_pylintrc;import os, sys; sys.path.append(os.path.append(os.path.dirname(find_pylintrc())))"

```
