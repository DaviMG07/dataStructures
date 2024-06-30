import asyncio
import os

async def one_cycle(speed = 1):
    speed = speed if speed else 1
    speed /= 40
    await asyncio.sleep(speed)
    return 1

async def counter(start, end = 0, speed = None):
    while (start > end):
        start -= await one_cycle(speed)
        yield start
    while (start < end):
        start += await one_cycle(speed)
        yield start - 1

class MEF:
    def __init__(self):
        self.matrix = [0 for num in range(5)]

    async def gen(self):
        async for now in counter(0, 10, 10):
            for i, x in enumerate(self.matrix):
                self.matrix[i] = not self.matrix[i]
                await one_cycle(10)

    async def print(self):
        async for now in counter(200):
            os.system("clear")
            for i, x in enumerate(self.matrix):
                if (True == self.matrix[i]):
                    print("• " * 5)
                else:
                    print("· " * 5)
            await one_cycle()
async def main():
    mef = MEF()
    await asyncio.gather(mef.gen(), mef.print())

asyncio.run(main())