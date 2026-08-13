"""One random valid input for Office Placement.

usage: python3 generator.py [seed] [size]

The whole input space is 458 triples, so this does not build an input so much as choose one — and
choosing uniformly is the trap. Most (h, w) pairs with h*w <= 27 are thin strips (1 x k, 2 x k),
where the answer is a one-dimensional spacing argument that a wrong solution can still get right.
The interesting instances are the fat ones near the cell ceiling with several offices, where the
placement genuinely has to be two-dimensional.

`size` selects the band: small sizes stay in tiny grids with one or two offices, large sizes push
h*w toward 27 and n toward 5 — the largest search space, and the slowest case for anything that
enumerates placements.
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 8
rng = random.Random(seed)

pairs = [(h, w) for h in range(1, 28) for w in range(1, 28) if h * w <= 27]

scale = max(1, min(150, size))
if scale <= 6:
    pool = [(h, w) for h, w in pairs if h * w <= 6]
    nmax = 2
elif scale <= 30:
    pool = [(h, w) for h, w in pairs if h * w <= 15]
    nmax = 3
else:
    # The heavy band: as many cells as the limit allows, and enough offices to make the choice hard.
    # Most pairs this large are still strips (1x27, 2x13), so the FAT ones are drawn deliberately
    # rather than left to chance — they are the shapes where the placement is genuinely 2-D.
    fat = [(h, w) for h, w in pairs if h * w >= 18 and min(h, w) >= 3]
    strips = [(h, w) for h, w in pairs if h * w >= 18 and min(h, w) < 3]
    pool = fat if (rng.random() < 0.7 or not strips) else strips
    nmax = 5

h, w = rng.choice(pool or pairs)
n = rng.randint(1, min(nmax, h * w))
print(h, w, n)
