import sys


def solve(n, m, edges, a, b):
    # WRITE YOUR CODE HERE
    return False


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    m = int(next(it))
    edges = []
    for _ in range(m):
        u = int(next(it))
        v = int(next(it))
        edges.append((u, v))
    a = int(next(it))
    b = int(next(it))
    print("true" if solve(n, m, edges, a, b) else "false")


if __name__ == "__main__":
    main()
