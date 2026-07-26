import sys
import random

seed = int(sys.argv[1])
size = int(sys.argv[2])
random.seed(seed)

n = max(1, min(size, 700))
k = [[0] * n for _ in range(n)]
for i in range(n):
    for j in range(n):
        if i != j:
            k[i][j] = random.randint(0, 1)

# About half the time, plant a genuine celebrity so both "exists" and "does not exist" appear.
if n >= 1 and random.random() < 0.5:
    c = random.randrange(n)
    for i in range(n):
        if i != c:
            k[i][c] = 1   # everyone knows c
            k[c][i] = 0   # c knows no one

out = [str(n)]
for row in k:
    out.append(" ".join(map(str, row)))
sys.stdout.write("\n".join(out) + "\n")
