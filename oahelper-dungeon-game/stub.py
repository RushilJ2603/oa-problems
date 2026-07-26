import sys


def solve(m, n, dungeon):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = list(map(int, sys.stdin.read().split()))
    if not data:
        return
    m, n = data[0], data[1]
    vals = data[2:]
    dungeon = [vals[i * n : (i + 1) * n] for i in range(m)]
    print(solve(m, n, dungeon))


if __name__ == "__main__":
    main()
