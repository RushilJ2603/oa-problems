#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2]) if len(sys.argv) > 2 else 10
    random.seed(seed)

    # Map size -> dimensions; large size hits constraint max m=n=200.
    if size <= 5:
        m = random.randint(1, 3)
        n = random.randint(1, 3)
    elif size <= 15:
        m = random.randint(2, 5)
        n = random.randint(2, 5)
    elif size <= 40:
        m = random.randint(4, 12)
        n = random.randint(4, 12)
    elif size <= 100:
        m = random.randint(8, 20)
        n = random.randint(8, 20)
    elif size <= 250:
        # Still below max-scale; keep modest so recursive brute stays safe
        m = random.randint(15, 35)
        n = random.randint(15, 35)
    else:
        m, n = 200, 200

    mode = random.randint(0, 7)
    grid = [[0] * n for _ in range(m)]

    if mode == 0:
        # all equal
        v = random.randint(0, 10**9)
        for i in range(m):
            for j in range(n):
                grid[i][j] = v
    elif mode == 1:
        # strictly increasing snake (row-major zigzag)
        cur = 0
        for i in range(m):
            cols = range(n) if i % 2 == 0 else range(n - 1, -1, -1)
            for j in cols:
                grid[i][j] = cur
                cur += 1
    elif mode == 2:
        # strictly decreasing snake
        cur = m * n
        for i in range(m):
            cols = range(n) if i % 2 == 0 else range(n - 1, -1, -1)
            for j in cols:
                grid[i][j] = cur
                cur -= 1
    elif mode == 3:
        # random with many duplicates
        pool = [random.randint(0, 50) for _ in range(max(1, (m * n) // 4))]
        for i in range(m):
            for j in range(n):
                grid[i][j] = random.choice(pool)
    elif mode == 4:
        # sparse extremes near 2^31-1
        for i in range(m):
            for j in range(n):
                if random.random() < 0.3:
                    grid[i][j] = 2147483647
                else:
                    grid[i][j] = random.randint(0, 100)
    elif mode == 5:
        # sorted rows ascending
        cur = 0
        for i in range(m):
            for j in range(n):
                grid[i][j] = cur
                cur += random.randint(0, 3)
    else:
        # fully random in full range
        for i in range(m):
            for j in range(n):
                grid[i][j] = random.randint(0, 2147483647)

    print(m)
    print(n)
    for row in grid:
        print(" ".join(map(str, row)))


if __name__ == "__main__":
    main()
