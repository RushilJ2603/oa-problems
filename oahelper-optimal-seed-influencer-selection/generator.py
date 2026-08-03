#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 1000:
        n = 2000
        m = min(20000, n * 5)
        s = 200
        d = min(n, 10)
    else:
        n = max(1, min(size, 2000))
        m = min(n * (n - 1) // 2 if n > 1 else 0, max(0, size * 2))
        s = max(0, min(200, max(1, size // 2)))
        d = random.randint(0, min(n, max(0, size // 10)))

    edges = set()
    # Build a connected backbone then add random edges
    for i in range(2, n + 1):
        if len(edges) >= m:
            break
        edges.add((i - 1, i))
    while len(edges) < m and n > 1:
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v:
            continue
        a, b = (u, v) if u < v else (v, u)
        edges.add((a, b))

    # Potential seeds: mix of valid ids, occasional invalid, occasional duplicate
    seeds = []
    for i in range(s):
        if random.random() < 0.05:
            sid = n + 5
        else:
            sid = random.randint(1, n)
        cost = random.randint(1, 1000)
        seeds.append((sid, cost))
    if s >= 2 and random.random() < 0.3:
        # force a duplicate id with different cost
        seeds[1] = (seeds[0][0], seeds[0][1] + 1)

    values = [random.randint(0, 1000) for _ in range(n)]
    if random.random() < 0.1:
        values = [0] * n
    budget = random.randint(0, max(1, sum(c for _, c in seeds)))
    if random.random() < 0.2:
        budget = 10**9

    print(n)
    print(len(edges))
    for u, v in edges:
        print(u, v)
    print(len(seeds))
    for sid, cost in seeds:
        print(sid, cost)
    print(" ".join(map(str, values)))
    print(budget)
    print(d)

if __name__ == "__main__":
    main()
