import sys

MOD = 10**9 + 7


def solve(n, k, edges):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    m = int(next(it))
    k = int(next(it))
    edges = []
    for _ in range(m):
        a = int(next(it))
        b = int(next(it))
        edges.append((a, b))
    print(solve(n, k, edges))


if __name__ == "__main__":
    main()
