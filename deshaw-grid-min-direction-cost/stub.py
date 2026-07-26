import sys


def min_cost(m, n, grid):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    m, n = int(data[0]), int(data[1])
    grid = data[2:2 + m]
    print(min_cost(m, n, grid))


if __name__ == "__main__":
    main()
