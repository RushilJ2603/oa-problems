#!/usr/bin/env python3
"""Random valid instance for Cisco Q1. argv[1]=seed, argv[2]=integer size hint (grid side).

Guarantees the harness's invariants: start/end/kiosk cells are open and distinct, coordinates
in range, kiosks pairwise distinct. Solvability is NOT forced — plenty of -1 cases are useful.
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else 0
size = int(sys.argv[2]) if len(sys.argv) > 2 else 12
random.seed(seed)

n = max(1, min(size, 50))
R = random.randint(1, n)
C = random.randint(1, n)
wall_p = random.choice([0.0, 0.1, 0.2, 0.3])
grid = [[1 if random.random() < wall_p else 0 for _ in range(C)] for _ in range(R)]

cells = [(r, c) for r in range(R) for c in range(C)]
(sr, sc) = random.choice(cells); grid[sr][sc] = 0
(er, ec) = random.choice(cells); grid[er][ec] = 0

B = random.randint(1, 50)
K = random.randint(0, 10)

open_cells = [(r, c) for r in range(R) for c in range(C)
              if grid[r][c] == 0 and (r, c) != (sr, sc)]
random.shuffle(open_cells)
M = random.randint(0, min(len(open_cells), 10))
stations = open_cells[:M]

out = [f"{R} {C}"]
for row in grid:
    out.append(" ".join(map(str, row)))
out.append(f"{sr} {sc}")
out.append(f"{er} {ec}")
out.append(str(B))
out.append(str(M))
for (a, b) in stations:
    out.append(f"{a} {b}")
out.append(str(K))
print("\n".join(out))
