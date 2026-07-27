#!/usr/bin/env python3
# Independent cross-check: recompute the components from scratch after every edge
# via BFS over the adjacency list (no DSU, no incremental sum). O(m*(n+m)) — only
# used on small inputs, but structurally different from the reference.
import sys
from collections import deque


def main():
    data = sys.stdin.buffer.read().split()
    idx = 0
    n = int(data[idx]); m = int(data[idx + 1]); idx += 2
    adj = [[] for _ in range(n + 1)]
    res = []
    for _ in range(m):
        u = int(data[idx]); v = int(data[idx + 1]); idx += 2
        adj[u].append(v)
        adj[v].append(u)
        seen = [False] * (n + 1)
        total = 0
        for s in range(1, n + 1):
            if seen[s]:
                continue
            q = deque([s]); seen[s] = True; mx = s
            while q:
                x = q.popleft()
                if x > mx:
                    mx = x
                for y in adj[x]:
                    if not seen[y]:
                        seen[y] = True
                        q.append(y)
            total += mx
        res.append(total)
    print(' '.join(map(str, res)))


main()
