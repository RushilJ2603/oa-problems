#!/usr/bin/env python3
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 8
random.seed(seed)

n = max(1, size)
m = max(1, size)
lines = [f"{n} {m}"]
for _ in range(m):
    u = random.randint(1, n)
    v = random.randint(1, n)
    lines.append(f"{u} {v}")
print('\n'.join(lines))
