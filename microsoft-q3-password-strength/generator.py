#!/usr/bin/env python3
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 8
random.seed(seed)

n = max(1, size)
c = max(0, size // 2)
# pools biased so different weakness rules fire often
pools = [
    "0123456789",                 # all-digit
    "ABCDEFGHIJKLMNOP",           # all-upper
    "abcdefghijklmnop",           # all-lower
    "aB3#xY7$mN&qZ",              # mixed / strong-ish
    "abcABC123",                  # substring-prone
]
lines = [str(n)]
for _ in range(n):
    L = random.randint(1, 12)
    pool = random.choice(pools)
    lines.append(''.join(random.choice(pool) for _ in range(L)))
lines.append(str(c))
for _ in range(c):
    L = random.randint(1, 4)
    lines.append(''.join(random.choice("abcABC123") for _ in range(L)))
print('\n'.join(lines))
