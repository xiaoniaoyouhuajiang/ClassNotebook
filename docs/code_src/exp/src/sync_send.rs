#[allow(unused_variables, dead_code)]
struct Rc<T> {
    inner: Box<Inner<T>>
}
#[allow(unused_variables, dead_code)]
struct Inner<T> {
    count: usize,
    value: T
}

#[allow(unused_variables, dead_code)]
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
