#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    if size >= 400:
        n = 100000
    elif size >= 150:
        n = min(100000, size * 50)
    elif size >= 40:
        n = min(1000, size * 5)
    else:
        n = max(1, min(20, size))
    # A[0] = 0; remaining non-negative
    vals = [0]
    lo, hi = 0, 10**9
    mode = seed % 5
    for i in range(1, n):
        if mode == 0:
            vals.append(random.randint(0, 1000))
        elif mode == 1:
            vals.append(i * (hi // max(n, 1)))
        elif mode == 2:
            vals.append(random.choice([0, 1, 2, hi, hi - 1]))
        elif mode == 3:
            vals.append(random.randint(0, hi))
        else:
            vals.append(random.randint(0, max(1, 100 * n)))
    print(n)
    print(' '.join(map(str, vals)))

if __name__ == "__main__":
    main()
