import sys


def solve(M, N, grid, startR, startC, Z, safe_cells):
    # WRITE YOUR CODE HERE
    return "0"


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    it = iter(data)
    M, N = next(it), next(it)
    grid = [[next(it) for _ in range(N)] for _ in range(M)]
    sr, sc, Z = next(it), next(it), next(it)
    S = next(it)
    safe = {(next(it), next(it)) for _ in range(S)}
    print(solve(M, N, grid, sr, sc, Z, safe))


if __name__ == "__main__":
    main()
