import sys

def solve(L, R, K):
    # WRITE YOUR CODE HERE
    return -1

def main():
    data = sys.stdin.read().split()
    if len(data) < 3:
        return
    L, R, K = int(data[0]), int(data[1]), int(data[2])
    print(solve(L, R, K))

if __name__ == "__main__":
    main()
