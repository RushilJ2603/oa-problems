#!/usr/bin/env python3
import random
import string
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 400:
        n = 2000
    elif size <= 120:
        n = random.randint(max(1, size // 3), min(40, max(1, size)))
    elif size <= 200:
        n = random.randint(30, 80)
    else:
        n = random.randint(80, min(400, size * 2))

    mode = random.randint(0, 7)
    if mode == 0:
        s = random.choice(string.ascii_lowercase) * n
    elif mode == 1:
        pat = random.choice(["ab", "abc", "aba", "abab"])
        s = (pat * ((n // len(pat)) + 1))[:n]
    elif mode == 2:
        s = "".join(random.choice(string.ascii_lowercase) for _ in range(n))
    elif mode == 3 and n >= 2:
        s = "a" * (n - 1) + random.choice("bcdefghijklmnopqrstuvwxyz")
    elif mode == 4:
        s = "a" * n
    elif mode == 5:
        s = "ab" * ((n + 1) // 2)
        s = s[:n]
    else:
        s = "".join(random.choice("ab") for _ in range(n))

    k = random.randint(0, n - 1)
    print(s)
    print(k)


if __name__ == "__main__":
    main()
