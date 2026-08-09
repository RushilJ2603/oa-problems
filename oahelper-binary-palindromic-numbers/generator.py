"""One random valid input for Binary Palindromic Numbers.

usage: python3 generator.py [seed] [size]

Uniform random N is nearly worthless here: almost every random 31-bit number sits a few thousand
operations from the nearest palindrome, so the answers all look alike and an implementation that
handles only even lengths still passes. The draws below sit ON palindromes (answer 0), one step off
them, and at the midpoints of the widest gaps, which is where the two neighbouring lengths compete.
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 6
rng = random.Random(seed)

LIMIT = 2 * 10 ** 9
# Keep the query count modest: the interesting variety is in the VALUES, and the max-scale T lives
# in the curated edge tests.
t = max(1, min(2000, size))


def palindromes_upto(limit):
    out = []
    for L in range(1, 33):
        half = (L + 1) // 2
        for h in range(1 << (half - 1), 1 << half):
            v = h
            for i in range(L - half - 1, -1, -1):
                v = (v << 1) | ((h >> (half - 1 - i)) & 1)
            if v <= limit:
                out.append(v)
    return sorted(set(out))


PAL = palindromes_upto(LIMIT)


def draw():
    kind = rng.randint(0, 5)
    if kind == 0:                                    # exactly a palindrome -> answer 0
        return rng.choice(PAL)
    if kind == 1:                                    # a step or two off a palindrome
        return max(1, min(LIMIT, rng.choice(PAL) + rng.randint(-3, 3)))
    if kind == 2:                                    # midway between neighbours: the widest gaps
        i = rng.randrange(len(PAL) - 1)
        return max(1, min(LIMIT, (PAL[i] + PAL[i + 1]) // 2))
    if kind == 3:                                    # powers of two: 100...0 is never a palindrome
        return min(LIMIT, 1 << rng.randint(0, 30))
    if kind == 4:                                    # small values, checkable by hand
        return rng.randint(1, 200)
    return rng.randint(1, LIMIT)


print(t)
for _ in range(t):
    print(draw())
