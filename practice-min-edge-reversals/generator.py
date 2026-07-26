import sys
import random

seed = int(sys.argv[1])
size = int(sys.argv[2])
random.seed(seed)

n = max(2, min(size, 2000))
max_edges = min(n * (n - 1), 6000)
m = random.randint(0, max(0, min(max_edges, 3 * n)))
lines = [f"{n} {m}"]
for _ in range(m):
    u = random.randint(1, n)
    v = random.randint(1, n)
    while v == u:
        v = random.randint(1, n)
    lines.append(f"{u} {v}")
s = random.randint(1, n)
t = random.randint(1, n)
while t == s:
    t = random.randint(1, n)
lines.append(f"{s} {t}")
sys.stdout.write("\n".join(lines) + "\n")
