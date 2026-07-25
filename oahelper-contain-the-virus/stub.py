import sys


def solve(n, m, grid):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    m = int(data[1])
    grid = []
    idx = 2
    for _ in range(n):
        grid.append([int(x) for x in data[idx:idx + m]])
        idx += m
    print(solve(n, m, grid))


if __name__ == "__main__":
    main()
