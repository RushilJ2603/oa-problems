#!/usr/bin/env python3
"""Deterministic generator: python3 generator.py <seed> <size>"""
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    rng = random.Random(seed)

    # Map size -> M (= 2*n); large size hits constraint max M=14 (n=7)
    if size <= 2:
        m = 2
    elif size <= 5:
        m = rng.choice([2, 4])
    elif size <= 12:
        m = rng.choice([4, 6, 8])
    elif size <= 40:
        m = rng.choice([8, 10, 12])
    else:
        m = 14  # max-scale n=7

    mode = seed % 6
    nums = []
    if mode == 0:
        # all equal
        v = rng.randint(1, 10**6)
        nums = [v] * m
    elif mode == 1:
        # max-ish values near 1e6
        nums = [rng.randint(10**5, 10**6) for _ in range(m)]
    elif mode == 2:
        # gcd-heavy multiples of small primes
        base = [2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 16, 18, 20, 24, 30, 36, 48, 60, 72, 96, 120]
        nums = [rng.choice(base) * rng.choice([1, 2, 3, 4, 5]) for _ in range(m)]
    elif mode == 3:
        # sorted ascending
        nums = sorted(rng.randint(1, 10**6) for _ in range(m))
    elif mode == 4:
        # reverse / descending
        nums = sorted((rng.randint(1, 10**6) for _ in range(m)), reverse=True)
    else:
        # uniform random
        nums = [rng.randint(1, 10**6) for _ in range(m)]

    print(m)
    print(" ".join(map(str, nums)))


if __name__ == "__main__":
    main()
