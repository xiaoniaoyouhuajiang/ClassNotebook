from multiprocessing.dummy import Pool as ThreadPool
from multiprocessing import Process
import multiprocessing
import requests
import time
import asyncio
import aiohttp
import threading

OPTION = {"COROUTINE": 0, "SINGLE_THREAD": 0,
          "MULTI_THREADS": 0, "MULTI_THREADS_COROUTINE": 0,  "MULTI_PROCESSES": 0,"MUTL_PROCESSES_COROUTINE": 0,}

urls = []

def getsource(url):
    _ = requests.get(url)
    return

async def agetsource(url):
    async with aiohttp.request("GET", url) as response:
        await response.text()
    return

def singleThread():
    for url in urls:
        getsource(url)

def multithreads():
    pool = ThreadPool(4)
    _ = pool.map(getsource, urls)
    pool.close()
    pool.join()

def multiprocesses():
    pool = multiprocessing.Pool(processes=4)
    for url in urls:
        pool.apply_async(getsource, (url,))
    pool.close()
    pool.join()

async def amain(index, pool_size):
    loop = asyncio.get_event_loop()
    start_index = index * int(len(urls) / pool_size)
    end_index = min(len(urls), start_index + int(len(urls) / pool_size))

    for url in urls[start_index:end_index]:
        _ = loop.create_task(agetsource(url))
    while (len(asyncio.all_tasks(loop)) > 1):
        await asyncio.sleep(2)

def main(index, pool_size):
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    # loop = asyncio.get_event_loop()
    loop.run_until_complete(amain(index, pool_size))

def mutithreads_coroutine():
    threads = []
    for index in range(4):
        threads.append(threading.Thread(target=main, args=(index, 4,)))
    for index in range(4):
        threads[index].start()
    for index in range(4):
        threads[index].join()

def multiprocesses_coroutine():
    processes = []
    for index in range(4):
        processes.append(Process(target=main, args=(index, 4,)))

    for index in range(4):
        processes[index].start()

    for index in range(4):
        processes[index].join()

if __name__ == "__main__":

    for option in OPTION:
        OPTION[option] = 1
        factor = 1
        start_time = time.time()

        # 准备测试数据
        urls.clear()
        for i in range(1, 80):
            newpage = 'http://tieba.baidu.com/p/3522395718?pn=' + str(i)
            urls.append(newpage)

        
        if OPTION["MUTL_PROCESSES_COROUTINE"]:
            multiprocesses_coroutine()
        if OPTION["SINGLE_THREAD"]:
            singleThread()
        if OPTION["MULTI_THREADS"]:
            multithreads()
        if OPTION["MULTI_THREADS_COROUTINE"]:
            mutithreads_coroutine()
        if OPTION["COROUTINE"]:
            main(0, 1)
        if OPTION["MULTI_PROCESSES"]:
            multiprocesses()
        end_time = time.time()
        print(f"Time consuming for option <{list(filter(lambda x : OPTION[x], OPTION))[0]}> = {factor * (end_time - start_time)}")
        OPTION[option] = 0