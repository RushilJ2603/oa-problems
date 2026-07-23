#!/usr/bin/env python3
"""Random valid instance for Cisco Q2. argv[1]=seed, argv[2]=integer size hint (N).

Timestamps are strictly increasing (harness invariant). User-id and window ranges are varied so
some instances trip the threshold and some never do.
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else 0
size = int(sys.argv[2]) if len(sys.argv) > 2 else 12
random.seed(seed)

N = max(1, min(size, 200000))
W = random.choice([1, 3, 5, 10, 50, random.randint(1, 10**9)])
K = random.randint(2, max(2, min(N, 6)))
# A small user pool makes the threshold reachable often; occasionally use a huge id to exercise
# the need for long long / a hash map.
pool_size = random.randint(2, 8)
users = [random.randint(1, 10**9) if random.random() < 0.3 else random.randint(1, 10)
         for _ in range(pool_size)]

out = [f"{N} {W} {K}"]
t = random.randint(0, 5)
for _ in range(N):
    t += random.randint(1, 6)      # strictly increasing
    out.append(f"{t} {random.choice(users)}")
print("\n".join(out))
