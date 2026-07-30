#!/usr/bin/env python3
# Independent, deliberately naive check: recompute each window's spread from scratch with Python's
# built-in max()/min() over the slice (no running accumulation like the reference), collect all
# window scores, sort, and add the k largest. O(n^3) — only ever run on small gate inputs.
import sys


def solve(n, k, a):
    scores = []
    for i in range(n):
        for j in range(i, n):
            seg = a[i:j + 1]
            scores.append(max(seg) - min(seg))
    scores.sort(reverse=True)
    return sum(scores[:k])


def main():
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    k = int(data[1])
    a = [int(x) for x in data[2:2 + n]]
    print(solve(n, k, a))


main()
