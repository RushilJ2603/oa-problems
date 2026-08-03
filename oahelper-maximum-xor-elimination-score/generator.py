#!/usr/bin/env python3
"""Emit one random valid input. CLI: python3 generator.py <seed> <size>"""
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size → n in [2, 2000], hitting max at large size
    if size <= 3:
        n = 2
    elif size <= 10:
        n = random.randint(3, 8)
    elif size <= 40:
        n = random.randint(10, 40)
    elif size <= 150:
        n = random.randint(50, min(150, 2000))
    elif size <= 400:
        n = random.randint(200, min(400, 2000))
    else:
        n = 2000  # MAX-SCALE

    # Vary value distributions by seed so outputs differ
    mode = seed % 6
    a = []
    if mode == 0:
        # uniform full range
        a = [random.randint(0, 10**9) for _ in range(n)]
    elif mode == 1:
        # small values
        a = [random.randint(0, 1023) for _ in range(n)]
    elif mode == 2:
        # powers of two + noise
        a = [(1 << random.randint(0, 29)) ^ random.randint(0, 7) for _ in range(n)]
    elif mode == 3:
        # many duplicates
        pool = [random.randint(0, 10**9) for _ in range(max(1, n // 5))]
        a = [random.choice(pool) for _ in range(n)]
    elif mode == 4:
        # all equal / near-equal
        v = random.randint(0, 10**9)
        a = [v if random.random() < 0.8 else v ^ random.randint(0, 3) for _ in range(n)]
    else:
        # sorted ascending / descending mix
        a = sorted(random.randint(0, 10**9) for _ in range(n))
        if seed % 2:
            a.reverse()

    print(n)
    print(" ".join(map(str, a)))


if __name__ == "__main__":
    main()
