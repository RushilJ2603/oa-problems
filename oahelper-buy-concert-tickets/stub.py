import sys

def solve(m: int, k: int) -> int:
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    m = int(data[0])
    k = int(data[1])
    print(solve(m, k))

if __name__ == "__main__":
    main()
