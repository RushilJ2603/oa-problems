#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size arg to grid dimensions; large size -> max-scale 100x100
    if size <= 5:
        n = random.randint(1, 3)
        m = random.randint(1, 3)
    elif size <= 20:
        n = random.randint(3, 8)
        m = random.randint(3, 8)
    elif size <= 80:
        n = random.randint(10, 30)
        m = random.randint(10, 30)
    elif size <= 200:
        n = random.randint(40, 70)
        m = random.randint(40, 70)
    else:
        n, m = 100, 100

    density = random.choice([0.05, 0.1, 0.2, 0.35, 0.5])
    grid = [[1 if random.random() < density else 0 for _ in range(m)] for _ in range(n)]

    # Occasionally force patterns
    mode = random.randint(0, 5)
    if mode == 0:
        grid = [[0] * m for _ in range(n)]
    elif mode == 1:
        grid = [[1] * m for _ in range(n)]
    elif mode == 2 and n >= 2 and m >= 2:
        # ring of infection around empty center
        for i in range(n):
            for j in range(m):
                grid[i][j] = 1 if i == 0 or j == 0 or i == n - 1 or j == m - 1 else 0
    elif mode == 3:
        # sparse single cells
        grid = [[0] * m for _ in range(n)]
        for _ in range(max(1, (n * m) // 20)):
            grid[random.randrange(n)][random.randrange(m)] = 1

    print(n, m)
    for row in grid:
        print(" ".join(map(str, row)))


if __name__ == "__main__":
    main()
