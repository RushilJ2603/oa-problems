import sys

def solve(n, m, k, X, Y, Z):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it)); m = int(next(it)); k = int(next(it))
    X = [int(next(it)) for _ in range(n)]
    Y = [int(next(it)) for _ in range(m)]
    Z = [int(next(it)) for _ in range(k)]
    print(solve(n, m, k, X, Y, Z))

if __name__ == "__main__":
    main()
