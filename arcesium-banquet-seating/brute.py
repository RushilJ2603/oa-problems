#!/usr/bin/env python3
# Independent brute force by a completely different method than the reference formula: exhaustively
# try EVERY circular arrangement of the guests. For a given cyclic order, the empty chairs needed
# between two adjacent guests is the larger of their demands; sum that over the ring and take the
# minimum over all orders. Feasible iff that minimum + n (occupied chairs) <= m. Only ever run on the
# small inputs the gate generates (n <= 8), where n! is tiny.
import sys
import itertools


def solve(m, d):
    n = len(d)
    if n == 0:
        return True
    if n == 1:
        return d[0] <= m - 1            # sole guest: the one wrap-around gap must hold demand[0]
    best = None
    first, rest = d[0], d[1:]           # fix one guest to factor out rotations
    for perm in itertools.permutations(rest):
        arr = [first] + list(perm)
        gaps = 0
        for t in range(n):
            a, b = arr[t], arr[(t + 1) % n]
            gaps += a if a > b else b
        if best is None or gaps < best:
            best = gaps
    return best <= m - n


def main():
    data = sys.stdin.buffer.read().split()
    m = int(data[0])
    n = int(data[1])
    d = [int(x) for x in data[2:2 + n]]
    print("YES" if solve(m, d) else "NO")


main()
