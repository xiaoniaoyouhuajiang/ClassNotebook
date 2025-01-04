struct Rc<T> {
    inner: Box<Inner<T>>
}

struct Inner<T> {
    count: usize,
    value: T
}

impl<T> Rc<T> {
    fn new(value: T) -> Self {
        Self {
            inner: Box::new(Inner {
                count: 1,
                value: value
            })
        }
    }
}

// impl<T> Clone for Rc<T> {
//     fn clone(&self) -> Self {
//         unsafe {&mut *self.inner}.count += 1;
//         Self {
//             inner: self.inner
//         }
//     }
// }
