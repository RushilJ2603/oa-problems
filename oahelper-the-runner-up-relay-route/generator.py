#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size <= 3:
        n = 3
    elif size <= 10:
        n = random.randint(3, 8)
    elif size <= 40:
        n = random.randint(10, 30)
    elif size <= 150:
        n = random.randint(50, 120)
    elif size <= 400:
        n = random.randint(200, 800)
    elif size <= 1000:
        n = random.randint(2000, 8000)
    else:
        # max-scale at large size
        n = 100000

    # Keep m manageable for mid sizes; hit constraint bound at max
    if n >= 100000:
        m = min(200000, n - 1 + 50000)
    elif n >= 500:
        m = n - 1 + random.randint(0, min(n, 2000))
    else:
        m = n - 1 + random.randint(0, max(0, min(n, 40)))

    print(n)
    print(m)
    # spanning tree so connected
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        w = random.randint(2, 1000000000 if n >= 1000 else 1000)
        # vary weight range with seed
        if seed % 5 == 0:
            w = random.randint(2, 10)
        print(p, i, w)
    for _ in range(m - (n - 1)):
        u = random.randint(1, n)
        v = random.randint(1, n)
        while v == u:
            v = random.randint(1, n)
        w = random.randint(2, 1000000000 if n >= 1000 else 1000)
        print(u, v, w)


if __name__ == "__main__":
    main()
