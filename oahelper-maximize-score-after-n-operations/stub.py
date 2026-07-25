import sys


def solve(m, nums):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    m = int(next(it))
    nums = [int(next(it)) for _ in range(m)]
    print(solve(m, nums))


if __name__ == "__main__":
    main()
