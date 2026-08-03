import sys


def solve(n, quality):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    n = data[0]
    quality = data[1 : 1 + n]
    print(solve(n, quality))


if __name__ == "__main__":
    main()
