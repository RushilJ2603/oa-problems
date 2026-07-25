#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size <= 12:
        n = random.randint(2, max(2, size + 2))
    elif size <= 60:
        n = random.randint(5, min(40, size))
    elif size <= 150:
        n = random.randint(20, 80)
    elif size <= 400:
        n = random.randint(40, 120)
    elif size < 2000:
        n = random.randint(500, 2000)
    else:
        n = 200000

    W = random.choice([1, 2, 5, 10, 100, 10**9, random.randint(1, 10**6)])
    K = random.randint(2, max(2, min(n, 20 if n < 1000 else n)))
    if n >= 200000:
        K = random.randint(2, 50)

    # Strictly increasing timestamps
    t = []
    cur = 0
    for i in range(n):
        cur += random.randint(1, 3 if n < 1000 else 5)
        if random.random() < 0.05:
            cur += random.randint(W, W + 10) if W < 10**8 else random.randint(1, 100)
        t.append(cur)

    # Users: mix shared IDs so thresholds can be hit
    pool = list(range(1, min(n, 30) + 1))
    if random.random() < 0.3:
        pool = [random.randint(1, 10**9) for _ in range(min(10, n))]
    u = [random.choice(pool) for _ in range(n)]

    print(n, W, K)
    for i in range(n):
        print(t[i], u[i])


if __name__ == "__main__":
    main()
