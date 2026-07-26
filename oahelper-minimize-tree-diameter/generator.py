#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size -> n; hit max constraint at large size
    if size <= 3:
        n = random.randint(1, 4)
    elif size <= 10:
        n = random.randint(5, 12)
    elif size <= 40:
        n = random.randint(13, 40)
    elif size <= 150:
        n = random.randint(50, min(150, size + 20))
    else:
        n = 2000  # MAX-SCALE

    k = random.randint(0, n)

    # Build a random tree via random parents, then randomly relabel
    edges = []
    if n >= 2:
        for i in range(2, n + 1):
            p = random.randint(1, i - 1)
            edges.append((p, i))
        # Occasionally force path / star shapes for variety
        shape = random.randint(0, 5)
        if shape == 0 and n >= 2:
            edges = [(i, i + 1) for i in range(1, n)]
        elif shape == 1 and n >= 2:
            edges = [(1, i) for i in range(2, n + 1)]
        perm = list(range(1, n + 1))
        random.shuffle(perm)
        mp = {i: perm[i - 1] for i in range(1, n + 1)}
        edges = [(mp[u], mp[v]) for u, v in edges]
        random.shuffle(edges)

    print(n, k)
    for u, v in edges:
        print(u, v)


if __name__ == "__main__":
    main()
