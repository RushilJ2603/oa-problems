#!/usr/bin/env python3
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 8
random.seed(seed)

total = max(1, size)
cases = []
remaining = total
while remaining > 0:
    L = random.randint(1, max(1, min(remaining, size // 3 + 1)))
    dens = random.random()
    s = ''.join('1' if random.random() < dens else '0' for _ in range(L))
    cases.append(s)
    remaining -= L
print(len(cases))
for c in cases:
    print(c)
