#!/usr/bin/env python3
import random
import string
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Brute is O(n^4); keep n small for cross-check sizes. Max |s|=1500 at large size.
    if size <= 12:
        n = random.randint(1, max(1, min(8, size + 2)))
    elif size <= 60:
        n = random.randint(4, 12)
    elif size <= 150:
        n = random.randint(8, 16)
    elif size <= 400:
        n = random.randint(12, 20)
    elif size < 2000:
        n = random.randint(50, 200)
    else:
        n = 1500

    alphabet = string.ascii_lowercase
    if random.random() < 0.2:
        alphabet = "ab"
    elif random.random() < 0.15:
        alphabet = "a"

    s = "".join(random.choice(alphabet) for _ in range(n))
    k = random.randint(0, n - 1)
    print(s)
    print(k)


if __name__ == "__main__":
    main()
