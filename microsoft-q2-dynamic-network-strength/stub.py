import sys


def solve(n, edges):
    # edges is a list of (u, v). Return the strength after each edge, in order.
    # WRITE YOUR CODE HERE
    return []


def main():
    data = sys.stdin.buffer.read().split()
    idx = 0
    n = int(data[idx]); m = int(data[idx + 1]); idx += 2
    edges = []
    for _ in range(m):
        u = int(data[idx]); v = int(data[idx + 1]); idx += 2
        edges.append((u, v))
    print(' '.join(map(str, solve(n, edges))))


main()
