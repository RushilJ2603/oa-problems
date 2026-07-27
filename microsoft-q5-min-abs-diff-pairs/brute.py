#!/usr/bin/env python3
# Independent O(k^2) cross-check: consider ALL pairs of distinct values (not just
# adjacent ones), track the global minimum difference and collect every pair hitting it.
import sys


def main():
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    a = list(map(int, data[1:1 + n]))
    vals = sorted(set(a))
    if len(vals) < 2:
        return
    best = None
    pairs = []
    for i in range(len(vals)):
        for j in range(i + 1, len(vals)):
            d = vals[j] - vals[i]
            if best is None or d < best:
                best = d
                pairs = [(vals[i], vals[j])]
            elif d == best:
                pairs.append((vals[i], vals[j]))
    pairs.sort()
    sys.stdout.write(''.join(f'{x} {y}\n' for x, y in pairs))


main()
