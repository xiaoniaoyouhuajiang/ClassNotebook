#[test]
fn test_static() {
    trait Drawable {
        fn draw(&self);
    }
    
    // 实现Drawable trait的Circle结构体
    struct Circle {
        radius: f64,
    }
    
    impl Drawable for Circle {
        fn draw(&self) {
            println!("Drawing a circle with radius {}", self.radius);
        }
    }
    
    // 实现Drawable trait的Rectangle结构体
    struct Rectangle {
        width: f64,
        height: f64,
    }
    
    impl Drawable for Rectangle {
        fn draw(&self) {
            println!("Drawing a rectangle with width {} and height {}", self.width, self.height);
        }
    }
    
    // 使用dyn关键字创建一个函数，接受一个实现了Drawable trait的对象
    fn draw_shape<T: Drawable>(shape: &T) {
        shape.draw();
    }
    let circle = Circle { radius: 5.0 };
    let rectangle = Rectangle { width: 4.0, height: 6.0 };

    // 调用draw_shape函数，传入Circle和Rectangle对象
    draw_shape(&circle);
    draw_shape(&rectangle);
}

#[allow(unused_variables, dead_code)]
#[test]
fn test_dynamic_vector() {
    trait Drawable {
        fn draw(&self);
    }
    
    // 实现Drawable trait的Circle结构体
    struct Circle {
        radius: f64,
    }
    
    impl Drawable for Circle {
        fn draw(&self) {
            println!("Drawing a circle with radius {}", self.radius);
        }
    }
    
    // 实现Drawable trait的Rectangle结构体
    struct Rectangle {
        width: f64,
        height: f64,
    }
    
    impl Drawable for Rectangle {
        fn draw(&self) {
            println!("Drawing a rectangle with width {} and height {}", self.width, self.height);
        }
    }
    
    let mut shape_vector: Vec<Box<dyn Drawable>> = Vec::new();
    shape_vector.push(Box::new(Circle { radius: 5.0 }));
    shape_vector.push(Box::new(Rectangle { width: 4.0, height: 6.0 }));
}
