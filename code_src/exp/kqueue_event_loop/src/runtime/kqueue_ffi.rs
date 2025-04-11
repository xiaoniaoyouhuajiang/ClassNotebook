#![allow(non_camel_case_types, non_snake_case)]
// 基于kqueue的FFI绑定

use libc::{c_int, c_void, intptr_t, timespec, uintptr_t};

// 基于macOS/BSD的libc定义定义kevent结构体
#[derive(Debug, Clone, Copy)] // Removed Default
#[repr(C)]
pub struct kevent {
    pub ident: uintptr_t,  // 事件的标识符
    pub filter: i16,       // 事件过滤器
    pub flags: u16,        // kqueue的动作标志
    pub fflags: u32,       // 过滤器标志值
    pub data: intptr_t,    // 过滤器数据值
    pub udata: *mut c_void, // 不透明的用户数据标识符
}

// kqueue过滤器和标志的常量（常用值）
// Filters
pub const EVFILT_READ: i16 = -1;
// pub const EVFILT_WRITE: i16 = -2; // Not used in this example

// Flags
pub const EV_ADD: u16 = 0x1; // 添加事件到kqueue（隐含启用）
pub const EV_ENABLE: u16 = 0x4; // 启用事件
#[allow(unused)]
pub const EV_DELETE: u16 = 0x2; // 从kqueue删除事件
pub const EV_CLEAR: u16 = 0x20; // 检索后清除事件状态（模拟边缘触发）
// pub const EV_ONESHOT: u16 = 0x10; // 只报告一次发生

extern "C" {
    pub fn kqueue() -> c_int;

    // timespec可以为null表示无限等待
    pub fn kevent(
        kq: c_int,
        changelist: *const kevent,
        nchanges: c_int,
        eventlist: *mut kevent,
        nevents: c_int,
        timeout: *const timespec,
    ) -> c_int;

    // We still need close
    pub fn close(fd: c_int) -> c_int;
}

// 事件结构的包装器
#[derive(Debug)]
pub struct Event(pub kevent); // Tuple struct wrapping kevent

impl Event {
    // 帮助获取token(udata)作为usize返回
    pub fn token(&self) -> usize {
        self.0.udata as usize
    }
}
