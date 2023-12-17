# linter & editor
原本想把这个章节加入到`元工具.md`文件中，但这样元工具文档的文本内容有点太多了，于是决定将该章节给独立出来

本文主要用做记录开发过程中使用一些编辑器来优化开发工作流的体验

## 编辑器

### vscode
我的主力编辑器，一开始用的都是jb家的编辑器（因为公司有购买专业版，奔着薅羊毛的心态），发现有很多地方不太符合我的需求，比如远程服务器开发，所以还是切回来了（哭..）,本文中的大部分内容都会围绕vscode及其插件开展


## linter

### pylint
pylint是python开发者用的最多的linter（大概吧），而且我们开发的项目也有相关的门禁，所以就讲讲这个工具把

一个.pylintrc模板：
```ini
[MASTER]
init-hook = "from pylint.config import find_pylintrc;import os, sys; sys.path.append(os.path.append(os.path.dirname(find_pylintrc())))"

```
