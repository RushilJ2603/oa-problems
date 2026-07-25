#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 400:
        # Max-scale: one test, N at upper bound (sum N <= 2e5)
        t = 1
        n = 100000
        cases = [(n,)]
    elif size >= 150:
        t = random.randint(1, 3)
        cases = []
        remaining = min(200000, size * 500)
        for _ in range(t):
            cap = max(1, remaining // (t - len(cases)) if cases else remaining)
            nn = random.randint(max(1, cap // 2), cap)
            nn = min(nn, 50000)
            cases.append((nn,))
            remaining -= nn
    else:
        # Small/medium: keep N tiny for brute cross-check (N <= 8)
        n = min(8, max(1, size // 15))
        if size <= 5:
            n = random.randint(1, 3)
        t = random.randint(1, min(5, max(1, size // 10)))
        cases = [(n,) for _ in range(t)]

    print(t)
    for (n,) in cases:
        print(n)
        mode = random.randint(0, 7)
        if size >= 400:
            # Large values near 1e9
            a = [random.randint(1, 10**9) for _ in range(n)]
            b = [random.randint(1, ai) for ai in a]
            c = [random.randint(1, 10**9) for _ in range(n)]
        elif mode == 0:
            # All equal floors
            v = random.randint(1, 50)
            a = [v] * n
            b = [v] * n
            c = [random.randint(1, 20) for _ in range(n)]
        elif mode == 1:
            # One heavy donor
            a = [random.randint(1, 100) for _ in range(n)]
            j = random.randrange(n)
            a[j] = random.randint(500, 5000)
            b = [random.randint(1, min(x, 50)) for x in a]
            for i in range(n):
                if b[i] > a[i]:
                    b[i] = a[i]
            c = [random.randint(1, 100) for _ in range(n)]
        elif mode == 2:
            # Sorted increasing costs
            a = [random.randint(10, 200) for _ in range(n)]
            b = [random.randint(1, min(x - 1, 50)) if x > 1 else 1 for x in a]
            c = list(range(1, n + 1))
            random.shuffle(a)
            random.shuffle(b)
        else:
            a = [random.randint(1, 500) for _ in range(n)]
            b = [random.randint(1, ai) for ai in a]
            c = [random.randint(1, 500) for _ in range(n)]

        print(" ".join(map(str, a)))
        print(" ".join(map(str, b)))
        print(" ".join(map(str, c)))


if __name__ == "__main__":
    main()
