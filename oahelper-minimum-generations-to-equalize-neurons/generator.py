#!/usr/bin/env python3
import random
import sys


def main() -> None:
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Large size => hit n = 1e5 max-scale
    if size >= 400:
        n = 100000
    elif size >= 150:
        n = min(100000, 1000 + size * 50)
    elif size >= 40:
        n = min(100000, max(10, size * 20))
    else:
        n = max(1, min(100, size))

    mode = seed % 7
    layer = [0] * n
    if mode == 0:
        # already equal
        v = random.randint(1, 10**9)
        layer = [v] * n
    elif mode == 1:
        # one outlier low
        mx = random.randint(2, 10**9)
        layer = [mx] * n
        layer[random.randrange(n)] = random.randint(1, mx)
    elif mode == 2:
        # one outlier high
        base = random.randint(1, 10**6)
        layer = [base] * n
        layer[random.randrange(n)] = random.randint(base, 10**9)
    elif mode == 3:
        # ascending
        start = random.randint(1, 1000)
        layer = [start + i for i in range(n)]
    elif mode == 4:
        # descending
        start = random.randint(n, n + 10**6)
        layer = [max(1, start - i) for i in range(n)]
    elif mode == 5:
        # two values alternating
        a = random.randint(1, 10**9)
        b = random.randint(1, 10**9)
        layer = [a if i % 2 == 0 else b for i in range(n)]
    else:
        lo = random.randint(1, 10**6)
        hi = random.randint(lo, min(lo + 10**6, 10**9))
        if size >= 150:
            hi = 10**9
            lo = 1
        layer = [random.randint(lo, hi) for _ in range(n)]

    print(n)
    for x in layer:
        print(x)


if __name__ == "__main__":
    main()
