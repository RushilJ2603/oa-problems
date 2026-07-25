import sys


def solve(n, r, meetings):
    # WRITE YOUR CODE HERE
    return 0


def main():
    raw = sys.stdin.read().replace("\\n", "\n")
    data = raw.split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    r = int(next(it))
    meetings = []
    for _ in range(n):
        s = int(next(it))
        e = int(next(it))
        p = int(next(it))
        meetings.append((s, e, p))
    print(solve(n, r, meetings))


if __name__ == "__main__":
    main()
