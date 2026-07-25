#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Scale n with size; only hit full constraint at large size args
    if size >= 1500:
        n = 100000  # MAX-SCALE
    elif size >= 400:
        n = min(5000, size * 8)
    elif size >= 150:
        n = min(800, size * 3)
    elif size >= 40:
        n = min(120, size + 10)
    elif size >= 10:
        n = random.randint(max(2, size // 2), size + 5)
    else:
        n = random.randint(1, max(1, size + 2))

    order = list(range(n))
    random.shuffle(order)
    rank = [0] * n
    for i, v in enumerate(order):
        rank[v] = i

    if n >= 100000:
        m = min(200000, n + n // 2)
    elif n > 1:
        m = random.randint(0, min(n * 3, n * (n - 1) // 2, 5000))
    else:
        m = 0

    edges = []
    edge_set = set()
    attempts = 0
    while len(edges) < m and attempts < max(m * 30, 100):
        attempts += 1
        u = random.randrange(n)
        v = random.randrange(n)
        if rank[u] < rank[v]:
            if (u, v) not in edge_set or random.random() < 0.03:
                edges.append((u, v))
                edge_set.add((u, v))

    mode = random.randrange(6)
    if mode == 0 and edge_set:
        a, b = random.choice(list(edge_set))
    elif mode == 1:
        a = b = random.randrange(n)
    elif mode == 2 and n > 1:
        i = random.randrange(n - 1)
        a, b = order[min(i + 1, n - 1)], order[i]
    elif mode == 3 and n > 1:
        i = random.randrange(n - 1)
        a, b = order[i], order[i + 1]
    else:
        a, b = random.randrange(n), random.randrange(n)

    out = [f"{n} {len(edges)}"]
    out.extend(f"{u} {v}" for u, v in edges)
    out.append(f"{a} {b}")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
