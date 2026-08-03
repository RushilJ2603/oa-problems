#!/usr/bin/env python3
"""Generate one random valid weighted-coupon-collector input.
CLI: python3 generator.py <seed> <size>
At large size, emit a MAX-SCALE instance (sum W = 1e5).
"""
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    MAX_SUM = 10**5
    MAX_W = 100

    if size >= 200:
        # Max-scale: sum of weights hits 1e5
        target = MAX_SUM
        w = []
        rem = target
        while rem > 0:
            wi = random.randint(1, min(MAX_W, rem))
            w.append(wi)
            rem -= wi
        random.shuffle(w)
        n = len(w)
    else:
        # Keep N <= 16 so the bitmask brute stays fast during cross-checks
        # (gate sizes go up to 120).
        lo = 1
        hi = min(16, max(1, size // 2 + 2))
        if size <= 3:
            hi = 3
        n = random.randint(lo, hi)
        # Vary total weight with size for length diversity
        max_sum = min(MAX_SUM, max(n, size * 15))
        max_sum = min(max_sum, n * MAX_W)
        target = random.randint(n, max_sum)
        w = [1] * n
        rem = target - n
        idxs = list(range(n))
        while rem > 0:
            random.shuffle(idxs)
            progressed = False
            for i in idxs:
                if w[i] < MAX_W and rem > 0:
                    w[i] += 1
                    rem -= 1
                    progressed = True
                if rem == 0:
                    break
            if not progressed:
                break

    print(n)
    print(" ".join(map(str, w)))


if __name__ == "__main__":
    main()
