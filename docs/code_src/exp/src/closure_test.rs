#[test]
fn test_move() {
    let data = vec![1, 2, 3];
    println!("{:?}", data.as_ptr());
    let closure = move || {
        println!("{:?}", data.as_ptr());
    };
    // data is moved into closure, so it can't be used here
    // println!("{:?}", data);
    closure();
}

#[test]
fn test_by_copy() {
    let mut data = 3;
    let closure = move || {
        println!("{:?}", *&data as *const usize);
    };
    data += 1;
    println!("{:?}", *&data as *const usize);
    closure();
}

#[test]
fn test_by_reference() {
    let data = 3;
    let closure = || {
        println!("{:?}", *&data as *const usize);
    };
    // data is moved into closure, so it can't be used here
    closure();
    println!("{:?}", *&data as *const usize);
}

#[test]
fn test_unique_immutable() {
    let mut b = false;
    let x: &mut bool = &mut b;
    {
        let mut c = || { *x = true; };
        // The following line is an error:
        // let y = &x;
        c();
    }
    let z = &x;
    print!("{:?}", z)
}

#[allow(unused_variables, dead_code)]
#[test]
fn test_fn_once_by_reference() {
    fn fn_once<F>(func: F)
        where
            F: FnOnce(usize) -> bool,
    {
        println!("{}", func(3));
        // println!("{}", func(4));
    }
    let x = vec![1, 2, 3];
    let closure = |z: usize | {z == x.len()};
    fn_once(closure);
    closure(4);
    closure(3);
    let y = x;
}

#[test]
fn test_fn_once_by_ownership() {
    fn fn_once<F>(func: F)
        where
            F: FnOnce() -> Vec<i32>,
    {
        func();
        // println!("{}", func());
    }
    let x = vec![1, 2, 3];
    fn_once(||{x});
    // println!("{:?}", x);
}

#[test]
fn test_fn_mut() {
    fn exec<'a, F: FnMut(&'a str)>(mut f: F) {
        f("hello");
        f(" world")
    }
    let mut s = String::new();
    let update_string =  |str| s.push_str(str);
    exec(update_string);
    println!("{:?}",s);
}

