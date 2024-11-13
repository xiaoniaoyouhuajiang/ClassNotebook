use criterion::{criterion_group, criterion_main, Criterion, BenchmarkId};

use exp::matmul::{generate_matrices, matmul_o1, matmul_o2, matmul_o3_1, matmul_o3_2, matmul_o4_1, matmul_orignal};

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
    let (a, b) = generate_matrices::<f64>();
    group.bench_with_input(BenchmarkId::new("4x4", "4"), &(), |bench, _| {
        bench.iter(|| matmul_o1(&a, &b));
    });
    group.finish();
}

fn bench_matmul_order(c: &mut Criterion) {
    let mut group = c.benchmark_group("Matrix Multiplication with better order");
    let (a, b) = generate_matrices::<f64>();
    group.bench_with_input(BenchmarkId::new("4x4", "4"), &(), |bench, _| {
        bench.iter(|| matmul_o2(&a, &b));
    });
    group.finish();
}

fn bench_matmul_parallel_outter(c: &mut Criterion) {
    let mut group = c.benchmark_group("Matrix Multiplication with outter parallel");
    let (a, b) = generate_matrices::<f64>();
    group.bench_with_input(BenchmarkId::new("4x4", "4"), &(), |bench, _| {
        bench.iter(|| matmul_o3_1(&a, &b));
    });
    group.finish();
}

fn bench_matmul_parallel_all(c: &mut Criterion) {
    let mut group = c.benchmark_group("Matrix Multiplication with outter parallel");
    let (a, b) = generate_matrices::<f64>();
    group.bench_with_input(BenchmarkId::new("4x4", "4"), &(), |bench, _| {
        bench.iter(|| matmul_o3_2(&a, &b));
    });
    group.finish();
}

fn bench_matmul_tiling(c: &mut Criterion) {
    let mut group = c.benchmark_group("Matrix Multiplication with tiled matrix");
    let (a, b) = generate_matrices::<f64>();
    group.bench_with_input(BenchmarkId::new("4x4", "4"), &(), |bench, _| {
        bench.iter(|| matmul_o4_1(&a, &b, 64));
    });
    group.finish();
}

// fn bench_matmul_tiling_parallel(c: &mut Criterion) {
//     let mut group = c.benchmark_group("Matrix Multiplication with tiled matrix");
//     let (a, b) = generate_matrices();
//     group.bench_with_input(BenchmarkId::new("4x4", "4"), &(), |bench, _| {
//         bench.iter(|| matmul_o4_2(&a, &b));
//     });
//     group.finish();
// }

criterion_group!(matrix_multiply, bench_matmul_orignal, bench_matmul_reference, bench_matmul_order, bench_matmul_tiling
    , bench_matmul_parallel_outter, bench_matmul_parallel_all);
criterion_main!(matrix_multiply);

