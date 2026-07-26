import sys


def solve(n, values, state, m):
    # WRITE YOUR CODE HERE
    return [0] * m


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    values = [int(next(it)) for _ in range(n)]
    state = next(it)
    m = int(next(it))
    for x in solve(n, values, state, m):
        print(x)


if __name__ == "__main__":
    main()
