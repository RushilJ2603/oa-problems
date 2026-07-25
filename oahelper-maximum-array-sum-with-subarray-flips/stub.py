import sys


def solve(n: int, k: int, a: list) -> int:
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = list(map(int, sys.stdin.read().split()))
    if not data:
        return
    n, k = data[0], data[1]
    a = data[2:2 + n]
    print(solve(n, k, a))


if __name__ == "__main__":
    main()
