# 为了能让人确切地看到什么是协程，选择：
import asyncio
import timeit

# 一个倒计时函数，同时能够log出东西来保证异步的过程被观察到
async def countdown(identifier, n):
    while n > 0:
        print('left:', n, '({})'.format(identifier))
        await asyncio.sleep(1)
        n -= 1
        
async def main():
    await asyncio.wait([
        countdown("A", 2),
        countdown("B", 3)
    ])

# loop = asyncio.get_event_loop()
# loop.run_until_complete(main())

async def wait_until(predicate):
    import time
    seconds = 0
    while not predicate():
        print('Waiting...')
        await asyncio.sleep(1)
        seconds += 1
    print('Done!')
    return seconds

# fetch_url部分不能直接使用urllib，因为这会导致当前线程一直阻塞，因此我们只能使用asyncio.
# open_connection,这是一个纯TCP层的实现，因此需要我们自己实现http
import urllib
async def fetch_url(url):
    url = urllib.parse.urlsplit(url)
    reader, writer = await asyncio.open_connection(url.hostname, 80)
    req = ('GET {path} HTTP/1.0\r\n'
          'Host: {hostname}\r\n'
          '\r\n').format(path=url.path or '/', hostname = url.hostname)
    writer.write(req.encode('latin-1'))
    while True:
        lint = await reader.readline()
        if not line.strip():
            break
    return await reader.read()


loop = asyncio.get_event_loop()
t1 = asyncio.ensure_future(fetch_url('http://httpbin.org/delay/3'))
t2 = asyncio.ensure_future(wait_until(t1.done))
loop.run_until_complete(t2)

