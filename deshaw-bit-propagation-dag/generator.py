import sys
import random

seed = int(sys.argv[1])
size = int(sys.argv[2])
random.seed(seed)

n = max(2, min(size, 2000))
# Edges only go from a lower index to a higher index -> guaranteed acyclic, node 0 is a source.
# Small out-degree keeps the propagated counts within 64-bit range.
edges = []
for i in range(n - 1):
    k = random.randint(1, 3)
    hi = n - 1 - i
    targets = random.sample(range(i + 1, n), min(k, hi))
    for t in targets:
        edges.append((i, t))
if not any(u == 0 for u, v in edges):
    edges.append((0, random.randint(1, n - 1)))
random.shuffle(edges)
out = [f"{n} {len(edges)}"]
for u, v in edges:
    out.append(f"{u} {v}")
sys.stdout.write("\n".join(out) + "\n")
