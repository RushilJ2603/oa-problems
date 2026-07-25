import sys


def solve(s, k):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.read().split()
    if len(data) < 2:
        return
    print(solve(data[0], int(data[1])))


if __name__ == "__main__":
    main()
