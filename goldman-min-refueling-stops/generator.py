#!/usr/bin/env python3
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 8
random.seed(seed)

n = max(0, size)
big = random.choice([40, 1000, 10 ** 9])
target = max(big, n + 2)                       # ensure room for n distinct positions in [1, target)
start = random.randint(0, target)              # sometimes already enough (0 stops) or too little (-1)
positions = sorted(random.sample(range(1, target), n)) if n > 0 else []
lines = [f"{target} {start}", str(n)]
for p in positions:
    lines.append(f"{p} {random.randint(1, target)}")
print('\n'.join(lines))
