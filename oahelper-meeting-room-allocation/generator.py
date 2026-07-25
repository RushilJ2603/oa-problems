#!/usr/bin/env python3
"""Deterministic generator: python3 generator.py <seed> <size>"""
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    rng = random.Random(seed)

    # Map size -> N; large size hits constraint max N=1e5
    if size <= 3:
        n = rng.randint(1, 3)
    elif size <= 10:
        n = rng.randint(4, 15)
    elif size <= 40:
        n = rng.randint(20, 80)
    elif size <= 150:
        n = rng.randint(200, 800)
    else:
        n = 100000  # max-scale

    r = rng.randint(1, n)
    mode = seed % 6
    meetings = []

    if mode == 0:
        # overlapping cascade, R often small
        r = max(1, min(n, rng.randint(1, max(1, n // 10))))
        t = 1
        for i in range(n):
            s = t + rng.randint(0, 2)
            e = s + rng.randint(1, 20)
            p = rng.randint(1, 10**9)
            meetings.append((s, e, p))
            t = s
    elif mode == 1:
        # all same start time
        s0 = rng.randint(1, 10**6)
        for _ in range(n):
            e = s0 + rng.randint(1, 10**6)
            p = rng.randint(1, 10**9)
            meetings.append((s0, e, p))
    elif mode == 2:
        # equal priorities (no replacements)
        p0 = rng.randint(1, 10**9)
        for _ in range(n):
            s = rng.randint(1, 10**6)
            e = s + rng.randint(1, 10**6)
            meetings.append((s, e, p0))
    elif mode == 3:
        # R = 1 stress
        r = 1
        for i in range(n):
            s = i + 1
            e = s + rng.randint(1, 5)
            p = rng.randint(1, 10**9)
            meetings.append((s, e, p))
    elif mode == 4:
        # R = N (always accept)
        r = n
        for _ in range(n):
            s = rng.randint(1, 10**9 - 1)
            e = rng.randint(s + 1, 10**9)
            p = rng.randint(1, 10**9)
            meetings.append((s, e, p))
    else:
        # large values / random
        for _ in range(n):
            s = rng.randint(1, 10**9 - 1)
            e = rng.randint(s + 1, 10**9)
            p = rng.randint(1, 10**9)
            meetings.append((s, e, p))

    print(n)
    print(r)
    for s, e, p in meetings:
        print(s, e, p)


if __name__ == "__main__":
    main()
