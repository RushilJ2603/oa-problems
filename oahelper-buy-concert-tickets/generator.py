#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 200:
        # MAX-SCALE
        m = 10**6
        k = random.choice([1, 2, 3, 10000, random.randint(2, 10000)])
    else:
        # keep small for random brute cross-check (size <= 120 in the gate)
        m = max(0, min(size * 3, 500))
        if random.random() < 0.1:
            m = 0
        k = random.randint(1, 10000)
        if random.random() < 0.15:
            k = 1
        if random.random() < 0.1:
            k = 10000

    print(m)
    print(k)

if __name__ == "__main__":
    main()
