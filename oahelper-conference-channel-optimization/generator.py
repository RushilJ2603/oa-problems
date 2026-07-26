#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size <= 3:
        n = random.randint(1, 4)
        m = random.randint(0, min(8, n * n))
    elif size <= 12:
        n = random.randint(3, 12)
        m = random.randint(n - 1, min(40, n * 3))
    elif size <= 60:
        n = random.randint(20, 80)
        m = random.randint(n, min(300, n * 4))
    elif size <= 150:
        n = random.randint(200, 800)
        m = random.randint(n, min(3000, n * 3))
    else:
        # MAX-SCALE
        n = 100000
        m = 200000

    # Build a spanning tree so the graph is often connected, then add extra edges.
    edges = []
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        w = random.randint(-10, 20) if size < 400 else random.randint(-10**9, 10**9)
        edges.append((p, i, w))

    extra = m - (n - 1)
    if extra < 0:
        edges = edges[:max(0, m)]
    else:
        for _ in range(extra):
            u = random.randint(1, n)
            v = random.randint(1, n)
            if size >= 400:
                w = random.randint(-2 * 10**9, 2 * 10**9)
            else:
                w = random.randint(-50, 100)
            edges.append((u, v, w))

    # Occasionally emit a deliberately disconnected instance
    if size <= 60 and seed % 7 == 0 and n >= 4:
        edges = [(1, 2, 5), (3, 4, -1)]
        m = 2

    # Occasionally all-negative / all-zero / multi-edges
    mode = seed % 5
    if size <= 40 and mode == 1 and n >= 2:
        edges = [(i, i + 1, -random.randint(1, 10)) for i in range(1, n)]
        m = len(edges)
    elif size <= 40 and mode == 2 and n >= 2:
        edges = [(1, 2, random.randint(0, 5)) for _ in range(min(m, 10))]
        m = len(edges)

    m = len(edges)
    print(n, m)
    for u, v, w in edges:
        print(u, v, w)

if __name__ == "__main__":
    main()
