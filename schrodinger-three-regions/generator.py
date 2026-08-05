"""One random valid input for Three Regions, One Reorganisation.

usage: python3 generator.py [seed] [size]

`size` moves the magnitude of the numbers, not n — n is 3..10 by the constraints and the whole
point of the problem is that it is small. The shiftingCost is drawn on its own scale so that both
regimes appear: cheap enough that pouring regions together wins, and dear enough that it never does.
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 10
rng = random.Random(seed)

hi = max(1, min(10 ** 9, size * size))
n = rng.randint(3, 10)
machines = [rng.randint(1, hi) for _ in range(n)]
# Half the time draw the targets near achievable sums, so that merging is genuinely tempting.
if rng.random() < 0.5:
    finals = []
    for _ in range(3):
        k = rng.randint(1, n)
        finals.append(max(1, min(10 ** 9, sum(rng.sample(machines, k)) + rng.randint(-3, 3))))
else:
    finals = [rng.randint(1, hi) for _ in range(3)]

print(n)
print(" ".join(map(str, machines)))
print(" ".join(map(str, finals)))
print(rng.choice([1, 2, rng.randint(1, max(1, hi)), rng.randint(1, 10 ** 9)]))
