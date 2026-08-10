"""One random valid input for Conway Cubes.

usage: python3 generator.py [seed] [size]

A uniformly random slice at 50% density is the least informative test this problem has: it is dense
enough that almost everything dies in the first cycle or two, so the answer stops depending on the
cycle count and a solution with the wrong survival rule still lands close. The shapes below either
keep the automaton ALIVE for the full run (the glider, which is the one AoC ships because it stays
interesting for six cycles) or push it to a boundary case (empty, solid, a single cube).

`size` drives both the slice dimensions and the cycle count, so a large size is genuinely the
expensive input and not just a wider grid that dies immediately.
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 6
rng = random.Random(seed)

# Floors matter more than they look. A 1x1 or 2x2 slice dies to nothing within one cycle whatever
# it started as, and T = 0 never runs the automaton at all — so a generator that reaches those
# produces a pile of tests whose answer is 0, and `return 0` scores most of the suite. Both
# degenerate cases are worth testing exactly once, which is what tests/edge is for; the random layer
# stays at 3x3 and one cycle minimum so every test it produces actually simulates something.
R = max(3, min(25, 3 + size // 8))
C = max(3, min(25, 3 + size // 8))
T = max(1, min(12, size // 50))

shape = rng.choice(["random", "random", "glider", "glider", "glider", "sparse",
                    "solid", "blinker", "stripes"])

grid = [["."] * C for _ in range(R)]


def put(pattern, top, left):
    for di, row in enumerate(pattern):
        for dj, ch in enumerate(row):
            i, j = top + di, left + dj
            if 0 <= i < R and 0 <= j < C and ch == "#":
                grid[i][j] = "#"


if shape == "solid":
    grid = [["#"] * C for _ in range(R)]
elif shape == "glider":
    # The pattern from the problem statement: the one starting slice that is still evolving at T=6.
    for _ in range(rng.randint(1, max(1, (R * C) // 12))):
        put([".#.", "..#", "###"], rng.randrange(R), rng.randrange(C))
elif shape == "blinker":
    for _ in range(rng.randint(1, max(1, (R * C) // 8))):
        if rng.random() < 0.5:
            put(["###"], rng.randrange(R), rng.randrange(C))
        else:
            put(["#", "#", "#"], rng.randrange(R), rng.randrange(C))
elif shape == "sparse":
    for _ in range(rng.randint(max(2, (R * C) // 8), max(3, (R * C) // 3))):
        grid[rng.randrange(R)][rng.randrange(C)] = "#"
elif shape == "stripes":
    # Regular structure: every cube has the same neighbourhood, so a wrong survival threshold
    # changes the answer by a large, obvious factor rather than by one or two cubes.
    period = rng.choice([2, 3, 4])
    for i in range(R):
        for j in range(C):
            if (i + j) % period == 0:
                grid[i][j] = "#"
else:
    p = rng.choice([0.1, 0.2, 0.35, 0.5, 0.65, 0.85])
    for i in range(R):
        for j in range(C):
            if rng.random() < p:
                grid[i][j] = "#"

print("%d %d" % (R, T))
for row in grid:
    print("".join(row))
