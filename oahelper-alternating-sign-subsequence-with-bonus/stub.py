import sys


def solve(n, b, a):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    b = int(data[1])
    a = [int(data[i + 2]) for i in range(n)]
    print(solve(n, b, a))


if __name__ == "__main__":
    main()
