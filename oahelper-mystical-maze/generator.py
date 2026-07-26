#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    # Hit M*N <= 1e5 at large size
    if size >= 400:
        # max-scale: roughly square ~316x316 or skinny
        mode = seed % 3
        if mode == 0:
            m, n = 1, 100000
        elif mode == 1:
            m, n = 100000, 1
        else:
            m = n = 316
            while m * n > 100000:
                n -= 1
    elif size >= 150:
        m = random.randint(1, min(size, 200))
        n = max(1, min(100000 // m, size))
    else:
        m = random.randint(1, max(1, min(20, size)))
        n = random.randint(1, max(1, min(20, size)))
    cells = m * n
    # cost patterns
    pattern = seed % 6
    grid = [[0] * n for _ in range(m)]
    for i in range(m):
        for j in range(n):
            if pattern == 0:
                grid[i][j] = random.randint(0, 10)
            elif pattern == 1:
                grid[i][j] = random.randint(0, 10**9)
            elif pattern == 2:
                grid[i][j] = 0
            elif pattern == 3:
                grid[i][j] = 10**9 if (i + j) % 3 == 0 else random.randint(0, 5)
            elif pattern == 4:
                # high costs off the diagonal-ish path
                grid[i][j] = 1 if abs(i * n - j * m) < max(m, n) else 100
            else:
                grid[i][j] = random.randint(1, 100)
    # compute a rough lower bound via DP to set E sometimes tight
    dp = [0] * n
    for i in range(m):
        for j in range(n):
            c = grid[i][j]
            if i == 0 and j == 0:
                dp[j] = c
            elif i == 0:
                dp[j] = dp[j - 1] + c
            elif j == 0:
                dp[j] = dp[j] + c
            else:
                dp[j] = min(dp[j], dp[j - 1]) + c
    mincost = dp[n - 1]
    e_mode = seed % 4
    if e_mode == 0:
        e = mincost  # exact boundary
    elif e_mode == 1:
        e = max(0, mincost - 1)  # just fail
    elif e_mode == 2:
        e = 10**9
    else:
        e = random.randint(0, 10**9)
    print(m)
    print(n)
    print(e)
    for row in grid:
        print(" ".join(map(str, row)))

if __name__ == "__main__":
    main()
