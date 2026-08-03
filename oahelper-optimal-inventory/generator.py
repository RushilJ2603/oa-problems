#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size <= 5:
        n = random.randint(1, 5)
    elif size <= 20:
        n = random.randint(5, 15)
    elif size <= 80:
        n = random.randint(15, 40)
    elif size <= 200:
        n = random.randint(40, 100)
    else:
        n = 200000  # MAX-SCALE

    mode = random.choice(["random", "alternating", "nested", "already", "many_dup"])
    quality = []
    if mode == "already":
        # Already optimal: contiguous runs of distinct values
        i = 0
        v = 0
        while i < n:
            run = random.randint(1, max(1, n // 10))
            run = min(run, n - i)
            quality.extend([v] * run)
            i += run
            v += 1
    elif mode == "alternating":
        a, b = random.randint(-10**9, 10**9), random.randint(-10**9, 10**9)
        while a == b:
            b = random.randint(-10**9, 10**9)
        quality = [a if i % 2 == 0 else b for i in range(n)]
    elif mode == "nested":
        # Overlapping intervals that force large merged components
        k = max(2, min(n, random.randint(3, 20)))
        vals = [random.randint(-10**9, 10**9) for _ in range(k)]
        for i in range(n):
            quality.append(vals[i % k])
    elif mode == "many_dup":
        pool = [random.randint(-1000, 1000) for _ in range(max(2, n // 5))]
        quality = [random.choice(pool) for _ in range(n)]
    else:
        quality = [random.randint(-10**9, 10**9) for _ in range(n)]

    print(n)
    for x in quality:
        print(x)

if __name__ == "__main__":
    main()
