import sys

def solve(N, A, B):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = list(map(int, sys.stdin.read().split()))
    if len(data) < 2:
        return
    N, M = data[0], data[1]
    A = data[2:2 + M]
    B = data[2 + M:2 + 2 * M]
    print(solve(N, A, B))

if __name__ == "__main__":
    main()
