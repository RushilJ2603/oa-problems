import sys


def solve(Xp, Yp, trees, building):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    p = 0

    def nxt():
        nonlocal p
        v = data[p]
        p += 1
        return v

    Xp = int(nxt()); Yp = int(nxt()); N = int(nxt())
    trees = [(int(nxt()), int(nxt())) for _ in range(N)]
    K = int(nxt())
    building = [(int(nxt()), int(nxt())) for _ in range(K)]
    print(solve(Xp, Yp, trees, building))


if __name__ == "__main__":
    main()
