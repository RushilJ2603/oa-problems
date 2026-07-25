import sys

def solve(r, b):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.read().split()
    if len(data) < 2:
        return
    r, b = int(data[0]), int(data[1])
    print(solve(r, b))

if __name__ == "__main__":
    main()
