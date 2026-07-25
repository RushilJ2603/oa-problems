#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Gate brute-checks sizes up to ~120; emit true max-scale only for large size.
    if size >= 150:
        n = 100000
    elif size >= 40:
        n = min(200, max(30, size))
    else:
        n = max(1, min(40, size))

    mode = seed % 7
    if mode == 0:
        arr = [-1] * n
    elif mode == 1:
        arr = [random.randint(1, 10**9) for _ in range(n)]
    elif mode == 2:
        arr = [random.randint(-10**9, -1) for _ in range(n)]
    elif mode == 3:
        arr = [((-1) ** i) * random.randint(1, 10**6) for i in range(n)]
    elif mode == 4:
        arr = sorted(random.randint(-10**9, 10**9) for _ in range(n))
    elif mode == 5:
        arr = sorted((random.randint(-10**9, 10**9) for _ in range(n)), reverse=True)
    else:
        arr = [random.randint(-10**9, 10**9) for _ in range(n)]

    print(n)
    print(" ".join(map(str, arr)))


if __name__ == "__main__":
    main()
