import sys
import random

seed = int(sys.argv[1])
size = int(sys.argv[2])
random.seed(seed)

mx = max(1, min(size, 500))
m = random.randint(1, mx)
n = random.randint(1, mx)
# keep total cells bounded even at max size
while m * n > 250000:
    if m >= n:
        m = max(1, m // 2)
    else:
        n = max(1, n // 2)

dirs = "UDLR"
out = [f"{m} {n}"]
for _ in range(m):
    out.append("".join(random.choice(dirs) for _ in range(n)))
sys.stdout.write("\n".join(out) + "\n")
