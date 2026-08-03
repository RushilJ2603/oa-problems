import sys

MOD = 998244353


def solve(n, w):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    n = int(data[0])
    w = [int(x) for x in data[1:1 + n]]
    print(solve(n, w))


if __name__ == "__main__":
    main()
