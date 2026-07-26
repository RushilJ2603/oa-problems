import sys

MOD = 10**9 + 7


def solve(n, A, B):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    n = int(data[0])
    A = [int(x) for x in data[1:1 + n]]
    B = [int(x) for x in data[1 + n:1 + 2 * n]]
    print(solve(n, A, B))


if __name__ == "__main__":
    main()
