#!/usr/bin/env python3
# Independent implementation: recover the fixed position-permutation pi by literally
# simulating "reverse then append" on a list of index LABELS (O(n^2), vs the reference's
# O(n) deque trick), then place the descending-sorted target at those positions.
import sys


def solve_one(s):
    n = len(s)
    ones = s.count('1')
    lab = []
    for i in range(n):
        lab.reverse()
        lab.append(i)          # lab[j] = original index landing at output position j
    target = ['1'] * ones + ['0'] * (n - ones)
    p = ['0'] * n
    for j in range(n):
        p[lab[j]] = target[j]
    return ''.join(p)


def main():
    data = sys.stdin.read().split()
    T = int(data[0])
    print('\n'.join(solve_one(data[i]) for i in range(1, T + 1)))


main()
