"""One random valid input for Balance the Two Baskets.

usage: python3 generator.py [seed] [size]

Independent uniform arrays make `a` and `b` roughly agree, so almost any greedy lands on the answer
and the tests prove nothing. The shapes below are chosen so the two arrays PULL APART — that is the
only setting where "pick the k biggest by a", "pick the k biggest by a+b" and "pick the k biggest by
min(a,b)" give different sets, which is exactly what the DP has to beat.
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 6
rng = random.Random(seed)

n = max(1, min(50, size))
hi = rng.choice([1, 2, 3, 10, 100, 100])

shape = rng.choice(["random", "random", "anti", "mirror", "one_spike", "flat", "two_camps"])

if shape == "anti":
    # a ascending, b descending: every index that helps one basket hurts the other.
    a = sorted(rng.randint(1, hi) for _ in range(n))
    b = sorted((rng.randint(1, hi) for _ in range(n)), reverse=True)
elif shape == "mirror":
    # b is a's reflection, so the balanced set is not the heavy set.
    a = [rng.randint(1, hi) for _ in range(n)]
    b = [hi + 1 - x for x in a]
elif shape == "one_spike":
    # a single index carries basket a; any answer has to take it despite its weak b.
    a = [rng.randint(1, max(1, hi // 20)) for _ in range(n)]
    b = [rng.randint(1, hi) for _ in range(n)]
    spike = rng.randrange(n)
    a[spike] = hi
    b[spike] = 1
elif shape == "flat":
    va, vb = rng.randint(1, hi), rng.randint(1, hi)
    a = [va] * n
    b = [vb] * n
elif shape == "two_camps":
    # half the indices are good for a, half for b — the split has to be found, not sorted for.
    a, b = [], []
    for i in range(n):
        if rng.random() < 0.5:
            a.append(rng.randint(max(1, hi // 2), hi))
            b.append(rng.randint(1, max(1, hi // 4)))
        else:
            a.append(rng.randint(1, max(1, hi // 4)))
            b.append(rng.randint(max(1, hi // 2), hi))
else:
    a = [rng.randint(1, hi) for _ in range(n)]
    b = [rng.randint(1, hi) for _ in range(n)]

k = rng.randint(1, n)

print("%d %d" % (n, k))
print(" ".join(map(str, a)))
print(" ".join(map(str, b)))
