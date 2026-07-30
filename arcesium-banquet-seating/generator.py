#!/usr/bin/env python3
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 6
random.seed(seed)

# Keep the guest count small enough for the exhaustive brute (n! ) while letting demand magnitudes and
# the chair count grow with size (so larger `size` really does produce a bigger, harder input).
n = min(max(1, size), 8)
cap = min(10 ** 8, max(3, size ** 3))
d = [random.randint(1, cap) for _ in range(n)]

S, mn, mx = sum(d), min(d), max(d)
need = n + (S - mn) + mx                 # true threshold — centre m here to stress near-boundary cases
delta = random.randint(-(cap + 3), cap + 3)
m = max(1, need + delta)

print(f"{m} {n}")
print(' '.join(map(str, d)))
