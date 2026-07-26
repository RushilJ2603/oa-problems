import sys


def solve(n: int, s: str, k: int) -> int:
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    s = data[1]
    k = int(data[2])
    print(solve(n, s, k))


if __name__ == "__main__":
    main()
