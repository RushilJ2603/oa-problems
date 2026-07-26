#!/usr/bin/env python3
"""Generate one random valid drone-delivery instance.
CLI: python3 generator.py <seed> <size>
At large size, emits near max-scale grids (up to 50x50).
"""
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size -> dimensions; large size hits constraint bounds
    if size <= 5:
        rows = random.randint(1, 3)
        cols = random.randint(1, 4)
        B = random.randint(1, 4)
        K = random.randint(0, 2)
    elif size <= 30:
        rows = random.randint(3, 8)
        cols = random.randint(3, 8)
        B = random.randint(2, 10)
        K = random.randint(0, 4)
    elif size <= 100:
        rows = random.randint(10, 25)
        cols = random.randint(10, 25)
        B = random.randint(5, 25)
        K = random.randint(0, 7)
    else:
        rows = 50
        cols = 50
        B = 50
        K = 10

    # Build open grid with some walls (~20%), keep connectivity loosely
    grid = [[0] * cols for _ in range(rows)]
    open_cells = [(r, c) for r in range(rows) for c in range(cols)]
    wall_count = max(0, int(len(open_cells) * 0.15))
    # never wall every cell: leave enough open
    for r, c in random.sample(open_cells, min(wall_count, max(0, len(open_cells) - 2))):
        grid[r][c] = 1

    opens = [(r, c) for r in range(rows) for c in range(cols) if grid[r][c] == 0]
    if len(opens) < 2:
        # force at least two open cells
        grid = [[0] * cols for _ in range(rows)]
        opens = [(r, c) for r in range(rows) for c in range(cols)]

    sr, sc = random.choice(opens)
    er, ec = random.choice(opens)

    remaining = [p for p in opens if p != (sr, sc) or True]
    M = random.randint(0, min(len(opens), max(1, rows * cols // 10), 20 if size < 100 else 40))
    stations = random.sample(opens, M) if M > 0 else []

    print(rows, cols)
    for r in range(rows):
        print(" ".join(map(str, grid[r])))
    print(sr, sc)
    print(er, ec)
    print(B)
    print(M)
    for r, c in stations:
        print(r, c)
    print(K)


if __name__ == "__main__":
    main()
