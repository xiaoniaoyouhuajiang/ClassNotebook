use std::alloc::{alloc, dealloc, Layout};
#[allow(unused)]
use std::arch::asm;
#[allow(unused)]
use std::ptr;
#[allow(unused)]
use std::time::Instant;

struct JitCode {
    code: *mut u8,
    size: usize,
}

impl JitCode {
    /// 分配可执行内存
    fn new(size: usize) -> Option<Self> {
        let layout = Layout::from_size_align(size, 4096).ok()?;
        let code = unsafe { alloc(layout) };
        if code.is_null() {
            return None;
        }

        // 设置内存为可读、可写、可执行（需平台相关代码）
        #[cfg(target_os = "linux")]
        unsafe {
            libc::mprotect(
                code as *mut libc::c_void,
                size,
                libc::PROT_READ | libc::PROT_WRITE | libc::PROT_EXEC,
            );
        }

        Some(Self { code, size })
    }

    #[allow(unused)]
    /// 动态生成加法函数 (x + y)
    fn generate_add(&mut self) -> Option<fn(i32, i32) -> i32> {
        let code = unsafe { std::slice::from_raw_parts_mut(self.code, self.size) };

        // x86_64 机器码: mov eax, edi; add eax, esi; ret
        #[cfg(target_arch = "x86_64")]
        let inst = [0x89, 0xF8, 0x01, 0xF0, 0xC3]; 

        // ARM64 机器码: add w0, w0, w1; ret
        #[cfg(target_arch = "aarch64")]
        let inst = [0x00, 0x00, 0x01, 0x0B, 0xC0, 0x03, 0x5F, 0xD6];

        code[..inst.len()].copy_from_slice(&inst);
        Some(unsafe { std::mem::transmute(self.code) })
    }

    #[allow(unused)]
    /// 动态生成优化后的乘法函数 (x * y) with 常量折叠
    fn generate_mul(&mut self, x: i32) -> Option<fn(i32) -> i32> {
        let code = unsafe { std::slice::from_raw_parts_mut(self.code, self.size) };

        // 如果乘数为 0，直接返回 0（优化）
        if x == 0 {
            // x86_64: xor eax, eax; ret
            #[cfg(target_arch = "x86_64")]
            code[..2].copy_from_slice(&[0x31, 0xC0, 0xC3]);
            return Some(unsafe { std::mem::transmute(self.code) });
        }

        // 动态生成: mov eax, edi; imul eax, <x>; ret
        #[cfg(target_arch = "x86_64")]
        {
            code[0] = 0x89; code[1] = 0xF8;  // mov eax, edi
            code[2] = 0x69; code[3] = 0xC0;  // imul eax, eax, <x>
            code[4..8].copy_from_slice(&x.to_le_bytes());
            code[8] = 0xC3;                  // ret
        }

        Some(unsafe { std::mem::transmute(self.code) })
    }
}

impl Drop for JitCode {
    fn drop(&mut self) {
        let layout = Layout::from_size_align(self.size, 4096).unwrap();
        unsafe { dealloc(self.code, layout); }
    }
}

#[test]
fn test_jit() {
    // 示例1：动态生成加法函数
    let mut jit_add = JitCode::new(4096).unwrap();
    let add = jit_add.generate_add().unwrap();
    println!("10 + 20 = {}", add(10, 20)); // 输出 30

    // 示例2：动态生成优化后的乘法函数（常量折叠）
    let mut jit_mul = JitCode::new(4096).unwrap();
    let mul = jit_mul.generate_mul(5).unwrap();
    println!("7 * 5 = {}", mul(7)); // 输出 35

    // 性能对比：JIT vs 解释执行
    let start = Instant::now();
    let mut sum = 0;
    for _ in 0..1_000_000 {
        sum += add(1, 2);
    }
    println!("JIT耗时: {:?}", start.elapsed());

    let start = Instant::now();
    let mut sum = 0;
    for _ in 0..1_000_000 {
        sum += (|a, b| a + b)(1, 2);
    }
    println!("解释执行耗时: {:?}", start.elapsed());
}