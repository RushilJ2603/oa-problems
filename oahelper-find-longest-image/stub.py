def solve(k, colors):
    # WRITE YOUR CODE HERE
    return 0


def main():
    import sys
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    k = int(next(it))
    n = int(next(it))
    m = int(next(it))
    colors = [[int(next(it)) for _ in range(m)] for _ in range(n)]
    print(solve(k, colors))


if __name__ == "__main__":
    main()
