
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
