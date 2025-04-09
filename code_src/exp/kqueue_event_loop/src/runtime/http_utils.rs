// src/runtime/http_utils.rs

// Helper function to create a simple GET request string
pub fn get_req(path: &str) -> String {
    format!(
        "GET {} HTTP/1.1\r\n\
         Host: localhost\r\n\
         Connection: close\r\n\
         \r\n", // Important: empty line signifies end of headers
        path
    )
}