#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    MAX = 400
    if size <= 3:
        m = random.randint(2, 2)
        n = random.randint(2, 3)
    elif size <= 10:
        m = random.randint(2, min(4, size))
        n = random.randint(2, min(4, size))
    elif size <= 40:
        side = min(15, size)
        m = random.randint(2, side)
        n = random.randint(2, side)
    elif size <= 150:
        side = min(40, size)
        m = random.randint(5, side)
        n = random.randint(5, side)
    elif size <= 400:
        side = min(100, size)
        m = random.randint(20, side)
        n = random.randint(20, side)
    else:
        # MAX-SCALE
        m = n = MAX

    mode = seed % 5
    print(m, n)
    for i in range(m):
        row = []
        for j in range(n):
            if mode == 0:
                row.append(random.randint(0, 10))
            elif mode == 1:
                # large values — overflow trap for 32-bit
                row.append(random.randint(10**8, 10**9))
            elif mode == 2:
                row.append(0 if random.random() < 0.5 else random.randint(1, 100))
            elif mode == 3:
                # increasing along rows
                row.append(i * n + j)
            else:
                row.append(random.randint(0, 10**9))
        print(" ".join(map(str, row)))

if __name__ == "__main__":
    main()
