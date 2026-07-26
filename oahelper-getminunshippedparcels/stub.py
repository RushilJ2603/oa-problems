def solve(weights, max_wt):
    # WRITE YOUR CODE HERE
    return 0


def main():
    import sys
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    n = data[0]
    weights = data[1 : 1 + n]
    max_wt = data[1 + n]
    print(solve(weights, max_wt))


if __name__ == "__main__":
    main()
