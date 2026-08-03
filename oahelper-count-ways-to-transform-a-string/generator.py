#!/usr/bin/env python3
"""Deterministic generator: python3 generator.py <seed> <size>"""
import random
import string
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size -> n; large size hits the constraint bound n=1000.
    if size <= 5:
        n = random.randint(1, 4)
    elif size <= 20:
        n = random.randint(3, min(12, size))
    elif size <= 80:
        n = random.randint(10, min(40, size))
    elif size <= 200:
        n = random.randint(50, min(200, max(50, size)))
    else:
        n = 1000  # MAX-SCALE

    alphabet = string.ascii_lowercase
    mode = random.randrange(6)

    if n == 1:
        ch = random.choice(alphabet)
        s = ch
        t = ch if random.random() < 0.7 else random.choice(alphabet)
    elif mode == 0:
        # identical strings
        s = "".join(random.choice(alphabet) for _ in range(n))
        t = s
    elif mode == 1:
        # t is a random rotation of s
        s = "".join(random.choice(alphabet) for _ in range(n))
        d = random.randint(0, n - 1)
        t = s[n - d :] + s[: n - d]
    elif mode == 2:
        # periodic string (many matching shifts)
        period = random.randint(1, max(1, n // 2))
        unit = "".join(random.choice(alphabet) for _ in range(period))
        s = (unit * ((n // period) + 2))[:n]
        d = random.choice([i for i in range(n) if i % period == 0] or [0])
        t = s[n - d :] + s[: n - d]
    elif mode == 3:
        # all equal characters
        ch = random.choice(alphabet)
        s = ch * n
        t = ch * n
    elif mode == 4:
        # unrelated strings (often answer 0)
        s = "".join(random.choice(alphabet) for _ in range(n))
        t = "".join(random.choice(alphabet) for _ in range(n))
    else:
        # mostly unique with one planted matching rotation
        s = "".join(random.choice(alphabet) for _ in range(n))
        d = random.randint(1, n - 1)
        t = s[n - d :] + s[: n - d]

    if size <= 5:
        k = random.randint(1, 5)
    elif size <= 20:
        k = random.randint(1, 30)
    elif size <= 80:
        k = random.randint(1, 10**6)
    elif size <= 200:
        k = random.randint(10**5, 10**9)
    else:
        k = 10**9  # MAX-SCALE k

    sys.stdout.write(s + "\n" + t + "\n" + str(k) + "\n")


if __name__ == "__main__":
    main()
