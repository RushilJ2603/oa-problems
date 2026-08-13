"""One random valid input for Talent Coverage Windows.

usage: python3 generator.py [seed] [size]

Drawing talents uniformly from 1..talentsCount is the trap here. With k small relative to n almost
every start covers everything within a handful of students, so the -1 tail never appears and the
answers are all tiny — a suite like that is passed by code that never checks completeness at all.

So k is drawn RELATIVE to n, across the whole useful range: k = 1 (every answer is 1), k around n
(the covering windows are long and the -1 tail is most of the array), and k > the number of distinct
talents actually present (every answer is -1). Several shapes then attack the sweep specifically:

  blocks    - all copies of a talent sit together, so the window has to span nearly the whole queue
  rare      - one talent appears once, at a random spot; every start past it answers -1
  tail_only - the last talent appears only at the very end, so ans[0] is n and the rest step down
  perm      - a permutation repeated, the case where the window length is exactly k everywhere
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 8
rng = random.Random(seed)

n = max(1, min(200000, size))

# k relative to n, so the -1 tail and the long-window cases actually occur.
choice = rng.random()
if choice < 0.12:
    k = 1
elif choice < 0.30:
    k = max(1, min(200000, n + rng.randint(0, 3)))      # often unsatisfiable
elif choice < 0.55:
    k = max(1, n // rng.choice([1, 2, 3]))
else:
    k = max(1, min(200000, rng.randint(1, max(1, min(n, 12)))))

shape = rng.choice(["random", "random", "blocks", "rare", "tail_only", "perm", "one_value"])

if shape == "blocks":
    talent = []
    order = list(range(1, k + 1))
    rng.shuffle(order)
    i = 0
    while len(talent) < n:
        t = order[i % len(order)]
        talent.extend([t] * rng.randint(1, max(1, n // max(1, k))))
        i += 1
    talent = talent[:n]
elif shape == "rare":
    # One talent appears exactly once. Every start after that position is -1.
    rare = rng.randint(1, k)
    pool = [t for t in range(1, k + 1) if t != rare] or [rare]
    talent = [rng.choice(pool) for _ in range(n)]
    talent[rng.randrange(n)] = rare
elif shape == "tail_only":
    last = rng.randint(1, k)
    pool = [t for t in range(1, k + 1) if t != last] or [last]
    talent = [rng.choice(pool) for _ in range(n)]
    talent[-1] = last
elif shape == "perm":
    order = list(range(1, k + 1))
    talent = []
    while len(talent) < n:
        rng.shuffle(order)
        talent.extend(order)
    talent = talent[:n]
elif shape == "one_value":
    v = rng.randint(1, k)
    talent = [v] * n
else:
    talent = [rng.randint(1, k) for _ in range(n)]

print(n, k)
sys.stdout.write(" ".join(str(t) for t in talent) + "\n")
