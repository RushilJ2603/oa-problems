import sys


def solve(n, x, y, r, xs, ys, xt, yt):
    # WRITE YOUR CODE HERE
    return "NO"


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    x, y, r = [], [], []
    for _ in range(n):
        x.append(float(next(it)))
        y.append(float(next(it)))
        r.append(float(next(it)))
    xs = float(next(it))
    ys = float(next(it))
    xt = float(next(it))
    yt = float(next(it))
    print(solve(n, x, y, r, xs, ys, xt, yt))


if __name__ == "__main__":
    main()
