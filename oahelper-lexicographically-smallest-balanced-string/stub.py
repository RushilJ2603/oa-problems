import sys

def solve(n: int, k: int, s: str) -> str:
    # WRITE YOUR CODE HERE
    return "-1"

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0]); k = int(data[1]); s = data[2]
    print(solve(n, k, s))

if __name__ == "__main__":
    main()
