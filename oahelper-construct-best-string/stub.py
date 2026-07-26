import sys

def solve(n, list_str, points, limit):
    # WRITE YOUR CODE HERE
    return 0

def main():
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    it = iter(tokens)
    n = int(next(it))
    strings = [next(it) for _ in range(n)]
    points = [int(next(it)) for _ in range(n)]
    limit = int(next(it))
    print(solve(n, strings, points, limit))

if __name__ == "__main__":
    main()
