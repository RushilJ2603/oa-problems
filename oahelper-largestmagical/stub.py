import sys

def solve(s: str) -> str:
    # WRITE YOUR CODE HERE
    return s

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    print(solve(data[0]))

if __name__ == "__main__":
    main()
