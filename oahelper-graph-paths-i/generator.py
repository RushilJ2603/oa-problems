#!/usr/bin/env python3
"""Deterministic generator: python3 generator.py <seed> <size>"""
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 100:
        # MAX-SCALE: hit constraint bounds
        n = 100
        k = 10**9
        edges = []
        for i in range(1, n + 1):
            for j in range(1, n + 1):
                if i != j:
                    edges.append((i, j))
        # Drop a few edges deterministically from seed so seeds still differ
        drop = seed % 17
        if drop:
            edges = edges[:-drop] if drop < len(edges) else edges
        m = len(edges)
        print(n, m, k)
        for a, b in edges:
            print(a, b)
        return

    if size <= 5:
        n = random.randint(2, 4)
        k = random.randint(1, 10)
        m_target = random.randint(1, min(n * n, n + 3))
    elif size <= 20:
        n = random.randint(3, 10)
        k = random.randint(1, 50)
        m_target = random.randint(1, min(n * n, 4 * n))
    else:
        n = random.randint(10, min(40, size // 2 + 5))
        k = random.randint(1, 10**7)
        m_target = random.randint(n, min(n * n, 6 * n))

    kind = random.randint(0, 4)
    if kind == 0:
        edges = [(i, i + 1) for i in range(1, n)]
    elif kind == 1:
        edges = [(i, i % n + 1) for i in range(1, n + 1)]
    elif kind == 2:
        edges = []
        for i in range(1, n + 1):
            for j in range(1, n + 1):
                if i != j and random.random() < 0.4:
                    edges.append((i, j))
        if not edges:
            edges = [(1, n)]
    else:
        edges = []
        for _ in range(m_target):
            edges.append((random.randint(1, n), random.randint(1, n)))

    m = len(edges)
    print(n, m, k)
    for a, b in edges:
        print(a, b)


if __name__ == "__main__":
    main()
