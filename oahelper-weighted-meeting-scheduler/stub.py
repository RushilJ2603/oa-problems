import sys


def solve(n, meetings):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = list(map(int, sys.stdin.read().split()))
    if not data:
        return
    n = data[0]
    meetings = []
    idx = 1
    for _ in range(n):
        s, e, p = data[idx], data[idx + 1], data[idx + 2]
        meetings.append((s, e, p))
        idx += 3
    print(solve(n, meetings))


if __name__ == "__main__":
    main()
