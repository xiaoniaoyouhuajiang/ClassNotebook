#[allow(unused_variables, dead_code)]
#[test]
fn test_collection_lifetime() {
    let mut v = vec![1i32, 2, 3, 4];
    let tem = v.get(2);
    v[2] += 1;
    // 上述代码不会出错，因为非词法生命周期的存在：
    // https://stackoverflow.com/questions/50251487/what-are-non-lexical-lifetimes
    // 所以想要它报错就注释掉下面的代码
    // println!("{:?}", tem);
}