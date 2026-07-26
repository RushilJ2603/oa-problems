import sys

def solve(m, n, e, grid):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    m = int(next(it)); n = int(next(it)); e = int(next(it))
    grid = [[int(next(it)) for _ in range(n)] for _ in range(m)]
    print(solve(m, n, e, grid))

if __name__ == "__main__":
    main()
