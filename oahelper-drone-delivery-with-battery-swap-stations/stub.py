import sys


def solve(rows, cols, grid, sr, sc, er, ec, B, stations, K):
    # WRITE YOUR CODE HERE
    return -1


def main():
    data = list(map(int, sys.stdin.read().split()))
    if not data:
        return
    p = 0
    rows, cols = data[p], data[p + 1]
    p += 2
    grid = []
    for _ in range(rows):
        grid.append(data[p:p + cols])
        p += cols
    sr, sc = data[p], data[p + 1]
    p += 2
    er, ec = data[p], data[p + 1]
    p += 2
    B = data[p]
    p += 1
    M = data[p]
    p += 1
    stations = []
    for _ in range(M):
        stations.append((data[p], data[p + 1]))
        p += 2
    K = data[p]
    print(solve(rows, cols, grid, sr, sc, er, ec, B, stations, K))


if __name__ == "__main__":
    main()
