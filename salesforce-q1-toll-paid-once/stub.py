import sys
from typing import List, Tuple


def min_total_toll(n: int, adj: List[List[Tuple[int, int]]], a: int, b: int, c: int) -> int:
    """adj[u] holds (neighbour, toll) pairs. Junctions are numbered 1..n."""
    # WRITE YOUR CODE HERE
    return -1


def main() -> None:
    data = sys.stdin.buffer.read().split()
    p = 0
    n = int(data[p]); p += 1
    m = int(data[p]); p += 1
    adj: List[List[Tuple[int, int]]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        u = int(data[p]); p += 1
        v = int(data[p]); p += 1
        w = int(data[p]); p += 1
        adj[u].append((v, w))
        adj[v].append((u, w))
    a = int(data[p]); p += 1
    b = int(data[p]); p += 1
    c = int(data[p]); p += 1

    print(min_total_toll(n, adj, a, b, c))


if __name__ == "__main__":
    main()
