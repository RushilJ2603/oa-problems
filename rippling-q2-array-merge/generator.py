#!/usr/bin/env python3
"""Two positive-int arrays for the merge problem. argv[1]=seed, argv[2]=size hint.
Usually equal-sum (two random compositions of one total); sometimes unequal (-> -1)."""
import random, sys
seed = int(sys.argv[1]) if len(sys.argv) > 1 else 0
size = int(sys.argv[2]) if len(sys.argv) > 2 else 12
random.seed(seed)
cap = max(1, min(size, 3000))

def composition(total, maxparts):
    # random composition of `total` into positive parts (at most ~maxparts)
    if total <= 1:
        return [total]
    k = random.randint(1, min(total, maxparts))
    cuts = sorted(random.sample(range(1, total), k - 1)) if k > 1 else []
    parts, prev = [], 0
    for c in cuts:
        parts.append(c - prev); prev = c
    parts.append(total - prev)
    return parts

if random.random() < 0.15:
    # unequal sums -> impossible
    X = [random.randint(1, 9) for _ in range(random.randint(1, cap))]
    Y = [random.randint(1, 9) for _ in range(random.randint(1, cap))]
    if sum(X) == sum(Y):
        Y.append(1)
else:
    total = random.randint(1, cap)
    X = composition(total, cap)
    Y = composition(total, cap)

print(len(X)); print(" ".join(map(str, X)))
print(len(Y)); print(" ".join(map(str, Y)))
