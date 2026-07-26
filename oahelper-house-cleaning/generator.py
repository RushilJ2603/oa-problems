#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size -> n; large size hits constraint max N=400
    if size <= 3:
        n = random.randint(1, 3)
    elif size <= 10:
        n = random.randint(3, 10)
    elif size <= 40:
        n = random.randint(10, 40)
    elif size <= 150:
        n = random.randint(50, 150)
    else:
        n = 400

    # Variety of layouts by seed
    mode = seed % 7
    houses = []
    if mode == 0:
        # diagonal — matching = n
        for i in range(n):
            houses.append((i, i))
    elif mode == 1:
        # single row
        x = random.randint(0, 10**9)
        for i in range(n):
            houses.append((x, random.randint(0, 10**9)))
    elif mode == 2:
        # single column
        y = random.randint(0, 10**9)
        for i in range(n):
            houses.append((random.randint(0, 10**9), y))
    elif mode == 3:
        # few rows, many cols
        rows = max(1, n // 5)
        for i in range(n):
            houses.append((random.randint(0, rows - 1), random.randint(0, 10**9)))
    elif mode == 4:
        # grid-ish
        w = max(1, int(n ** 0.5))
        for i in range(n):
            houses.append((i % w, i // w))
    elif mode == 5:
        # reverse sorted coords
        for i in range(n):
            houses.append((10**9 - i, 10**9 - 2 * i))
    else:
        # random with occasional duplicates
        for i in range(n):
            if i > 0 and random.random() < 0.1:
                houses.append(houses[random.randrange(i)])
            else:
                houses.append((random.randint(0, 10**6), random.randint(0, 10**6)))

    print(n)
    for x, y in houses:
        print(x, y)

if __name__ == "__main__":
    main()
