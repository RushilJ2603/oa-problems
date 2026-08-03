#!/usr/bin/env python3
"""Deterministic generator: python3 generator.py <seed> <size>"""
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size to X; large size -> max-scale X=10000 with up to 5000 prereqs
    if size >= 2000:
        x = 10000
        max_edges = 5000
    elif size >= 800:
        x = 3000
        max_edges = 3000
    elif size >= 300:
        x = min(1000, 10000)
        max_edges = min(2000, x)
    elif size >= 100:
        x = min(size, 400)
        max_edges = min(800, x)
    else:
        x = max(1, min(size, 40))
        max_edges = min(x, max(0, size // 2))

    boost = [0] * (x + 1)
    for i in range(1, x + 1):
        # mix of positive, negative, zero
        r = random.random()
        if r < 0.4:
            boost[i] = random.randint(1, 10**6)
        elif r < 0.8:
            boost[i] = -random.randint(1, 10**6)
        else:
            boost[i] = 0

    # Build a random DAG: edges only from higher label to lower (topo order)
    # prereq of i is a lower-numbered cell
    edges = []
    for i in range(2, x + 1):
        if len(edges) >= max_edges:
            break
        if random.random() < 0.35:
            p = random.randint(1, i - 1)
            edges.append((i, p))

    # Extra random edges while under budget
    attempts = 0
    while len(edges) < max_edges and attempts < max_edges * 3:
        attempts += 1
        a = random.randint(2, x)
        b = random.randint(1, a - 1)
        edges.append((a, b))

    # Deduplicate per node
    from collections import defaultdict
    pr = defaultdict(set)
    for a, b in edges:
        if len(pr) > max_edges and b in pr[a]:
            continue
        pr[a].add(b)
    # Cap total
    flat = []
    for a in sorted(pr):
        for b in pr[a]:
            flat.append((a, b))
            if len(flat) >= max_edges:
                break
        if len(flat) >= max_edges:
            break
    pr2 = defaultdict(list)
    for a, b in flat:
        pr2[a].append(b)

    out = [str(x)]
    for i in range(1, x + 1):
        ps = pr2[i]
        out.append(f"{boost[i]} {len(ps)}" + ("" if not ps else " " + " ".join(map(str, ps))))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
