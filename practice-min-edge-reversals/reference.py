import sys
from collections import deque


def main():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    idx = 0
    n = int(data[idx]); idx += 1
    m = int(data[idx]); idx += 1
    adj = [[] for _ in range(n + 1)]
    for _ in range(m):
        u = int(data[idx]); v = int(data[idx + 1]); idx += 2
        adj[u].append((v, 0))   # with the edge, free
        adj[v].append((u, 1))   # against the edge, one reversal
    s = int(data[idx]); t = int(data[idx + 1])
    INF = float("inf")
    dist = [INF] * (n + 1)
    dist[s] = 0
    dq = deque([s])
    while dq:
        u = dq.popleft()
        du = dist[u]
        for v, w in adj[u]:
            if du + w < dist[v]:
                dist[v] = du + w
                if w == 0:
                    dq.appendleft(v)
                else:
                    dq.append(v)
    print(-1 if dist[t] == INF else dist[t])


if __name__ == "__main__":
    main()
