## cpu微架构

## 其他基础知识

### RV32I

**RV32I** 是RISC-V指令集的基础配置：
- **RV** = RISC-V架构
- **32** = 32位地址空间和寄存器宽度
- **I** = Integer基础整数指令集（约40条指令）

这是最小的可用RISC-V指令集，包括算术运算、逻辑运算、加载/存储、分支跳转等基本指令。其他扩展如M（乘除法）、A（原子操作）、C（压缩指令）等可以在I基础上添加。

### CPU的"Tick"及其模拟

**Tick**（时钟周期）是CPU执行的最小时间单位：
- 每个tick代表一个时钟周期
- 在这个周期内，CPU完成一部分工作（如取指、译码、执行等）

**简单的模拟**：
```rust
struct CPU {
    pc: u32,           // 程序计数器
    registers: [u32; 32],
    memory: Vec<u8>,
    // ... 其他状态
}

impl CPU {
    fn tick(&mut self) {
        // 1. 取指 (Fetch)
        let instruction = self.fetch();
        
        // 2. 译码 (Decode)
        let decoded = self.decode(instruction);
        
        // 3. 执行 (Execute)
        self.execute(decoded);
        
        // 4. 更新PC
        self.pc += 4;
    }
    
    fn run(&mut self) {
        loop {
            self.tick();  // 每次调用代表一个时钟周期
        }
    }
}
```

### 如何模拟CPU流水线

#### 五级流水线

**五级流水线模拟**：
```rust
struct Pipeline {
    // 五个流水线阶段
    if_stage: Option<IFStage>,    // Instruction Fetch
    id_stage: Option<IDStage>,    // Instruction Decode
    ex_stage: Option<EXStage>,    // Execute
    mem_stage: Option<MEMStage>,  // Memory Access
    wb_stage: Option<WBStage>,    // Write Back
}

impl Pipeline {
    fn tick(&mut self) {
        // 反向执行避免数据冲突
        self.write_back();
        self.memory_access();
        self.execute();
        self.decode();
        self.fetch();
    }
}
```

流水线需要处理冒险（hazards）：
- **数据冒险**：后续指令依赖前面指令结果 → 需要前递（forwarding）或停顿（stall）
- **控制冒险**：分支指令 → 需要分支预测或清空流水线
- **结构冒险**：资源冲突 → 教育模拟器通常忽略

### 外设设备详解

#### **DTB (Device Tree Blob)**
- **作用**：设备树二进制文件，描述硬件配置
- **功能**：告诉操作系统系统中有哪些设备、内存布局、中断配置等
- **模拟**：通常在启动时加载到内存特定位置，传递给内核

#### **CLINT (Core-Local Interruptor)**
- **作用**：核心本地中断器
- **功能**：
  - 提供机器态定时器中断（MTIP）
  - 提供软件中断（MSIP）用于核间通信
- **关键寄存器**：
  - `mtime`：当前时间计数器
  - `mtimecmp`：比较值，mtime≥mtimecmp时触发中断

#### **PLIC (Platform-Level Interrupt Controller)**
- **作用**：平台级中断控制器
- **功能**：管理外部中断（如UART、硬盘等设备）
- **特性**：支持中断优先级、多核中断路由

#### **UART (Universal Asynchronous Receiver/Transmitter)**
- **作用**：串口通信设备
- **功能**：用于字符输入/输出（通常是控制台）
- **模拟示例**：
```rust
struct UART {
    data: u8,  // 数据寄存器
}

impl UART {
    fn write(&mut self, value: u8) {
        print!("{}", value as char);  // 输出到终端
    }
}
```

#### **VirtIO**
- **作用**：虚拟化I/O设备标准接口
- **功能**：提供标准化的虚拟设备（块设备、网络、GPU等）
- **优势**：简化设备驱动开发，提高性能
- **常见设备**：
  - virtio-blk：块设备（虚拟硬盘）
  - virtio-net：网络设备
  - virtio-console：控制台
