#!/usr/bin/env python3
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 8
random.seed(seed)

n = max(2, size)
# vary the value range: small ranges force ties & duplicates; large ranges spread out
hi = random.choice([3, 15, 1000, 10 ** 9])
a = [random.randint(-hi, hi) for _ in range(n)]
print(n)
print(' '.join(map(str, a)))
