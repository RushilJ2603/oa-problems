#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Brute enumerates 2^n; keep n tiny for sizes used in brute cross-checks.
    # At the largest size, hit the constraint bound X = 10000.
    if size <= 12:
        n = random.randint(1, max(1, min(8, size + 1)))
    elif size <= 60:
        n = random.randint(4, 12)
    elif size <= 150:
        n = random.randint(8, 14)
    elif size <= 400:
        n = random.randint(10, 16)
    elif size < 2000:
        n = random.randint(80, 200)
    else:
        n = 10000

    boosts = [random.randint(-1000 if n > 500 else -10**6,
                             1000 if n > 500 else 10**6) for _ in range(n)]
    if n >= 10000:
        # Max-scale: sparse DAG, bounded boosts so flow stays fast under mutation load.
        boosts = [random.randint(-100, 100) for _ in range(n)]

    # Build a random DAG: edges only from higher index to lower index (topo order).
    max_edges = min(5000, max(0, n - 1))
    if n <= 18:
        max_edges = min(n * 2, 40)
    edges_left = max_edges
    prereqs = [[] for _ in range(n)]
    for i in range(1, n):
        if edges_left <= 0:
            break
        if random.random() < 0.5:
            p = random.randint(0, i - 1)
            prereqs[i] = [p]
            edges_left -= 1

    # Shared expensive prerequisite pattern (small n only).
    if 4 <= n <= 50 and random.random() < 0.4:
        hub = 0
        boosts[hub] = -abs(boosts[hub]) - 1
        for i in range(1, min(n, 1 + random.randint(2, 4))):
            if hub not in prereqs[i]:
                prereqs[i].append(hub)
            boosts[i] = abs(boosts[i]) + 1

    print(n)
    for i in range(n):
        row = [boosts[i], len(prereqs[i])] + [p + 1 for p in prereqs[i]]
        print(*row)


if __name__ == "__main__":
    main()
