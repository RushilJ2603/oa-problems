import sys


def solve(n, m, g):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    m = int(next(it))
    g = [[int(next(it)) for _ in range(m)] for _ in range(n)]
    print(solve(n, m, g))


if __name__ == "__main__":
    main()
