#![feature(optimize_attribute)]
// for n_body
pub mod matmul;
pub mod n_body;
pub mod n_body_safe;
// use nalgebra;
pub use matmul::{matmul_o1, matmul_o2, matmul_o4_1, matmul_o4_2, matmul_o3_1, 
    matmul_o3_2, generate_matrices, static_matmul};
pub use n_body::main as n_body_main;
pub use n_body_safe::main as n_body_safe_main;
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
