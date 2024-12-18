#![feature(optimize_attribute)]
// for n_body
#![allow(
    non_upper_case_globals,
    non_camel_case_types,
    non_snake_case,
)]
pub mod matmul;
// use nalgebra;
pub use matmul::{matmul_o1, matmul_o2, matmul_o4_1, matmul_o4_2, matmul_o3_1, 
    matmul_o3_2, generate_matrices, static_matmul};
use rand;

/* 
矩阵size: 1280 * 1280
命令记录：
cargo build --release
valgrind --tool=cachegrind ./target/release/exp

记录cache利用情况：
普通转置矩阵乘：
block64_转置矩阵乘：
*/
fn main() {
    // let (a, b) = generate_matrices::<i32>();
    let m = 
        nalgebra::DMatrix::from_element(256, 256, rand::random::<f32>());
    let start_time = std::time::Instant::now();
    static_matmul();
    let end_time = std::time::Instant::now();
    println!("simple matrix multiplication time: {:?}", end_time - start_time);
    let start_time = std::time::Instant::now();
    // let _ = matmul_o3_2(&a, &b);
    let _ = &m * &m;
    let end_time = std::time::Instant::now();
    println!("blis matrix multiplication time: {:?}", end_time - start_time);
}
