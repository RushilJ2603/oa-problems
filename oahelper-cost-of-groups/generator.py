#!/usr/bin/env python3
"""Random valid tree input. CLI: python3 generator.py <seed> <size>"""
import random
import sys


def main():
    random.seed(int(sys.argv[1]))
    size = int(sys.argv[2]) if len(sys.argv) > 2 else 10

    # Large size -> max-scale N=1e5. Smaller sizes stay brute-friendly (subset DP ~2^{n/2}).
    if size >= 400:
        t = 1
        ns = [100000]
        amax = 10**9
    elif size >= 150:
        t = random.randint(1, 2)
        ns = [random.randint(10, 14) for _ in range(t)]
        amax = 10**9
    elif size >= 40:
        t = random.randint(1, 3)
        ns = [random.randint(6, 12) for _ in range(t)]
        amax = 10**6
    elif size >= 10:
        t = random.randint(1, 3)
        ns = [random.randint(3, 10) for _ in range(t)]
        amax = 1000
    else:
        t = 1
        ns = [random.randint(1, min(8, max(1, size + 2)))]
        amax = 100

    lines = [str(len(ns))]
    for ni in ns:
        mode = random.randint(0, 4)
        if mode == 0:
            a = [random.randint(1, amax) for _ in range(ni)]
        elif mode == 1:
            v = random.randint(1, amax)
            a = [v] * ni
        elif mode == 2:
            a = list(range(1, ni + 1))
            random.shuffle(a)
        elif mode == 3:
            a = [1 if i % 2 == 0 else amax for i in range(ni)]
        else:
            a = sorted(random.randint(1, amax) for _ in range(ni))
            if random.random() < 0.5:
                a.reverse()

        shape = random.randint(0, 3)
        edges = []
        if ni == 1:
            pass
        elif shape == 0:
            for i in range(2, ni + 1):
                edges.append((i, random.randint(1, i - 1)))
        elif shape == 1:
            for i in range(1, ni):
                edges.append((i, i + 1))
        elif shape == 2:
            for i in range(2, ni + 1):
                edges.append((1, i))
        else:
            for i in range(2, ni + 1):
                edges.append((i, i // 2))

        random.shuffle(edges)
        lines.append(str(ni))
        lines.append(" ".join(map(str, a)))
        for u, v in edges:
            if random.random() < 0.5:
                u, v = v, u
            lines.append(f"{u} {v}")

    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
