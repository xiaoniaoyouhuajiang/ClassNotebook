use std::sync::atomic::{AtomicBool, Ordering};
use std::cell::UnsafeCell;

struct Mutex<T> {
    locked: AtomicBool,
    v: UnsafeCell<T>,
}

unsafe impl<T> Sync for Mutex<T> where T: Send {}

impl<T> Mutex<T> {
    pub fn new(t: T) -> Self {
        Self {
            locked: AtomicBool::new(false),
            v: UnsafeCell::new(t),
        }
    }
    
    // 不能编译：不知道load的Ordering参数该是啥
    pub fn with_lock<R>(&self, f: impl FnOnce(&mut T) -> R) -> R {
        while self.locked.load(Ordering::Relaxed) == true {}
        self.locked.store(true, Ordering::Relaxed);
        let ret = f(unsafe {&mut *self.v.get()});
        self.locked.store(false, Ordering::Relaxed);
        ret
    }
}

#[test]
fn test_mutex() {
    use std::thread;
    let mutex: &'static _ = Box::leak(Box::new(Mutex::new(0)));
    let handles: Vec<_> = (0..100).map(|_| {
        thread::spawn(move || {
            for _ in 0..1000 {
                mutex.with_lock(|v| {
                    *v += 1;
                });
                }
        })
        }).collect();
    for handle in handles {
        handle.join().unwrap();
    }
    assert_eq!(mutex.with_lock(|v| *v), 100_000);
}