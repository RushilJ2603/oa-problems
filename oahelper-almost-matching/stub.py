#!/usr/bin/env python3


def solve(s: str, k: int) -> int:
    # WRITE YOUR CODE HERE
    return 0


def main():
    import sys

    data = sys.stdin.read().split()
    if not data:
        return
    s = data[0]
    k = int(data[1])
    print(solve(s, k))


if __name__ == "__main__":
    main()
