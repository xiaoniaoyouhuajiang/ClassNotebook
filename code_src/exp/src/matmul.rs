use rayon::prelude::*;
use rand::Rng;
use rand::distributions::{Standard, Distribution};
// 编译优化就不使用单独函数来演示了

pub fn random_dynamic_matrix<T>(rows: usize, cols: usize) -> Vec<Vec<T>>
where Standard: Distribution<T>,
{
    let mut rng = rand::thread_rng();
    (0..rows)
        .map(|_| (0..cols).map(|_| rng.gen::<T>()).collect())
        .collect()
}


pub fn generate_matrices<T>() -> (Vec<Vec<T>>, Vec<Vec<T>>)
where Standard: Distribution<T>,
{
    let a = random_dynamic_matrix::<T>(4096, 4096);
    let b = random_dynamic_matrix::<T>(4096, 4096);
    (a, b)
}

pub fn matmul_orignal(a: Vec<Vec<f64>>, b: Vec<Vec<f64>>) -> Vec<Vec<f64>> {
    let mut result = vec![vec![0.0; b[0].len()]; a.len()];

    for i in 0..a.len() {
        for j in 0..b[0].len() {
            for k in 0..b.len() {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    result
}

pub fn matmul_o1<T>(a: &Vec<Vec<T>>, b: &Vec<Vec<T>>) -> Vec<Vec<T>> 
where
    T: std::ops::Mul<Output = T> + Default + Copy + std::ops::AddAssign,
{
    let mut result = vec![vec![T::default(); b[0].len()]; a.len()];

    for i in 0..a.len() {
        for j in 0..b[0].len() {
            for k in 0..b.len() {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    result
}

// loop order
pub fn matmul_o2<T>(a: &Vec<Vec<T>>, b: &Vec<Vec<T>>) -> Vec<Vec<T>> 
where
    T: std::ops::Mul<Output = T> + Default + Copy + std::ops::AddAssign,
{
    let mut result = vec![vec![T::default(); b[0].len()]; a.len()];

    for i in 0..a.len() {
        for k in 0..b.len() {
            for j in 0..b[0].len() {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    result
}

pub fn matmul_o3_1<T>(a: &Vec<Vec<T>>, b: &Vec<Vec<T>>) -> Vec<Vec<T>> 
where
    T: Send + Sync + Copy + Default 
    + std::ops::Mul<Output = T> + std::ops::Add<Output = T>
    + std::iter::Sum,
{
    let mut result = vec![vec![T::default(); b[0].len()]; a.len()];

    // 只对化外层并行循环
    result.par_iter_mut().enumerate().for_each(|(i, row)| {
        row.iter_mut().enumerate().for_each(|(j, elem)| {
            *elem = a[i].iter()
                .zip(b.iter())
                .map(|(&ai, bj)| ai * bj[j])
                .sum();
        });
    });

    result
}

pub fn matmul_o3_2<T>(a: &Vec<Vec<T>>, b: &Vec<Vec<T>>) -> Vec<Vec<T>>
where
    T: Send + Sync + Copy + Default 
    + std::ops::Mul<Output = T> + std::ops::Add<Output = T>
    + std::iter::Sum,
{
    let mut result = vec![vec![T::default(); b[0].len()]; a.len()];

    // 并行化外层循环
    result.par_iter_mut().enumerate().for_each(|(i, row)| {
        // 并行化内层循环
        row.par_iter_mut().enumerate().for_each(|(j, elem)| {
            *elem = a[i].iter()
                .zip(b.iter())
                .map(|(&ai, bj)| ai * bj[j])
                .sum();
        });
    });

    result
}

// tiled matrix
pub fn matmul_o4_1<T>(a: &Vec<Vec<T>>, b: &Vec<Vec<T>>, block_size: usize) -> Vec<Vec<T>> 
where
    T: std::ops::Mul<Output = T> + Default + Copy + std::ops::AddAssign,
{
    let mut result = vec![vec![T::default(); b[0].len()]; a.len()];
    let min_size = block_size.min(a.len()).min(b[0].len());
    for ih in (0..a.len()).step_by(min_size) {
        for jh in (0..b[0].len()).step_by(min_size) {
            for kh in (0..b.len()).step_by(min_size) {
                for il in 0..min_size {
                    for kl in 0..min_size {
                        for jl in 0..min_size {
                            result[ih + il][jh + jl] += a[ih + il][kh + kl] * b[kh + kl][jh + jl];
                        }
                    }
                }
            }
        }
    }
    result
}

// nalgebra
pub fn matmul_o4_2<T>(a: &Vec<Vec<T>>, b: &Vec<Vec<T>>, block_size: usize) -> Vec<Vec<T>>
where
    T: std::ops::Mul<Output = T> + Default + Copy + std::ops::AddAssign + Sync + Send,
{
    let mut result = vec![vec![T::default(); b[0].len()]; a.len()];
    let min_size = block_size.min(a.len()).min(b[0].len());

    // 并行化处理每个块
    result.par_iter_mut().enumerate().for_each(|(i, row)| {
        row.par_iter_mut().enumerate().for_each(|(j, elem)| {
            for kh in (0..b.len()).step_by(min_size) {
                for kl in 0..min_size {
                    *elem += a[i][kh * min_size + kl] * b[kh * min_size + kl][j];
                }
            }
        });
    });

    result
}

pub fn static_matmul()
{
    let matrix = vec![vec![0; 4096]; 4096];
    let mut result = vec![vec![0; 4096]; 4096];

    // 只对化外层并行循环
    result.par_iter_mut().enumerate().for_each(|(i, row)| {
        row.iter_mut().enumerate().for_each(|(j, elem)| {
            *elem = matrix[i].iter()
                .zip(matrix.iter())
                .map(|(&ai, bj)| ai * bj[j])
                .sum();
        });
    });
}


#[test]
fn test() {
    let (a, b) = generate_matrices::<i32>();
    assert_eq!(matmul_o1(&a, &b), matmul_o4_1(&a, &b, 64));
}
