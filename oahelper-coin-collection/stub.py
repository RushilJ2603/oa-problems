import sys

def solve(n, coins):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    coins = [[0] * n for _ in range(2)]
    idx = 1
    for i in range(n):
        coins[0][i] = int(data[idx]); idx += 1
    for i in range(n):
        coins[1][i] = int(data[idx]); idx += 1
    print(solve(n, coins))

if __name__ == "__main__":
    main()
