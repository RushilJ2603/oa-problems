#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 300:
        m = n = 100
    elif size >= 150:
        # medium grids — still small enough that length grows with size
        m = 20 + (seed % 5)
        n = 20 + ((seed // 3) % 5)
    elif size >= 60:
        # brute-safe: path length ~14
        m = 4 + (seed % 4)
        n = 4 + ((seed // 2) % 4)
    else:
        m = max(1, min(6, 1 + size % 5))
        n = max(1, min(6, 1 + (size // 2) % 5))
        if size <= 3:
            m = 1
            n = max(1, size)

    # Value patterns that stress the DP
    mode = seed % 6
    dungeon = [[0] * n for _ in range(m)]
    for i in range(m):
        for j in range(n):
            if mode == 0:
                dungeon[i][j] = random.randint(-1000, 1000)
            elif mode == 1:
                dungeon[i][j] = random.randint(-50, -1)  # all damage
            elif mode == 2:
                dungeon[i][j] = random.randint(0, 50)  # non-negative
            elif mode == 3:
                dungeon[i][j] = -1000 if (i + j) % 2 == 0 else 1000
            elif mode == 4:
                dungeon[i][j] = random.choice([-5, -1, 0, 1, 10])
            else:
                dungeon[i][j] = random.randint(-100, 100)

    print(m, n)
    for row in dungeon:
        print(" ".join(map(str, row)))


if __name__ == "__main__":
    main()
