use criterion::{criterion_group, criterion_main, Criterion, BenchmarkId};

use exp::matmul::{matmul_o1, matmul_orignal};

fn generate_matrices() -> (Vec<Vec<f64>>, Vec<Vec<f64>>) {
    let a = vec![vec![1.0, 2.0, 3.0, 4.0], vec![5.0, 6.0, 7.0, 8.0], vec![9.0, 10.0, 11.0, 12.0], vec![13.0, 14.0, 15.0, 16.0]];
    let b = vec![vec![1.0, 2.0, 3.0, 4.0], vec![5.0, 6.0, 7.0, 8.0], vec![9.0, 10.0, 11.0, 12.0], vec![13.0, 14.0, 15.0, 16.0]];
    (a, b)
}

fn bench_matmul_orignal(c: &mut Criterion) {
    let mut group = c.benchmark_group("Matrix Multiplication Orignal");
    let (a, b) = generate_matrices();
    group.bench_with_input(BenchmarkId::new("4x4", "4"), &(), |bench, _| {
        bench.iter(|| matmul_orignal(a.clone(), b.clone()));
    });
    group.finish();
}

fn bench_matmul_reference(c: &mut Criterion) {
    let mut group = c.benchmark_group("Matrix Multiplication Reference");
    let (a, b) = generate_matrices();
    group.bench_with_input(BenchmarkId::new("4x4", "4"), &(), |bench, _| {
        bench.iter(|| matmul_o1(&a, &b));
    });
    group.finish();
}

criterion_group!(matrix_multiply, bench_matmul_orignal, bench_matmul_reference);
criterion_main!(matrix_multiply);

