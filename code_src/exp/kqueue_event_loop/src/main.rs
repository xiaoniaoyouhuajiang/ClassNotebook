// src/main.rs

// 使用 std::net::TcpStream 简化实现，也可以使用 mio::net::TcpStream
use std::collections::HashMap;
use std::io::{self, Read, Write};
use std::net::TcpStream;
// use std::os::unix::io::AsRawFd; // 此处未直接使用
// use std::time::Duration; // 此处未直接使用

// 从runtime模块导入
mod runtime;
use runtime::poll::{Poll, Events, interest};
use runtime::http_utils::get_req;

const SERVER_ADDR: &str = "127.0.0.1:8080"; // 确保delayserver在此地址运行

fn main() -> io::Result<()> {
    println!("启动kqueue示例客户端...");
    let poll = Poll::new()?;
    let mut events = Events::with_capacity(1024); // 事件缓冲区

    let n_requests = 5;
    // 存储流及其读取缓冲区，以token为键
    let mut streams = HashMap::new();

    // 1. 创建连接并注册
    for i in 0..n_requests {
        let delay = (n_requests - 1 - i) * 1000; // 前面的请求延迟更长
        let path = format!("/{}/request-{}", delay, i);
        println!("正在连接请求 {} ({})", i, path);

        match TcpStream::connect(SERVER_ADDR) {
            Ok(mut stream) => {
                stream.set_nonblocking(true)?; // 必须设置为非阻塞

                let request = get_req(&path);
                stream.write_all(request.as_bytes())?;
                println!("已发送请求 {}", i);

                let token = i; // 使用循环索引作为token
                poll.registry().register(
                    &stream,
                    token,
                    interest::READABLE, // 注册读事件
                )?;

                streams.insert(token, (stream, Vec::new())); // 存储流和缓冲区
            }
            Err(e) => {
                eprintln!("连接请求 {} 失败: {}", i, e);
                // 决定如何处理连接错误，可能继续？
                continue;
            }
        }
    }

    // 2. 事件循环
    let mut handled_requests = 0;
    while handled_requests < n_requests {
        println!("\n轮询事件中...");
        // 在本示例中无限等待事件
        poll.poll(&mut events, None)?; // 可以添加超时，例如 Some(Duration::from_millis(500))

        if events.is_empty() {
            println!("轮询返回无事件(超时或虚假唤醒?)");
            continue;
        }

        println!("处理 {} 个事件...", events.len());
        for event in events.iter() { // 遍历收到的事件
            let token = event.token();
            println!("  token {} 的事件:", token);

            if let Some((stream, buffer)) = streams.get_mut(&token) {
                let mut read_buf = [0u8; 4096]; // 临时读取缓冲区
                loop {
                    match stream.read(&mut read_buf) {
                        Ok(0) => {
                            // 读取0字节: 对端关闭连接
                            println!("  token {} 的连接已关闭", token);
                            // 处理完整响应
                            let response = String::from_utf8_lossy(buffer);
                            println!("=== 收到请求 {} 的响应 ===\n{}\n===", token, response);

                            // 清理: 注销并移除流
                            // poll.registry().deregister(stream)?; // 可选，close会处理
                            streams.remove(&token); // 从map中移除
                            handled_requests += 1;
                            break; // 退出内部读取循环
                        }
                        Ok(n) => {
                            // 读取n字节: 追加到该流的缓冲区
                            println!("  为token {} 读取了 {} 字节", token, n);
                            buffer.extend_from_slice(&read_buf[..n]);
                            // 继续读取以防有更多数据可用(边缘触发)
                        }
                        Err(ref e) if e.kind() == io::ErrorKind::WouldBlock => {
                            // 当前没有更多数据可读
                            println!("  token {} 遇到WouldBlock", token);
                            break; // 退出内部读取循环，等待下次轮询
                        }
                        Err(e) => {
                            // 实际错误
                            eprintln!("  从token {} 读取时出错: {}", token, e);
                            // 将此请求视为失败
                            streams.remove(&token);
                            handled_requests += 1; // 计入已处理(失败)
                            break; // 退出内部读取循环
                        }
                    }
                }
            } else {
                println!("  警告: 收到未知或已移除token {} 的事件", token);
            }
        }
        // 清空事件缓冲区用于下次轮询
        // events.clear(); // 非必须，因为poll会设置长度
    }

    println!("\n所有请求处理完成。退出。");
    Ok(())
}
