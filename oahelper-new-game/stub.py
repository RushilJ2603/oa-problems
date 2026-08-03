import sys


def solve(n, m, t, k, B):
    # WRITE YOUR CODE HERE
    return -1


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    T = int(next(it))
    out = []
    for _ in range(T):
        n = int(next(it))
        m = int(next(it))
        t = int(next(it))
        k = int(next(it))
        B = []
        for _ in range(n):
            B.append((int(next(it)), int(next(it))))
        out.append(str(solve(n, m, t, k, B)))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
