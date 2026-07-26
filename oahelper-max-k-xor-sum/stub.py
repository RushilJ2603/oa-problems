import sys

def solve(n, k, x, a):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    k = int(data[1])
    x = int(data[2])
    a = [int(data[3 + i]) for i in range(n)]
    print(solve(n, k, x, a))

if __name__ == "__main__":
    main()
