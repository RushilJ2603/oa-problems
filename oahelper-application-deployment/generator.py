#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size hint to n; large size must hit max constraint.
    if size <= 3:
        n = random.randint(1, 5)
    elif size <= 10:
        n = random.randint(6, 20)
    elif size <= 40:
        n = random.randint(21, 80)
    elif size <= 150:
        n = random.randint(100, 500)
    elif size <= 400:
        n = random.randint(1000, 5000)
    else:
        n = 100000

    max_k = (n + 1) // 2
    k = random.randint(1, max_k)

    # Vary value patterns by seed
    mode = seed % 6
    vals = []
    if mode == 0:
        vals = [random.randint(1, 10**9) for _ in range(n)]
    elif mode == 1:
        vals = sorted([random.randint(1, 10**9) for _ in range(n)])
    elif mode == 2:
        vals = sorted([random.randint(1, 10**9) for _ in range(n)], reverse=True)
    elif mode == 3:
        base = random.randint(1, 10**9)
        vals = [base] * n
    elif mode == 4:
        vals = [random.randint(1, 100) if i % 2 == 0 else random.randint(10**8, 10**9)
                for i in range(n)]
    else:
        vals = [random.randint(1, 10**6) for _ in range(n)]
        if n >= 2:
            vals[0] = 10**9
            vals[-1] = 1

    print(n)
    for x in vals:
        print(x)
    print(k)

if __name__ == "__main__":
    main()
