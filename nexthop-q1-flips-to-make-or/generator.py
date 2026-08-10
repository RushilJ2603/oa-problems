"""One random valid input for Minimum Flips to Make a OR b Equal to c.

usage: python3 generator.py [seed] [size]

Three independent uniform draws almost never produce the cases that separate a correct solution
from a wrong one: with random bits, "c_i = 0 and both a_i and b_i set" (the only 2-flip case) shows
up in a quarter of the bits and a solution that charges 1 there is caught immediately — but
"c_i = 1 and the OR is already 1" (the only free case) and "c_i = 0 and the OR is already 0" get
mixed together and a sign error can hide. The shapes below force each case to dominate in turn.

`size` controls the BIT WIDTH, and the top bit of the width is always set somewhere, so a larger
size really does produce a longer input line (32-bit overflow lives at size >= ~200).
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 6
rng = random.Random(seed)

# size 1 -> 4 bits, size 400 -> 60 bits, monotone in between.
bits = max(2, min(60, 4 + (56 * min(size, 400)) // 400))
top = 1 << (bits - 1)
full = (1 << bits) - 1

shape = rng.choice(["random", "random", "c_zero", "c_full", "a_eq_b", "already_ok",
                    "disjoint", "c_disjoint", "sparse"])

if shape == "c_zero":
    # Every set bit of a and b has to be cleared: the maximum-cost shape.
    a = rng.randint(0, full)
    b = rng.randint(0, full)
    c = 0
elif shape == "c_full":
    # No bit may be cleared, only turned on: pure "1 flip per missing bit".
    a = rng.randint(0, full)
    b = rng.randint(0, full)
    c = full
elif shape == "a_eq_b":
    # a and b agree everywhere, so every clear costs 2 and every set costs 1.
    a = rng.randint(0, full)
    b = a
    c = rng.randint(0, full)
elif shape == "already_ok":
    # c is exactly the current OR — the answer is 0 even though the numbers are large.
    a = rng.randint(0, full)
    b = rng.randint(0, full)
    c = a | b
elif shape == "disjoint":
    # a and b share no bits, so no bit ever costs 2.
    m = rng.randint(0, full)
    a = m
    b = full ^ m
    c = rng.randint(0, full)
elif shape == "c_disjoint":
    # c is the complement of the current OR: every bit is wrong, in both directions at once.
    a = rng.randint(0, full)
    b = rng.randint(0, full)
    c = full ^ (a | b)
elif shape == "sparse":
    # Only a handful of bits set anywhere — most of the word is the "all zero, c zero" free case.
    def sparse():
        v = 0
        for _ in range(rng.randint(0, 3)):
            v |= 1 << rng.randrange(bits)
        return v
    a, b, c = sparse(), sparse(), sparse()
else:
    a = rng.randint(0, full)
    b = rng.randint(0, full)
    c = rng.randint(0, full)

# Guarantee the declared width is actually exercised (and that the printed line grows with size).
which = rng.randrange(3)
if which == 0:
    a |= top
elif which == 1:
    b |= top
else:
    c |= top

print("%d %d %d" % (a, b, c))
