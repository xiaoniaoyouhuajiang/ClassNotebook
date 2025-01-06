use std::future::Future;
use std::task::Waker;
use std::pin::Pin;

// return future
async fn async_hello_world() {
    println!("Hello, world!");
}

// 
async fn wait_for_hello_world() {
    async_hello_world().await;
}

pub struct Thought {
    /// This is the actual thing the brain should process as part of the Thought
    pub thinkable: Pin<Box<dyn Future<Output = ()> + 'static>>,
}

struct Brain {
    /// the list of `Thoughts`s that require processing
    thoughts: Vec<Option<Thought>>,
}

impl Brain {
    /// Add a new `Future` to the [Brain], so it can be processed
    fn think_on(&mut self, thinkable: impl Future<Output = ()> + 'static) {
        // ensure the given Future is getting a fixed position on the HEAP
        let thinkable = Box::pin(thinkable);
        // create the Thought
        let thought = Thought {
            thinkable,
        };
        // push the Thought to the list of thoughts to think on
        self.thoughts.push(Some(thought));
    }
}
