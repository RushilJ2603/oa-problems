def solve(N, T, adj):
    # WRITE YOUR CODE HERE
    # adj[u] = list of (v, p)
    # return (best_division, probability); best_division == 0 means not in any division
    return (0, 0.0)


def main():
    import sys
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    tc = 1
    while True:
        try:
            N = int(next(it))
            E = int(next(it))
            T = int(next(it))
        except StopIteration:
            break
        adj = [[] for _ in range(N + 1)]
        for _ in range(E):
            u = int(next(it))
            v = int(next(it))
            p = float(next(it))
            adj[u].append((v, p))
        best, max_p = solve(N, T, adj)
        if best == 0:
            print(f"#{tc} 0")
        else:
            print(f"#{tc} {best} {max_p:.6f}")
        tc += 1


if __name__ == "__main__":
    main()
