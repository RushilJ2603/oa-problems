import sys


def solve(n, k, edges):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    it = iter(data)
    n = next(it)
    k = next(it)
    edges = []
    for _ in range(n - 1):
        u = next(it)
        v = next(it)
        edges.append((u, v))
    print(solve(n, k, edges))


if __name__ == "__main__":
    main()
