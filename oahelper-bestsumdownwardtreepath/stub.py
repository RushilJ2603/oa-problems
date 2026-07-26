import sys


def solve(n, parent, values):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    n = data[0]
    parent = data[1 : 1 + n]
    values = data[1 + n : 1 + 2 * n]
    print(solve(n, parent, values))


if __name__ == "__main__":
    main()
