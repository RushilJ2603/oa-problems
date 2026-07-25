import sys


def solve(n, arr):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    n = int(data[0])
    arr = [int(x) for x in data[1:1 + n]]
    print(solve(n, arr))


if __name__ == "__main__":
    main()
