#!/usr/bin/env python3
"""Random sensors. argv[1]=seed, argv[2]=size hint (n)."""
import random, sys
seed = int(sys.argv[1]) if len(sys.argv) > 1 else 0
size = int(sys.argv[2]) if len(sys.argv) > 2 else 12
random.seed(seed)
n = max(2, min(size, 100000))
n = random.randint(2, n)
span = random.choice([50, 1000, 10**9])
p = [random.randint(-span, span) for _ in range(n)]
r = [random.randint(0, span // 2 + 1) for _ in range(n)]
print(n)
print(" ".join(map(str, p)))
print(" ".join(map(str, r)))
