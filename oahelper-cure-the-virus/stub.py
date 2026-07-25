import sys


def solve(n, impact, precells):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    idx = 0
    n = int(data[idx]); idx += 1
    impact = [0] * n
    precells = [[] for _ in range(n)]
    for i in range(n):
        impact[i] = int(data[idx]); idx += 1
        k = int(data[idx]); idx += 1
        precells[i] = [int(data[idx + j]) - 1 for j in range(k)]
        idx += k
    print(solve(n, impact, precells))


if __name__ == "__main__":
    main()
