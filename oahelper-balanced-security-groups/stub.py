import sys

def solve(n, security):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    security = list(map(int, data[1:n + 1]))
    print(solve(n, security))

if __name__ == "__main__":
    main()
