#!/usr/bin/env python3
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 8
random.seed(seed)

n = max(1, size)
s = ''.join(random.choice('()') for _ in range(n))
k = random.randint(0, n)
print(s)
print(k)
