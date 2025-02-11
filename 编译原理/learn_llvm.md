# 学习LLVM

`PL.md`中，我们使用LLVM的PASS来演示如何将代码插入到程序执行的过程，我们在这个文档中将对LLVM进行更加细致入微的研究，希望将LLVM项目带来的便利，以及对我们工作的升级进行阐述。

我们会更加系统地学习LLVM相关的内容。

首先我们要更加地了解LLVM，学习一下ta能给我们带来一些什么，再来是了解`学习LLVM`本身能带给我们什么



## 学习LLVM能带来什么

描述自己和了解的相关技术：

* 对调试技术很感兴趣
  * 基于LLVM项目有很多新型DBI：qbdi、instrew
* 对编译器优化感兴趣
* 对软件运行的执行特征有兴趣（同时也是工作需要）
* 对内存访问不是特别懂，想深入了解
* 对异构服务器的性能工程



LLVM对上述知识的贡献：





## 从Julia开始

在我眼中，julia语言的一大特性是：**inspect**和解释执行（当然除此之外的其他特性也会好好讲下，但和学习LLVM相关的主要发自这两个原因）



### 特性

#### inspect

JIT以及@code_llvm宏，让我们可以直接查看某一个正确的op被转换为llvm ir之后的样子，帮助我们学习llvm ir，还有一些很值得探索的宏



#### 解释执行

这个大家再熟悉不过了（Python），好处就是能够对代码进行快速验证，大幅降低编译的时间成本，这对我们进行调试和学习很重要



### Julia internal

趁这个机会，我们好好回顾下Julia的执行机制

julia有非常棒的文档，我们只需要通过文档中`Developer Documentation`（特别是其中的Working with LLVM），就可以了解大体的机制了。我会把所有内容都过一遍，因此大家也可以把这部分内容当做**简化的julia开发者文档汉化版本**



#### 暂时跳过的内容以及为什么

我们会跳过：

* runtime初始化：一些琐碎的事，应该和py比较像，需要用到再看
* AST
* 类型相关的更多信息
* julia对象的内存布局



#### julia代码的执行

![Diagram of the compiler flow](../statics/compiler_diagram.png)

整个过程的概览如下：

* 用户启动 Julia。
* 从 cli/loader_exe.c 中的 C 函数 main() 被调用。此函数处理命令行参数，填充 jl_options 结构体并设置变量 ARGS。然后初始化 Julia（通过调用 init.c 中的 julia_init，这可能会加载先前编译的 sysimg）。最后，通过调用 Base._start() 将控制权交给 Julia。
* 当 _start() 接管控制权后，后续的命令序列取决于给定的命令行参数。例如，如果提供了文件名，它将执行该文件。否则，它将启动交互式 REPL。
* 略过 REPL 如何与用户交互的细节，可以说程序最终得到了一段想要运行的代码块。
  如果要运行的代码块在文件中，将调用 jl_load(char *filename) 来加载并解析该文件。然后将每个代码片段传递给 eval 执行。
* 每个代码片段（或抽象语法树），都会被传递给 eval() 转换为结果。
  eval() 会将每个代码片段传递给 jl_toplevel_eval_flex() 进行运行。
* `jl_toplevel_eval_flex()` 函数会判断代码是否为“顶层”操作（例如 `using` 或 `module`），这些操作在函数内部是无效的。如果是，则将代码传递给顶层解释器。
  `jl_toplevel_eval_flex()` 函数接着会扩展代码以消除任何宏，并将抽象语法树（AST）“降级”以使其更易于执行。
