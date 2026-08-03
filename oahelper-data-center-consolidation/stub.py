import sys


def solve(n, k, cost):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    n, k = data[0], data[1]
    cost = []
    idx = 2
    for _ in range(n):
        cost.append(data[idx : idx + n])
        idx += n
    print(solve(n, k, cost))


if __name__ == "__main__":
    main()
