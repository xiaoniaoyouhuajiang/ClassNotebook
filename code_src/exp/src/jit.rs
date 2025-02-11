use std::alloc::{alloc, dealloc, Layout};
use std::ptr;
use std::ops::{Index, IndexMut};

#[allow(unused)]
const PAGE_SIZE: usize = 4096;

#[allow(unused)]
struct JitMemory {
    contents: *mut u8,
    size: usize,
}

impl JitMemory {
    #[allow(unused)]
    fn new(num_pages: usize) -> Option<Self> {
        let size = num_pages * PAGE_SIZE;

        // 分配对齐的内存
        let layout = Layout::from_size_align(size, PAGE_SIZE).ok()?;
        let contents = unsafe { alloc(layout) };

        if contents.is_null() {
            return None; // 分配失败
        }

        // 初始化内存为 0xc3 (RET 指令)
        unsafe {
            ptr::write_bytes(contents, 0xc3, size);
        }

        // 设置内存为可执行
        if unsafe { libc::mprotect(contents as *mut libc::c_void, size, libc::PROT_EXEC | libc::PROT_READ | libc::PROT_WRITE) } != 0 {
            unsafe { dealloc(contents, layout); } // 释放内存
            return None; // mprotect 失败
        }

        Some(JitMemory { contents, size })
    }
}

impl Drop for JitMemory {
    fn drop(&mut self) {
        let layout = Layout::from_size_align(self.size, PAGE_SIZE).expect("Invalid layout");
        unsafe { dealloc(self.contents, layout); }
    }
}

impl Index<usize> for JitMemory {
    type Output = u8;

    fn index(&self, index: usize) -> &u8 {
        unsafe { &*self.contents.add(index) }
    }
}

impl IndexMut<usize> for JitMemory {
    fn index_mut(&mut self, index: usize) -> &mut u8 {
        unsafe { &mut *self.contents.add(index) }
    }
}

#[allow(unused)]
fn run_jit() -> Option<fn() -> i64> {
    let mut jit = JitMemory::new(1)?;

    jit[0] = 0x48;  // mov RAX, 0x3
    jit[1] = 0xc7;
    jit[2] = 0xc0;
    jit[3] = 0x3;
    jit[4] = 0;
    jit[5] = 0;
    jit[6] = 0;

    Some(unsafe { std::mem::transmute(jit.contents) })
}

#[test]
fn test_run_jit() {
    if let Some(fun) = run_jit() {
        println!("{}", fun());
    } else {
        eprintln!("Failed to create JIT function");
    }
}