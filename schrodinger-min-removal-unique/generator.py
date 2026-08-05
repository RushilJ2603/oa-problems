"""One random valid input for Shortest Block to Delete for Distinct Letters.

usage: python3 generator.py [seed] [size]

Deliberately biased towards SMALL alphabets. A random string over all 26 letters repeats almost
immediately, so the interesting structure — a long prefix and a long suffix that are each distinct
but overlap in one letter — only shows up when the alphabet is tight.
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 10
rng = random.Random(seed)

n = max(1, min(200000, size))
k = rng.choice([1, 2, 2, 3, 4, 6, 26])
alphabet = "abcdefghijklmnopqrstuvwxyz"[:k]
print("".join(rng.choice(alphabet) for _ in range(n)))
