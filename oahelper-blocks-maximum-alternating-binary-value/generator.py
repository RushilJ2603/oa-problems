#!/usr/bin/env python3
"""Random valid input generator. CLI: python3 generator.py <seed> <size>"""
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2]) if len(sys.argv) > 2 else 10
    random.seed(seed)

    if size <= 5:
        n = random.randint(1, 2)
        lo, hi = 1, 5
    elif size <= 15:
        n = random.randint(2, 6)
        lo, hi = 1, 20
    elif size <= 40:
        n = random.randint(5, min(25, size))
        lo, hi = 1, 100
    elif size <= 120:
        n = random.randint(20, min(80, size))
        lo, hi = 1, 1000
    elif size <= 400:
        n = random.randint(100, min(500, max(100, size)))
        lo, hi = 1, 10000
    elif size <= 2000:
        n = min(5000, max(1000, size * 2))
        lo, hi = 1, 100000
    else:
        # Max-scale: hit constraint bounds for TLE / overflow discrimination
        n = 100000
        lo, hi = 1, 1000000

    # Mix patterns so mutation tests see sorted / reverse / random shapes
    mode = seed % 5
    A = [random.randint(lo, hi) for _ in range(n)]
    B = [random.randint(lo, hi) for _ in range(n)]
    if mode == 1:
        A.sort(reverse=True)
        B.sort()
    elif mode == 2:
        A.sort()
        B.sort(reverse=True)
    elif mode == 3:
        A = [hi] * n
        B = [lo] * n
    elif mode == 4 and n >= 2:
        A[0] = hi
        B[-1] = hi

    out = [str(n)]
    out.extend(str(x) for x in A)
    out.extend(str(x) for x in B)
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
