import sys


def solve(m, n, matrix):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    m = data[0]
    n = data[1]
    vals = data[2:]
    matrix = [vals[i * n:(i + 1) * n] for i in range(m)]
    print(solve(m, n, matrix))


if __name__ == "__main__":
    main()
