#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size tiers to n; large size hits max constraint
    if size <= 3:
        n = random.randint(1, 3)
    elif size <= 10:
        n = random.randint(3, 10)
    elif size <= 40:
        n = random.randint(10, 40)
    elif size <= 150:
        n = random.randint(50, min(150, 200))
    elif size <= 400:
        n = random.randint(200, 400)
    else:
        # MAX-SCALE
        n = 10**5

    # Vary value distribution with seed
    mode = seed % 6
    vals = []
    if mode == 0:
        # mostly small primes / composites
        pool = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 21, 30, 35, 77]
        vals = [random.choice(pool) for _ in range(n)]
    elif mode == 1:
        # all ones
        vals = [1] * n
    elif mode == 2:
        # powers of two and odds
        vals = [random.choice([2, 4, 8, 16, 32, 3, 9, 27, 5, 25, 1]) for _ in range(n)]
    elif mode == 3:
        # large values near bound
        vals = [random.randint(max(1, 10**5 - 1000), 10**5) for _ in range(n)]
    elif mode == 4:
        # chain-linking composites
        primes = [2, 3, 5, 7, 11, 13, 17, 19, 23]
        vals = []
        for i in range(n):
            p = primes[i % len(primes)]
            q = primes[(i + 1) % len(primes)]
            vals.append(min(p * q, 10**5))
    else:
        vals = [random.randint(1, 10**5) for _ in range(n)]

    print(n)
    for v in vals:
        print(v)

if __name__ == "__main__":
    main()
