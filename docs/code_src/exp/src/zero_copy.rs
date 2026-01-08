use std::{borrow::Cow, fmt::Error, rc::Rc};
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

#[test]
fn test_cow_exp() {
    use std::path::Path;
    let path = Path::new("/tmpá€中™fo�o");
    match path.to_string_lossy() {
        Cow::Borrowed(_str_ref) => println!("path was valid UTF-8"),
        Cow::Owned(_new_string) => println!("path was not valid UTF-8"),
    }
}

#[test]
fn test_zero_copy_deserialize() {
    use serde_json::json;
    use tempfile::NamedTempFile;
    use std::io::Write;
    use memmap2::MmapOptions;
    use std::fs::File;

    #[derive(Deserialize)]
    struct Person<'a> {
        #[serde(borrow)]
        name: Cow<'a, str>,
        age: u32,
        #[serde(borrow)]
        email: Cow<'a, str>,
    }
    // 先创建一个临时文件，并写入一些JSON数据
    // test结束后，临时文件会被自动删除
    let mut temp_file = NamedTempFile::new().unwrap();
    let data = json!({
        "name": "Alice",
        "age": 30,
        "email": "alice@example.com"
    });
    writeln!(temp_file, "{}", data.to_string()).unwrap();
    let temp_path = temp_file.path();
    
    // 将临时文件映射到内存中
    let file = File::open(temp_path).unwrap();
    let mmap = unsafe {
        MmapOptions::new()
            .map(&file)
            .expect("Failed to mmap file")
    };
    let mmap_start = mmap.as_ptr() as usize;
    let mmap_end = mmap_start + mmap.len();
    println!("mmap memory range: {:#x} - {:#x}", mmap_start, mmap_end);

    // 反序列化，并检查name和email是否在mmap内存范围内
    let person: Person = serde_json::from_slice(&mmap).expect("Failed to deserialize JSON");
    let name_ptr = person.name.as_ptr() as usize;
    let email_ptr = person.email.as_ptr() as usize;
    println!("name address: {:#x}", name_ptr);
    println!("email address: {:#x}", email_ptr);
    assert!(
        name_ptr >= mmap_start && name_ptr < mmap_end,
        "name is not within mmap memory range"
    );
    assert!(
        email_ptr >= mmap_start && email_ptr < mmap_end,
        "email is not within mmap memory range"
    );
}

#[test]
fn test_yoke_deserialize() {
    use serde_json::json;
    use tempfile::NamedTempFile;
    use std::io::Write;
    use memmap2::MmapOptions;
    use std::fs::File;

    #[derive(yoke::Yokeable, Deserialize)]
    struct Person<'a> {
        #[serde(borrow)]
        name: Cow<'a, str>,
        age: u32,
        #[serde(borrow)]
        email: Cow<'a, str>,
    }

    let des = {
    // 先创建一个临时文件，并写入一些JSON数据
    // test结束后，临时文件会被自动删除
    let mut temp_file = NamedTempFile::new().unwrap();
    let data = json!({
        "name": "Alice",
        "age": 30,
        "email": "alice@example.com"
    });
    writeln!(temp_file, "{}", data.to_string()).unwrap();
    let temp_path = temp_file.path();
    
    // 将临时文件映射到内存中
    let file = File::open(temp_path).unwrap();
    let mmap = unsafe {
        MmapOptions::new()
            .map(&file)
            .expect("Failed to mmap file")
    };
    let mmap_start = mmap.as_ptr() as usize;
    let mmap_end = mmap_start + mmap.len();
    println!("mmap memory range: {:#x} - {:#x}", mmap_start, mmap_end);

    let person = yoke::Yoke::<Person<'static>, memmap2::Mmap>::try_attach_to_cart(
        mmap, |data| { let cow: Person = serde_json::from_slice(data).expect("Failed to deserialize JSON"); Ok::<_, Error>(cow) }
    );

    let person = person.expect("Failed to attach to cart");
    let name_ptr = person.get().name.as_ptr() as usize;
    let email_ptr = person.get().email.as_ptr() as usize;
    println!("name address: {:#x}", name_ptr);
    println!("email address: {:#x}", email_ptr);
    assert!(
        name_ptr >= mmap_start && name_ptr < mmap_end,
        "name is not within mmap memory range"
    );
    assert!(
        email_ptr >= mmap_start && email_ptr < mmap_end,
        "email is not within mmap memory range"
    );
    person
    };
    let name_ptr = des.get().name.as_ptr() as usize;
    let email_ptr = des.get().email.as_ptr() as usize;
    println!("name address: {:#x}", name_ptr);
    println!("email address: {:#x}", email_ptr);
}

#[test]
fn test_lifetime() {
    struct StrSpilt<'a> {
        remainder: Option<&'a str>,
        delimiter: &'a str,
    }

    impl<'a> StrSpilt<'a> {
        fn new(s: &'a str, delimiter: &'a str) -> Self {
            StrSpilt { remainder: Some(s), delimiter }
        }
    }

    impl<'a> Iterator for StrSpilt<'a> {
        type Item = &'a str;

        fn next(&mut self) -> Option<Self::Item> {
            if let Some(ref remainder) = self.remainder {
                if let Some(next_delimiter) = remainder.find(self.delimiter) {
                    let until_delimiter = &remainder[..next_delimiter];
                    self.remainder = Some(&remainder[next_delimiter + self.delimiter.len()..]);
                    Some(until_delimiter)
                } else {
                    self.remainder.take()
                }
            } else {
                None
            }
        }
    }

    let heystack = "a,b,c,d,e";
    let letters: Vec<_> = StrSpilt::new(heystack, ",").collect();
    assert_eq!(letters, vec!["a", "b", "c", "d", "e"]);

    let heystack = "a,b,c,d,";
    let letters: Vec<_> = StrSpilt::new(heystack, ",").collect();
    assert_eq!(letters, vec!["a", "b", "c", "d", ""])
}
