import sys


def solve(n, adj, q, queries):
    # WRITE YOUR CODE HERE
    return "0" * q


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    p = 0
    n = data[p]
    p += 1
    adj = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u, v = data[p], data[p + 1]
        p += 2
        adj[u].append(v)
        adj[v].append(u)
    q = data[p]
    p += 1
    queries = []
    for _ in range(q):
        queries.append(data[p : p + n])
        p += n
    print(solve(n, adj, q, queries))


if __name__ == "__main__":
    main()
