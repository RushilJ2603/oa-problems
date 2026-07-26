import sys

def solve(n, arr):
    # WRITE YOUR CODE HERE
    return []

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    arr = [[int(next(it)) for _ in range(n)] for _ in range(n)]
    ans = solve(n, arr)
    print(*ans)

if __name__ == "__main__":
    main()
