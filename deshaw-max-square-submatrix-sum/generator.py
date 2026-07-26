import sys
import random

seed = int(sys.argv[1])
size = int(sys.argv[2])
random.seed(seed)

mx = max(1, min(size, 300))
m = random.randint(1, mx)
n = random.randint(1, mx)
while m * n > 90000:
    if m >= n:
        m = max(1, m // 2)
    else:
        n = max(1, n // 2)

hi = random.choice([1, 9, 100, 10**6, 10**9])
grid = [[random.randint(0, hi) for _ in range(n)] for _ in range(m)]
total = sum(sum(row) for row in grid)
# choose k to span the range of answers: sometimes tiny, sometimes huge
r = random.random()
if r < 0.15:
    k = 0
elif r < 0.3:
    k = min((min(min(row) for row in grid)), total)   # around the smallest cell
elif r < 0.85:
    k = random.randint(0, total)
else:
    k = total + random.randint(0, 10**9)              # whole grid fits

out = [f"{m} {n} {k}"]
for row in grid:
    out.append(" ".join(map(str, row)))
sys.stdout.write("\n".join(out) + "\n")
