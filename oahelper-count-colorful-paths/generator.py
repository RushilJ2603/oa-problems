#!/usr/bin/env python3
import random
import sys


def main() -> None:
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size arg toward constraint bounds; large size => max-scale 10x10
    n = max(1, min(10, size if size <= 10 else 10))
    m = max(1, min(10, (size * 3 + seed) % 10 + 1 if size < 40 else 10))
    if size >= 150:
        n, m = 10, 10
    elif size >= 40:
        n = min(10, max(n, 6 + seed % 5))
        m = min(10, max(m, 6 + (seed // 3) % 5))
    else:
        n = max(1, min(10, 1 + (size + seed) % max(1, min(size, 10))))
        m = max(1, min(10, 1 + (size * 2 + seed) % max(1, min(size + 1, 10))))

    mode = seed % 5
    grid = [[0] * m for _ in range(n)]
    if mode == 0:
        # all distinct colors (when n*m <= 101)
        colors = list(range(101))
        random.shuffle(colors)
        k = 0
        for i in range(n):
            for j in range(m):
                grid[i][j] = colors[k % 101]
                k += 1
    elif mode == 1:
        # all same color
        c = random.randint(0, 100)
        for i in range(n):
            for j in range(m):
                grid[i][j] = c
    elif mode == 2:
        # few colors, high collision
        palette = [random.randint(0, 100) for _ in range(1 + seed % 4)]
        for i in range(n):
            for j in range(m):
                grid[i][j] = random.choice(palette)
    elif mode == 3:
        # mostly unique along a corridor, duplicates elsewhere
        for i in range(n):
            for j in range(m):
                grid[i][j] = (i * m + j) % 101
        if n > 1 and m > 1:
            grid[n - 1][0] = grid[0][0]
            grid[0][m - 1] = grid[n - 1][m - 1]
    else:
        for i in range(n):
            for j in range(m):
                grid[i][j] = random.randint(0, 100)

    print(n, m)
    for row in grid:
        print(" ".join(map(str, row)))


if __name__ == "__main__":
    main()
