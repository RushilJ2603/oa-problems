import sys

def solve(n, layer):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    layer = [int(next(it)) for _ in range(n)]
    print(solve(n, layer))

if __name__ == "__main__":
    main()
