#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size -> n; large size hits constraint bound 1e5
    if size <= 3:
        n = random.randint(1, 5)
    elif size <= 10:
        n = random.randint(5, 30)
    elif size <= 40:
        n = random.randint(30, 200)
    elif size <= 150:
        n = random.randint(500, 5000)
    else:
        n = 10**5  # max-scale

    mode = seed % 7
    if mode == 0:
        # all zeros / all ones
        ch = '0' if seed % 2 == 0 else '1'
        s = ch * n
        k = random.randint(0, n)
    elif mode == 1:
        # alternating
        s = ''.join('01'[i % 2] for i in range(n))
        k = random.randint(0, min(n, max(1, n // 3)))
    elif mode == 2:
        # long runs
        parts = []
        rem = n
        while rem > 0:
            run = min(rem, random.randint(1, max(1, n // 5)))
            parts.append(('0' if len(parts) % 2 == 0 else '1') * run)
            rem -= run
        s = ''.join(parts)
        k = random.randint(0, min(n, 20 + n // 10))
    elif mode == 3:
        # mostly ones with sparse zeros
        s = ['1'] * n
        for i in random.sample(range(n), min(n, max(1, n // 20))):
            s[i] = '0'
        s = ''.join(s)
        k = random.randint(0, min(n, n // 15 + 5))
    elif mode == 4:
        # k = 0
        s = ''.join(random.choice('01') for _ in range(n))
        k = 0
    elif mode == 5:
        # k = n
        s = ''.join(random.choice('01') for _ in range(n))
        k = n
    else:
        s = ''.join(random.choice('01') for _ in range(n))
        k = random.randint(0, n)

    print(n)
    print(s)
    print(k)


if __name__ == "__main__":
    main()
