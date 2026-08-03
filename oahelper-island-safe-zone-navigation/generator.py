#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size <= 3:
        M = N = random.randint(1, 3)
    elif size <= 10:
        M = random.randint(2, 5)
        N = random.randint(2, 5)
    elif size <= 40:
        M = random.randint(5, 15)
        N = random.randint(5, 15)
    elif size <= 150:
        M = random.randint(30, 80)
        N = random.randint(30, 80)
    else:
        M = N = 500

    grid = [[0] * N for _ in range(M)]
    # place a few islands
    num_islands = max(1, min(M * N // 4, 2 + seed % 7 + (M * N) // 50))
    islands = []
    for _ in range(num_islands):
        r, c = random.randint(0, M - 1), random.randint(0, N - 1)
        val = random.randint(1, 1000 if M < 100 else 10**9)
        grid[r][c] = val
        islands.append((r, c))

    # ensure at least one island for start
    if not islands:
        grid[0][0] = random.randint(1, 10)
        islands.append((0, 0))

    sr, sc = random.choice(islands)
    Z = random.randint(1, 10**18 if M >= 100 else 10000)

    # safe cells: mix of islands (and rarely water — ignored by solution for targets needing island)
    S = random.randint(1, min(len(islands), max(1, len(islands))))
    safe = random.sample(islands, S)
    # sometimes add start as safe
    if seed % 4 == 0 and (sr, sc) not in safe:
        safe.append((sr, sc))
        S = len(safe)

    # mode: block channel / open water
    if seed % 3 == 0:
        # fill most with water (already 0)
        pass
    elif seed % 3 == 1:
        # scatter blocking islands
        for _ in range(M * N // 10):
            r, c = random.randint(0, M - 1), random.randint(0, N - 1)
            if (r, c) != (sr, sc):
                grid[r][c] = random.randint(1, 50)

    print(M, N)
    for row in grid:
        print(*row)
    print(sr, sc)
    print(Z)
    print(S)
    for r, c in safe:
        print(r, c)


if __name__ == "__main__":
    main()
