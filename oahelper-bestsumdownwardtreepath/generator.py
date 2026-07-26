#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    rng = random.Random(seed)

    if size <= 3:
        n = rng.randint(1, 6)
    elif size <= 10:
        n = rng.randint(5, 15)
    elif size <= 40:
        n = rng.randint(20, 50)
    elif size <= 150:
        n = rng.randint(40, 80)  # keep brute O(n^2) feasible
    else:
        n = 100000

    parent = [-1] * n
    for i in range(1, n):
        parent[i] = rng.randint(0, i - 1)

    kind = rng.randint(0, 4)
    if kind == 0:
        values = [rng.randint(-1000, 1000) for _ in range(n)]
    elif kind == 1:
        values = [rng.randint(1, 1000) for _ in range(n)]
    elif kind == 2:
        values = [rng.randint(-1000, -1) for _ in range(n)]
    elif kind == 3:
        values = [0] * n
    else:
        values = [rng.randint(-100, 100) for _ in range(n)]
        values[rng.randint(0, n - 1)] = 1000

    print(n)
    for p in parent:
        print(p)
    for v in values:
        print(v)


if __name__ == "__main__":
    main()
