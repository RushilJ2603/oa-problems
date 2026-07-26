import sys

def solve(history):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    history = data[1:1 + n]
    print(solve(history))

if __name__ == "__main__":
    main()
