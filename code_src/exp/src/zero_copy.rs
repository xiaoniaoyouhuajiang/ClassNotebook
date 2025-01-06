use std::borrow::Cow;
use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize)]
pub struct Person<'a> {
    age: u8,
    #[serde(borrow)]
    name: Cow<'a, str>,
}

pub fn abs_all(input: &mut Cow<'_, [i32]>) {
    for i in 0..input.len() {
        let v = input[i];
        if v < 0 {
            // Clones into a vector if not already owned.
            input.to_mut()[i] = -v;
        }
    }
}

#[test]
fn test_cow_with_copy() {
    let slice = [0, -1, 2];
    let mut input = Cow::from(&slice);
    println!("{:?}", slice.as_ptr());
    println!("{:?}", input.as_ptr());
    println!("{:?}", *&slice[1] as *const i32);
    println!("{:?}", *&input[1] as *const i32);
    abs_all(&mut input);
    println!("{:?}", slice.as_ptr());
    println!("{:?}", input.as_ptr());
    println!("{:?}", *&slice[1] as *const i32);
    println!("{:?}", *&input[1] as *const i32);
}

#[test]
fn test_cow_without_copy() {
    let slice = [0, 1, 2];
    let mut input = Cow::from(&slice);
    println!("{:?}", slice.as_ptr());
    println!("{:?}", input.as_ptr());
    println!("{:?}", *&slice[1] as *const i32);
    println!("{:?}", *&input[1] as *const i32);
    abs_all(&mut input);
    println!("{:?}", slice.as_ptr());
    println!("{:?}", input.as_ptr());
    println!("{:?}", *&slice[1] as *const i32);
    println!("{:?}", *&input[1] as *const i32);
}