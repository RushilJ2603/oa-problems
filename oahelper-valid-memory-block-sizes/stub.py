import sys


def solve(memoryBlocks):
    # WRITE YOUR CODE HERE
    return []


def main():
    data = list(map(int, sys.stdin.read().split()))
    if not data:
        return
    n = data[0]
    blocks = data[1:1 + n]
    result = solve(blocks)
    print(*result)


if __name__ == "__main__":
    main()
