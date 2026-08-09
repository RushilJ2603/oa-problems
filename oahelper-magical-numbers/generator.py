"""One random valid input for Magical Numbers.

usage: python3 generator.py [seed] [size]

Uniform random n is a poor test: a random 30-bit number has popcount near 15 and the factorials
rarely help, so a wrong "just print popcount" solution survives. The draws below deliberately land on
and around the magical values themselves — exactly where using a factorial beats using more powers of
two, and where an off-by-one in the "is it magical" test shows up.
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 5
rng = random.Random(seed)

LIMIT = 10 ** 9
t = max(1, min(100, size))

powers = []
p = 1
while p <= LIMIT:
    powers.append(p)
    p *= 2
facts = []
f, a = 1, 1
while f <= LIMIT:
    facts.append(f)
    a += 1
    f *= a
magical = sorted(set(powers + facts))


def draw():
    kind = rng.randint(0, 6)
    if kind == 0:                                   # exactly a magical number -> answer 1
        return rng.choice(magical)
    if kind == 1:                                   # just off a magical number
        return max(1, min(LIMIT, rng.choice(magical) + rng.choice([-2, -1, 1, 2])))
    if kind == 2:                                   # a sum of a few magical numbers
        k = rng.randint(2, 4)
        s = sum(rng.sample(magical, k))
        return max(1, min(LIMIT, s))
    if kind == 3:                                   # high popcount: factorials should win
        bits = rng.randint(10, 29)
        return max(1, min(LIMIT, (1 << bits) - 1))
    if kind == 4:                                   # small values, where every answer is reachable
        return rng.randint(1, 300)
    if kind == 5:                                   # near the ceiling
        return rng.randint(LIMIT - 5000, LIMIT)
    return rng.randint(1, LIMIT)                    # plain uniform


print(t)
for _ in range(t):
    print(draw())
