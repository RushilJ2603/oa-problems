import sys

def solve(N, M, L, R, C):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = list(map(int, sys.stdin.read().split()))
    if len(data) < 2:
        return
    N, M = data[0], data[1]
    L = data[2:2 + M]
    R = data[2 + M:2 + 2 * M]
    C = data[2 + 2 * M:2 + 3 * M]
    print(solve(N, M, L, R, C))

if __name__ == "__main__":
    main()
