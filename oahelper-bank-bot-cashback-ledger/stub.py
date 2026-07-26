import sys


def solve(n, bal, reqs):
    """Return final balances as a list, or [-k] on first invalid request."""
    # WRITE YOUR CODE HERE
    return []


def main():
    data = sys.stdin.read().split()
    it = iter(data)
    n = int(next(it))
    bal = [int(next(it)) for _ in range(n)]
    m = int(next(it))
    reqs = []
    for _ in range(m):
        op = next(it)
        ts = int(next(it))
        h = int(next(it))
        amt = int(next(it))
        reqs.append((op, ts, h, amt))
    ans = solve(n, bal, reqs)
    print(" ".join(map(str, ans)))


if __name__ == "__main__":
    main()
