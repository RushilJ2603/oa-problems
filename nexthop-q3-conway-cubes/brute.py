"""Independent solution.

reference.cpp allocates a padded 3-D array and visits every cell of it. This one has no array and no
bounds at all: it keeps a SET of the active coordinates and, each cycle, pours one vote into a
Counter for each of the 26 neighbours of each active cube. A cube's neighbour count is then just its
tally, and every cube with a tally of zero — the overwhelming majority of the infinite grid — is
never represented.

Because the coordinates are unbounded integers, this solution cannot have an off-by-one in the
padding, which is exactly the class of bug the array version is exposed to. If the reference's
margin were one cell too small the two would disagree.
"""
import sys
from collections import Counter
from itertools import product

OFFSETS = [d for d in product((-1, 0, 1), repeat=3) if d != (0, 0, 0)]


def main() -> None:
    data = sys.stdin.read().split()
    R, T = int(data[0]), int(data[1])
    rows = data[2:2 + R]

    active = {(0, i, j) for i, row in enumerate(rows) for j, ch in enumerate(row) if ch == "#"}

    for _ in range(T):
        votes = Counter()
        for (z, x, y) in active:
            for (dz, dx, dy) in OFFSETS:
                votes[(z + dz, x + dx, y + dy)] += 1
        active = {p for p, c in votes.items() if c == 3 or (c == 2 and p in active)}

    print(len(active))


main()
