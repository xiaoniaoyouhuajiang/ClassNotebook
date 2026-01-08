async def async_hello_world():
    print("Hello, World!")

async def wait_for_hello_world():
    await async_hello_world()