* `jl_toplevel_eval_flex()` 函数然后使用一些简单的启发式方法来决定是即时编译（JIT）AST 还是直接解释它。
* 解释代码的大部分工作由 `interpreter.c` 中的 `eval` 函数处理。
* 如果代码被编译，大部分工作则由 `codegen.cpp` 处理。每当首次调用具有给定参数类型的 Julia 函数时，都会对该函数运行类型推断。此信息由代码生成步骤用于生成更快的代码。
* 最终，用户退出 REPL 或程序结束，`_start()` 方法返回。
* 在退出之前，`main()` 函数会调用 `jl_atexit_hook(exit_code)`。这会调用 `Base._atexit()`（它会调用在 Julia 中注册给 `atexit()` 的任何函数）。然后它会调用 `jl_gc_run_all_finalizers()`。最后，它优雅地清理所有 libuv 句柄，并等待它们完成刷新和关闭。



上面的部分涵盖了runtime的整个流程 ，我们重点关注的是下面关于compile time的流程，



##### Parsing

Julia 解析器是一个用 femtolisp 编写的小型 Lisp 程序，其源代码包含在 Julia 的 src/flisp 目录中。

与此相关的接口函数主要在 jlfrontend.scm 中定义。ast.c 中的代码负责在 Julia 端处理这种交接。

在这个阶段，其他相关的文件有 julia-parser.scm，它负责对 Julia 代码进行标记化处理并将其转换为抽象语法树（AST），还有 julia-syntax.scm，它负责将复杂的 AST 表示形式转换为更简单的、“降级”的 AST 表示形式，这种形式更适合分析和执行。



##### 宏展开

当 `eval()` 遇到宏时，它会先展开那个 AST 节点，然后再尝试评估表达式。宏展开涉及从 `eval()` （在 Julia 中）到解析函数 `jl_macroexpand()` （用 `flisp` 编写的）再到 Julia 宏本身（用what else Julia 编写的）通过 `fl_invoke_julia_macro()` ，然后再返回。



##### 类型推断

类型推断是通过在 `compiler/typeinfer.jl` 中使用 `typeinf()` 在 Julia 中实现的。类型推断是检查 Julia 函数并确定其每个变量的类型界限以及函数返回值的类型界限的过程。这使许多未来的优化成为可能，例如已知不可变值的解包和编译时提升各种运行时操作，如计算字段偏移量和函数指针。类型推断还可以包括其他步骤，如**常量传播**和**内联**。



##### JIT

julia的JIT编译器是libLLVM,代码生成（Codegen）的过程是指将 Julia AST 转换为 LLVM 指令的过程，也指 LLVM 优化这些指令并将其转换为本地汇编指令的过程。

* 即时编译环境通过在 `codegen.cpp` 中提前调用 `jl_init_codegen` 进行初始化。
* 根据需求，Julia 方法通过函数 `emit_function(jl_method_instance_t*)` 转换为本地函数。（注意：当使用 MCJIT（在 LLVM v3.4+中），每个函数都必须 JIT 到一个新模块中。）此函数递归调用 `emit_expr()` ，直到整个函数被发出。
* 大部分该文件的剩余部分都致力于各种特定代码模式的手动优化。例如， `emit_known_call()` 知道如何内联许多原始函数（定义在 `builtins.c` 中）以适应各种参数类型的组合。



* debuginfo.cpp:处理JIT函数的回溯
* ccall.cpp:处理ccall和llvmcall的ffi
* intrinsics.cpp:处理内建函数的发射



##### 系统镜像

系统镜像是一组 Julia 文件的预编译归档。与 Julia 一起分发的 `sys.ji` 文件就是这样一种系统镜像，通过执行文件 `sysimg.jl` 生成，并将生成的环境（包括类型、函数、模块和所有其他定义的值）序列化到文件中。因此，它包含 `Main` 、 `Core` 和 `Base` 模块的冻结版本（以及引导过程中环境中的其他内容）。此序列化/反序列化器由 `jl_save_system_image` / `jl_restore_system_image` 在 `staticdata.c` 中实现。



#### LLVM



#### 杂项

##### 在termux中安装

一般需要先安装一个linux发行版（因为julia不存在android-arch64的发行版）





## LLVM-IR

### SSA

static single assignment

在llvm ir中，变量是静态单赋值形式：

* 每个变量只能赋值一次
* 每次赋值会生成一个新的变量



LLVM IR是强类型的，



