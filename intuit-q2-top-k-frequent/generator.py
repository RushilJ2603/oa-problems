"""One random valid input for Top K Frequent Elements.

usage: python3 generator.py [seed] [size]

Biased towards a SMALL tag vocabulary. A random draw from a large vocabulary makes almost every count
equal to 1, which only ever exercises the lexicographic tie-break; a tight vocabulary produces the
mixed frequency ladders where a wrong comparator actually shows up.

The vocabulary is capped by how many distinct strings the chosen alphabet and length can actually
spell — asking for more than that in a rejection-sampling loop never terminates.
"""
import itertools
import random
import string
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 10
rng = random.Random(seed)

n = max(1, min(200000, size))

# Short tags over a tight alphabet collide often, which is what makes the tie-break interesting;
# occasionally go long to exercise 20-character comparisons and shared prefixes.
maxlen = rng.choice([1, 1, 2, 3, 8, 20])
alpha = string.ascii_lowercase[:rng.choice([2, 3, 4, 26])]

# How many distinct tags this (alphabet, maxlen) pair can spell at all. Stop counting past the point
# where it stops being the binding limit.
capacity = 0
for L in range(1, maxlen + 1):
    capacity += len(alpha) ** L
    if capacity > 400000:
        break

# Vocabulary size relative to n: sometimes far fewer tags than slots (heavy repeats, clear winners),
# sometimes nearly as many (a field of ties decided purely by spelling).
vocab_n = rng.choice([1, 2, 3, 5, max(1, n // 8), max(1, n // 2), n])
# 20k distinct tags is already a rich instance and keeps this generator well under a second at
# n = 200000; the genuinely extreme "every tag distinct" case is a curated edge test, not a random
# one, so there is nothing to gain from spending 13 seconds spelling 200000 unique strings here.
vocab_n = max(1, min(vocab_n, n, capacity, 20000))

if capacity <= 20000:
    # Small universe: enumerate it and sample, so a request for most of it still terminates.
    pool = []
    for L in range(1, maxlen + 1):
        for t in itertools.product(alpha, repeat=L):
            pool.append("".join(t))
        if len(pool) >= capacity:
            break
    vocab = sorted(rng.sample(pool, vocab_n))
else:
    # Large universe: collisions are rare, so rejection sampling is cheap and bounded in practice.
    # Build each tag with ONE choices() call — a per-character rng.choice loop costs seconds at
    # n = 200000, and stress mode in the app calls this generator on a request deadline.
    seen = set()
    while len(seen) < vocab_n:
        need = vocab_n - len(seen)
        for _ in range(need):
            seen.add("".join(rng.choices(alpha, k=rng.randint(1, maxlen))))
    vocab = sorted(seen)

# Weight the vocabulary unevenly so counts form a ladder rather than a flat line.
weights = [rng.randint(1, 10) for _ in vocab]
tags = rng.choices(vocab, weights=weights, k=n)

k = rng.randint(1, len(set(tags)))

print(n)
print(" ".join(tags))
print(k)
