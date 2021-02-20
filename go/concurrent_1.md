# 为什么并发/并行(concurrency)是困难的

## Race Conditions

```go
var data int
go func() {
    data++
}()
if data == 0{
    fmt.Printf("the value is %v.\n", data)
}
```

这段代码的执行结果一共有3中可能。