use std::sync::atomic::{AtomicBool, Ordering};
use std::cell::UnsafeCell;

struct Mutex<T> {
    locked: AtomicBool,
    v: UnsafeCell<T>,
}

unsafe impl<T> Sync for Mutex<T> where T: Send {}

#[allow(unused)]
impl<T> Mutex<T> {
    pub fn new(t: T) -> Self {
        Self {
            locked: AtomicBool::new(false),
            v: UnsafeCell::new(t),
        }
    }
    
    // 不能编译：不知道load的Ordering参数该是啥
    pub fn with_lock<R>(&self, f: impl FnOnce(&mut T) -> R) -> R {
        // while self.locked.load(Ordering::Relaxed) == true {}
        // self.locked.store(true, Ordering::Relaxed);
        while self.locked.compare_exchange(false, true, Ordering::Acquire, Ordering::Relaxed).is_err() {
            while self.locked.load(Ordering::Relaxed) == true {
                std::thread::yield_now();
            }
        }
        let ret = f(unsafe {&mut *self.v.get()});
        self.locked.store(false, Ordering::Release);
        ret
    }
}

#[test]
fn test_mutex() {
    use std::thread;
    let mutex: &'static _ = Box::leak(Box::new(Mutex::new(0)));
    let start_time = std::time::Instant::now();
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
    let elapsed = start_time.elapsed();
    println!("elapsed: {:?}", elapsed);
    assert_eq!(mutex.with_lock(|v| *v), 100_000);
}

#[test]
fn test_atomic() {
    use std::thread;
    use std::sync::Arc;
    use std::sync::atomic::{AtomicUsize, Ordering};

    let shared = Arc::new(AtomicUsize::new(0));
    let mut handles = vec![];
    let start_time = std::time::Instant::now();
    for _ in 0..100 {
        let shared = Arc::clone(&shared);
        let handle = thread::spawn(move || {
            for _ in 0..1000 {
                shared.fetch_add(1, Ordering::Relaxed);
            }
        });
        handles.push(handle);
    }
    for handle in handles {
        handle.join().unwrap();
    }
    let elapsed = start_time.elapsed();
    println!("elapsed: {:?}", elapsed);
    assert_eq!(shared.load(Ordering::Relaxed), 100_000);
}
