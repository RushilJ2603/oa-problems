"""Independent solution via the general Dreyfus-Wagner Steiner-tree DP.

reference.cpp uses the 3-terminal shortcut (answer = min over v of d(a,v)+d(b,v)+d(c,v)). This one
deliberately does NOT assume that shortcut: it runs the general minimum-Steiner-tree DP over subsets
of the terminal set, so it would disagree if the shortcut were wrong rather than merely mis-coded.

    dp[S][v] = cheapest tree spanning terminal subset S plus the vertex v
    dp[S][v] = min( split:  dp[T][v] + dp[S\\T][v]  over proper non-empty T subset S,
                    grow:   dp[S][u] + w(u,v)       over edges (u,v) )

The 'grow' step is a Dijkstra seeded with the whole dp[S] row.
"""
import heapq
import sys


def main() -> None:
    data = sys.stdin.buffer.read().split()
    p = 0
    n = int(data[p]); p += 1
    m = int(data[p]); p += 1
    adj = [[] for _ in range(n + 1)]
    for _ in range(m):
        u = int(data[p]); p += 1
        v = int(data[p]); p += 1
        w = int(data[p]); p += 1
        adj[u].append((v, w))
        adj[v].append((u, w))
    a = int(data[p]); p += 1
    b = int(data[p]); p += 1
    c = int(data[p]); p += 1

    terminals = [a, b, c]
    t = len(terminals)
    INF = float("inf")
    full = (1 << t) - 1
    dp = [[INF] * (n + 1) for _ in range(1 << t)]

    for i, term in enumerate(terminals):
        dp[1 << i][term] = 0

    for mask in range(1, full + 1):
        row = dp[mask]
        # split: merge two trees that meet at v
        sub = (mask - 1) & mask
        while sub > 0:
            other = mask ^ sub
            if sub < other:                      # each unordered split once
                left, right = dp[sub], dp[other]
                for v in range(1, n + 1):
                    if left[v] < INF and right[v] < INF:
                        s = left[v] + right[v]
                        if s < row[v]:
                            row[v] = s
            sub = (sub - 1) & mask
        # grow: Dijkstra seeded with every finite entry of this row
        pq = [(row[v], v) for v in range(1, n + 1) if row[v] < INF]
        heapq.heapify(pq)
        while pq:
            d, u = heapq.heappop(pq)
            if d > row[u]:
                continue
            for v, w in adj[u]:
                nd = d + w
                if nd < row[v]:
                    row[v] = nd
                    heapq.heappush(pq, (nd, v))

    best = min(dp[full][1:n + 1]) if n >= 1 else INF
    print(-1 if best == INF else best)


main()
