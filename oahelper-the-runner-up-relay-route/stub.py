import sys


def solve(n, edges):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    n, m = data[0], data[1]
    edges = []
    idx = 2
    for _ in range(m):
        edges.append((data[idx], data[idx + 1], data[idx + 2]))
        idx += 3
    print(solve(n, edges))


if __name__ == "__main__":
    main()
