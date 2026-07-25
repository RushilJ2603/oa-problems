#!/usr/bin/env python3
import sys

MOD = 10**9 + 7


def solve(n, a, b, c):
    # WRITE YOUR CODE HERE
    return 0, 0


def main():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    pos = 0
    t = int(data[pos])
    pos += 1
    for _ in range(t):
        n = int(data[pos])
        pos += 1
        a = [int(data[pos + i]) for i in range(n)]
        pos += n
        b = [int(data[pos + i]) for i in range(n)]
        pos += n
        c = [int(data[pos + i]) for i in range(n)]
        pos += n
        m, cost = solve(n, a, b, c)
        print(m, cost)


if __name__ == "__main__":
    main()
