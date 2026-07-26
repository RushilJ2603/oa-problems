import sys


def min_reversals(n, edges, s, t):
    # edges is a list of (u, v) directed edges u -> v.
    # Return the minimum number of edge reversals to get from s to t, or -1 if impossible.
    # WRITE YOUR CODE HERE
    return -1


def main():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    i = 0
    n = int(data[i]); i += 1
    m = int(data[i]); i += 1
    edges = []
    for _ in range(m):
        edges.append((int(data[i]), int(data[i + 1]))); i += 2
    s = int(data[i]); t = int(data[i + 1])
    print(min_reversals(n, edges, s, t))


if __name__ == "__main__":
    main()
