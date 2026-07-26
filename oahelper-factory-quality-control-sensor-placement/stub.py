import sys


def solve(N, K, A):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    N = int(data[0])
    K = int(data[1])
    A = list(map(int, data[2:2 + N]))
    print(solve(N, K, A))


if __name__ == "__main__":
    main()
