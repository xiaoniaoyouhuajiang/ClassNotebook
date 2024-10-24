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

pub fn matmul_o1(a: &Vec<Vec<f64>>, b: &Vec<Vec<f64>>) -> Vec<Vec<f64>> {
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
