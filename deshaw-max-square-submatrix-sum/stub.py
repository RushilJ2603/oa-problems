import sys


def max_square_side(m, n, k, grid):
    # grid is m x n with non-negative values. Return the largest L such that some L x L square
    # submatrix has sum <= k (0 if none).
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    m = int(data[0]); n = int(data[1]); k = int(data[2])
    vals = list(map(int, data[3:3 + m * n]))
    grid = [vals[i * n:(i + 1) * n] for i in range(m)]
    print(max_square_side(m, n, k, grid))


if __name__ == "__main__":
    main()
