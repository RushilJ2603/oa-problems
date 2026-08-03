import sys


def solve(x, boost, prereq):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.read().split()
    p = 0
    x = int(data[p]); p += 1
    boost = [0] * (x + 1)
    prereq = [[] for _ in range(x + 1)]
    for i in range(1, x + 1):
        boost[i] = int(data[p]); p += 1
        m = int(data[p]); p += 1
        prereq[i] = [int(data[p + j]) for j in range(m)]
        p += m
    print(solve(x, boost, prereq))


if __name__ == "__main__":
    main()
