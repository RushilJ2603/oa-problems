#!/usr/bin/env python3
"""Deterministic generator: python3 generator.py <seed> <size>"""
import random
import sys


def rand_range(rng, M):
    l = rng.randint(1, M)
    r = rng.randint(l, M)
    return l, r


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    rng = random.Random(seed)

    # Brute-friendly for size <= 120 (random cross-check); max-scale at size >= 400.
    if size >= 400:
        M = 1000000
        N = 200000
    elif size <= 120:
        M = max(1, min(2000, size * 20))
        N = max(1, min(200000, size * 2))
    else:
        M = max(1, min(5000, size * 20))
        N = max(1, min(200000, size * 2))

    mode = seed % 7
    if mode == 0:
        T = 1
    elif mode == 1:
        T = 10**9
    elif mode == 2:
        T = rng.randint(1, 50)
    else:
        T = rng.randint(1, max(1, N * 20))

    events = []
    if mode == 3 and size < 400:
        # queries only — threshold stays -1
        for _ in range(N):
            l, r = rand_range(rng, M)
            events.append(f"QUERY {l} {r}")
    elif mode == 4 and size < 400:
        # books only
        for i in range(N):
            l, r = rand_range(rng, M)
            if i % 11 == 0:
                l, r = 1, M
            p = rng.randint(1, 10000)
            events.append(f"BOOK {l} {r} {p}")
    else:
        for i in range(N):
            if size >= 400:
                kind = "QUERY" if (i % 17 == 0) else "BOOK"
            else:
                kind = "BOOK" if rng.random() < 0.65 else "QUERY"
            l, r = rand_range(rng, M)
            if kind == "BOOK":
                if size >= 400 and i % 31 == 0:
                    l, r = 1, M
                p = rng.randint(1, 10000)
                events.append(f"BOOK {l} {r} {p}")
            else:
                events.append(f"QUERY {l} {r}")

    print(M, N, T)
    for e in events:
        print(e)


if __name__ == "__main__":
    main()
