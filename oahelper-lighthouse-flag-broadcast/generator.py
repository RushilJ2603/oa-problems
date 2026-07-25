#!/usr/bin/env python3
import random
import sys


def max_k_sum(s, k):
    vals = sorted(ord(c) - 96 for c in s)
    vals.reverse()
    return sum(vals[:k])


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 400:
        n = 100000
        k = random.randint(1, n)
        # mix of letters; bias toward variety
        pool = "abcdefghijklmnopqrstuvwxyz"
        s = "".join(random.choice(pool) for _ in range(n))
        if random.randint(0, 3) == 0:
            s = "z" * n
        elif random.randint(0, 3) == 0:
            s = "a" * n
    elif size <= 25:
        n = random.randint(1, max(1, size))
        k = random.randint(1, min(n, max(1, size // 3 + 1)))
    elif size <= 120:
        n = random.randint(3, min(18, size))
        k = random.randint(1, min(n, 10))
    else:
        n = random.randint(50, min(500, size * 2))
        k = random.randint(1, min(n, 50))

    if size < 400:
        mode = random.randint(0, 7)
        if mode == 0:
            ch = random.choice("abcdefghijklmnopqrstuvwxyz")
            s = ch * n
        elif mode == 1:
            s = "".join(chr(ord("a") + i % 26) for i in range(n))
        elif mode == 2:
            s = "".join(chr(ord("z") - i % 26) for i in range(n))
        else:
            s = "".join(random.choice("abcdefghijklmnopqrstuvwxyz") for _ in range(n))

    hi = max_k_sum(s, k)
    f = random.randint(0, hi)

    print(n)
    print(s)
    print(k)
    print(f)


if __name__ == "__main__":
    main()
