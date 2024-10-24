pub mod matmul;
pub use matmul::matmul_o1;

fn main() {
    let a = vec![vec![1.0, 2.0], vec![3.0, 4.0]];
    let b = vec![vec![5.0, 6.0], vec![7.0, 8.0]];
    let c = matmul_o1(&a, &b);
    println!("{:?}", c);
}
