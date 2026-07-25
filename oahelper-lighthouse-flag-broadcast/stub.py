#!/usr/bin/env python3
import sys


def solve(n, s, k, f):
    # WRITE YOUR CODE HERE
    return ""


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    s = data[1]
    k = int(data[2])
    f = int(data[3])
    sys.stdout.write(solve(n, s, k, f) + "\n")


if __name__ == "__main__":
    main()
