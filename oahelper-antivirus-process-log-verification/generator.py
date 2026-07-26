#!/usr/bin/env python3
import random
import sys


def build_tree(n, rng):
    """Random tree rooted at 1 via random Prüfer-like parents."""
    edges = []
    for v in range(2, n + 1):
        u = rng.randint(1, v - 1)
        edges.append((u, v))
    return edges


def bfs_order(n, children, rng):
    """Produce one valid BFS log with random child enqueue orders."""
    from collections import deque

    dq = deque([1])
    order = []
    while dq:
        u = dq.popleft()
        order.append(u)
        kids = children[u][:]
        rng.shuffle(kids)
        for v in kids:
            dq.append(v)
    return order


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    rng = random.Random(seed)

    if size <= 3:
        n = rng.randint(1, 4)
    elif size <= 10:
        n = rng.randint(4, 12)
    elif size <= 40:
        n = rng.randint(20, 60)
    elif size <= 150:
        n = rng.randint(80, 200)
    else:
        # MAX-SCALE: hit q*n bound near 1e6
        n = 100000
        q = 10

    if size <= 150:
        q = max(1, min(20, size // 2 + rng.randint(1, 5)))
        if n * q > 200000:
            q = max(1, 200000 // n)

    edges = build_tree(n, rng)
    children = [[] for _ in range(n + 1)]
    for u, v in edges:
        children[u].append(v)

    queries = []
    for i in range(q):
        kind = rng.randint(0, 4)
        if kind == 0 or n == 1:
            queries.append(bfs_order(n, children, rng))
        elif kind == 1:
            # valid order then swap two positions (often invalid)
            ord_ = bfs_order(n, children, rng)
            if n >= 2:
                a, b = rng.sample(range(n), 2)
                ord_[a], ord_[b] = ord_[b], ord_[a]
            queries.append(ord_)
        elif kind == 2:
            # duplicate / not a permutation
            ord_ = [rng.randint(1, n) for _ in range(n)]
            queries.append(ord_)
        elif kind == 3:
            # reverse of a valid order
            ord_ = bfs_order(n, children, rng)
            queries.append(list(reversed(ord_)))
        else:
            # random permutation
            ord_ = list(range(1, n + 1))
            rng.shuffle(ord_)
            queries.append(ord_)

    out = [str(n)]
    for u, v in edges:
        out.append(f"{u} {v}")
    out.append(str(q))
    for ord_ in queries:
        out.append(" ".join(map(str, ord_)))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
