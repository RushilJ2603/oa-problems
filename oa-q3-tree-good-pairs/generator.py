#!/usr/bin/env python3
"""Random rooted tree for Tree Good Pairs. argv[1]=seed, argv[2]=size hint (n).
Node i>=1 attaches to a random earlier node, guaranteeing a tree rooted at 0."""
import random, sys
seed = int(sys.argv[1]) if len(sys.argv) > 1 else 0
size = int(sys.argv[2]) if len(sys.argv) > 2 else 12
random.seed(seed)
n = max(1, min(size, 100000))
n = random.randint(1, n)
w = [random.randint(0, 10**9) for _ in range(n)]
out = [str(n), " ".join(map(str, w))]
# occasionally force a deep path (parent = i-1) to exercise depth
deep = random.random() < 0.2
for i in range(1, n):
    p = i - 1 if deep else random.randint(0, i - 1)
    out.append(f"{p} {i} {random.randint(0, 10**6)}")
print("\n".join(out))
