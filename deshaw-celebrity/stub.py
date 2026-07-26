import sys


def celebrity(n, knows):
    # knows[i][j] == 1 iff person i knows person j. Return the celebrity index or -1.
    # WRITE YOUR CODE HERE
    return -1


def main():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    n = int(data[0])
    vals = list(map(int, data[1:1 + n * n]))
    knows = [vals[i * n:(i + 1) * n] for i in range(n)]
    print(celebrity(n, knows))


if __name__ == "__main__":
    main()
