// src/runtime/poll.rs

use crate::runtime::kqueue_ffi as ffi;
use std::io::{self, Result};
use std::os::unix::io::AsRawFd; // 用于获取文件描述符
use std::ptr;
use std::time::Duration;
use std::net::TcpStream; // 直接使用std::net::TcpStream
use libc::uintptr_t; // 导入uintptr_t

// 事件类型别名，使用我们的包装器
pub type Events = Vec<ffi::Event>;

// kqueue的注册器
#[derive(Debug)]
pub struct Registry {
    kq: i32, // kqueue文件描述符
}

impl Registry {
    // 注册对事件源的兴趣
    pub fn register(&self, source: &TcpStream, token: usize, interests: i16) -> Result<()> {
        // 使用EV_CLEAR模拟边缘触发行为
        // 或使用EV_ONESHOT进行单次通知
        let flags = ffi::EV_ADD | ffi::EV_ENABLE | ffi::EV_CLEAR;

        let kev = ffi::kevent {
            ident: source.as_raw_fd() as uintptr_t, // fd作为标识符
            filter: interests,                      // 例如EVFILT_READ
            flags,
            fflags: 0,
            data: 0,
            udata: token as *mut libc::c_void, // 将token存储在udata中
        };

        let changelist = [kev];
        let nchanges = 1;
        let eventlist = ptr::null_mut(); // 此处不获取事件
        let nevents = 0;
        let timeout = ptr::null(); // 注册无超时

        let res = unsafe {
            ffi::kevent(
                self.kq,
                changelist.as_ptr(),
                nchanges,
                eventlist,
                nevents,
                timeout,
            )
        };

        if res == -1 {
            Err(io::Error::last_os_error())
        } else {
            Ok(())
        }
    }

    // 注销(可选，通常由close或EV_DELETE处理)
    #[allow(unused)]
    pub fn deregister(&self, source: &TcpStream) -> Result<()> {
         let kev = ffi::kevent {
            ident: source.as_raw_fd() as uintptr_t,
            filter: ffi::EVFILT_READ, // 假设使用了读过滤器
            flags: ffi::EV_DELETE,
            fflags: 0,
            data: 0,
            udata: ptr::null_mut(),
        };
        let changelist = [kev];
        // ... 其余部分与register类似，调用kevent ...
        // 为简洁起见简化了，需要适当实现
         let res = unsafe {
            ffi::kevent(
                self.kq,
                changelist.as_ptr(),
                1, // nchanges
                ptr::null_mut(), // eventlist
                0, // nevents
                ptr::null(), // timeout
            )
        };
         if res == -1 {
            Err(io::Error::last_os_error())
        } else {
            Ok(())
        }
    }
}

// 包装kqueue的Poll结构体
#[derive(Debug)]
pub struct Poll {
    registry: Registry,
}

impl Poll {
    pub fn new() -> Result<Self> {
        let kq = unsafe { ffi::kqueue() };
        if kq == -1 {
            Err(io::Error::last_os_error())
        } else {
            Ok(Self {
                registry: Registry { kq },
            })
        }
    }

    pub fn registry(&self) -> &Registry {
        &self.registry
    }

    // 轮询事件，阻塞直到就绪或超时
    pub fn poll(&self, events: &mut Events, timeout: Option<Duration>) -> Result<()> {
        let kq = self.registry.kq;
        let changelist = ptr::null(); // 不做修改，只是轮询
        let nchanges = 0;

        let eventlist_ptr = events.as_mut_ptr() as *mut ffi::kevent;
        let capacity = events.capacity() as i32;

        // 准备超时
        let timespec; // 必须存活足够长时间
        let timeout_ptr = match timeout {
            Some(dur) => {
                timespec = libc::timespec {
                    tv_sec: dur.as_secs() as libc::time_t,
                    // 注意纳秒>10亿时的截断问题
                    tv_nsec: dur.subsec_nanos() as libc::c_long,
                };
                &timespec as *const _ // 获取timespec的指针
            }
            None => ptr::null(), // 无限等待
        };

        let num_events = unsafe {
            ffi::kevent(
                kq,
                changelist,
                nchanges,
                eventlist_ptr, // Pass our buffer
                capacity,      // Max events to receive
                timeout_ptr,
            )
        };

        if num_events == -1 {
            Err(io::Error::last_os_error())
        } else {
            // 重要：更新用户提供的vector长度
            unsafe {
                events.set_len(num_events as usize);
            }
            Ok(())
        }
    }
}

// 实现Drop以关闭kqueue文件描述符
impl Drop for Poll {
    fn drop(&mut self) {
        let res = unsafe { ffi::close(self.registry.kq) };
        if res == -1 {
            // 考虑记录错误，但避免在drop中panic
            eprintln!("Error closing kqueue fd: {}", io::Error::last_os_error());
        }
    }
}

// 定义类似mio的Interest常量
pub mod interest {
    use super::ffi;
    pub const READABLE: i16 = ffi::EVFILT_READ;
    // pub const WRITABLE: i16 = ffi::EVFILT_WRITE;
}
