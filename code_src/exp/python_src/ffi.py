import ctypes

# 加载共享库
lib = ctypes.CDLL("../ffi_example/target/release/libffi_example.so")

# 调用 Rust 函数
result_add = lib.add(2, 3)
result_multiply = lib.multiply(2, 3)

print(f"Sum: {result_add}")  # 输出: Sum: 5
print(f"Product: {result_multiply}")  # 输出: Product: 6