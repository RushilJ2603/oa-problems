#!/usr/bin/env python3
import sys
import random

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size <= 3:
        N = random.randint(2, 6)
    elif size <= 10:
        N = random.randint(5, 20)
    elif size <= 40:
        N = random.randint(20, 80)
    elif size <= 150:
        N = random.randint(100, 400)
    else:
        # max-scale
        N = 100000

    max_edges = min(100000, N * (N - 1) // 2)
    if size >= 400:
        M = min(100000, max_edges)
    elif size >= 150:
        M = min(max_edges, random.randint(N - 1, min(max_edges, 2 * N)))
    else:
        M = random.randint(1, min(max_edges, max(1, N * 2)))

    edges = set()
    # Ensure connectivity bias with a path / cycle backbone for variety
    kind = random.randint(0, 4)
    if kind == 0 and N >= 2:
        # path
        for i in range(N - 1):
            edges.add((i, i + 1))
    elif kind == 1 and N >= 3:
        # cycle
        for i in range(N):
            edges.add((i, (i + 1) % N))
    elif kind == 2:
        # star
        c = random.randint(0, N - 1)
        for i in range(N):
            if i != c:
                a, b = min(c, i), max(c, i)
                edges.add((a, b))
    elif kind == 3 and N >= 4:
        # triangle + dangling chains
        edges.add((0, 1))
        edges.add((1, 2))
        edges.add((2, 0))
        for i in range(3, N):
            edges.add((i - 1, i))

    attempts = 0
    while len(edges) < M and attempts < M * 20 + 100:
        u = random.randint(0, N - 1)
        v = random.randint(0, N - 1)
        if u == v:
            attempts += 1
            continue
        a, b = min(u, v), max(u, v)
        edges.add((a, b))
        attempts += 1

    edges = list(edges)[:M]
    M = len(edges)
    random.shuffle(edges)
    A = [e[0] for e in edges]
    B = [e[1] for e in edges]
    # randomly swap endpoints
    for i in range(M):
        if random.random() < 0.5:
            A[i], B[i] = B[i], A[i]

    print(N, M)
    print(" ".join(map(str, A)))
    print(" ".join(map(str, B)))

if __name__ == "__main__":
    main()
