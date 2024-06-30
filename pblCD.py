import platform
import os
import asyncio

def clear():
    if (platform.system().lower() == "windows"):
        os.system("cls")
    else:
        os.system("clear")

async def one_cycle(speed = 1):
    speed = speed if speed else 1
    speed /= 20
    await asyncio.sleep(speed)
    return 1

async def counter(start, end = 0, speed = None):
    while (start < end):
        yield start
        start += await one_cycle(speed)
    while (start > end):
        start -= await one_cycle(speed)
        yield start

class StateMachine:
    def __init__(self):
        self.rows = [0 for num in range(7)]
        self.row = 0
        self.time = 0
        self.total = 0
        self.especifico = False
        self.state = "E"
        self.rega = "N"
        self.level = "C"
        self.speed = 1
        self.run = True
    
    async def start(self):
        while (self.state == "E"):
            self.speed = 10 / 7
            async for now in counter(0, 8, self.speed):
                self.row = now

                match now:
                    case 0:
                        pass
                    case 1:
                        self.rows[0] = 2
                    case 2:
                        self.rows[1] = 2
                    case 3:
                        self.rows[2] = 2
                    case 4:
                        self.rows[3] = 2
                    case 5:
                        self.rows[4] = 2
                    case 6:
                        self.rows[5] = 2
                    case 7:
                        self.rows[6] = 2
                        self.state = self.rega
        while (self.state == "A"):
            self.speed = 15 / 7
            async for now in counter(7, 0, self.speed):
                self.row = now

                match now:
                    case 6:
                        self.rows[6] = 0
                    case 5:
                        self.rows[5] = 0
                    case 4:
                        self.rows[4] = 0
                    case 3:
                        self.rows[3] = 0
                    case 2:
                        self.rows[2] = 0
                    case 1:
                        self.rows[1] = 0
                        self.state = "L"
        while (self.state == "G"):
            self.speed = 30 / 7
            async for now in counter(7, 0, self.speed):
                self.row = now

                match now:
                    case 6:
                        self.rows[6] = 0
                    case 5:
                        self.rows[5] = 0
                    case 4:
                        self.rows[4] = 0
                    case 3:
                        self.rows[3] = 0
                    case 2:
                        self.rows[2] = 0
                    case 1:
                        self.rows[1] = 0
                        self.state = "L"
        while (self.state == "L"):
            async for now in counter(5):
                self.rows[0] = 1

                match now:
                    case 0:
                        self.rows[0] = 0
                        self.state = ""
        await one_cycle()
        self.run = False
        print("cabou")

    async def display(self):
        while True:
            clear()
            for i in range(len(self.rows) - 1, -1, -1):
                if (self.rows[i] == 2):
                    print("• " * 5)
                elif (self.rows[i] == 1):
                    print("_ " * 5)
                else:
                    print("· " * 5)
            print(f"state: {self.state}")
            print(f"level: {self.level}")
            print(f"speed: {self.speed}")
            print(f"row: {self.row}")
            print(f"current time: {self.time}")
            print(f"total time: {self.total}")
            print(self.rows)
            print("\n\nse não terminar é só spammar ctrl C")
            await one_cycle(0.5)

            if (not self.run):
                return
        print("cabou")
    
    async def timer(self):
        while True:
            if (self.state == "E"):
                async for now in counter(10):
                    self.time = now
                    self.total += 1
            elif (self.state == "A"):
                async for now in counter(15):
                    self.time = now
                    self.total += 1
            elif (self.state == "G"):
                async for now in counter(30):
                    self.time = now
                    self.total += 1
            elif (self.state == "L"):
                async for now in counter(5):
                    self.time = now
                    self.total += 1
            if (not self.run):
                return
        print("cabou")

async def main():
    mef = StateMachine()
    clear()
    while True:
        try:
            clear()
            print("1 - aspersao\n2 - gotejamento")
            x = int(input())
            if x in [1, 2]:
                break
        except:
            pass
    if (x == 1):
        mef.rega = "A"
    else:
        mef.rega = "G"

    await asyncio.gather(mef.start(), mef.display(), mef.timer())

asyncio.run(main())