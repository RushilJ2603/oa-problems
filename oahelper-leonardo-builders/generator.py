#!/usr/bin/env python3
"""Deterministic generator: python3 generator.py <seed> <size>"""
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 800:
        Xp = Yp = 500
    elif size >= 400:
        Xp = Yp = 200
    elif size >= 150:
        Xp = Yp = min(100, size // 2)
    elif size >= 40:
        Xp = Yp = min(40, size)
    else:
        Xp = Yp = max(2, min(20, size + 1))

    # Building: axis-aligned rectangle of varying size (always 4 corners)
    # Plus occasional L-shape / triangle for variety
    mode = seed % 4
    if mode == 0:
        bw = random.randint(1, max(1, min(Xp, 10)))
        bh = random.randint(1, max(1, min(Yp, 10)))
        building = [(0, 0), (bw, 0), (bw, bh), (0, bh)]
    elif mode == 1:
        # triangle
        building = [(0, 0), (random.randint(1, 5), 0), (0, random.randint(1, 5))]
    elif mode == 2:
        # rectangle not at origin (tests normalize)
        ox = random.randint(-1000, 1000)
        oy = random.randint(-1000, 1000)
        bw = random.randint(1, 4)
        bh = random.randint(1, 4)
        building = [(ox, oy), (ox + bw, oy), (ox + bw, oy + bh), (ox, oy + bh)]
    else:
        # L-shape
        building = [(0, 0), (2, 0), (2, 1), (1, 1), (1, 2), (0, 2)]

    # Trees: random interior points; density grows with size
    max_trees = max(0, (Xp - 1) * (Yp - 1))
    if size >= 800:
        N = min(max_trees, 5000)
    elif size >= 400:
        N = min(max_trees, 500)
    else:
        N = min(max_trees, max(0, size // 2))

    trees = set()
    attempts = 0
    while len(trees) < N and attempts < N * 20 + 10:
        attempts += 1
        if Xp <= 1 or Yp <= 1:
            break
        x = random.randint(1, Xp - 1)
        y = random.randint(1, Yp - 1)
        trees.add((x, y))
    trees = list(trees)
    N = len(trees)

    K = len(building)
    lines = [f"{Xp} {Yp} {N}"]
    for x, y in trees:
        lines.append(f"{x} {y}")
    lines.append(str(K))
    for x, y in building:
        lines.append(f"{x} {y}")
    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
