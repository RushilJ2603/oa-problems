import sys

def solve(n, t):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = list(map(int, sys.stdin.read().split()))
    if not data:
        return
    n = data[0]
    t = data[1:1 + n]
    print(solve(n, t))

if __name__ == "__main__":
    main()
