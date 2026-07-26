import sys


def solve(n, m, k, salary, earning):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    n, m, k = data[0], data[1], data[2]
    salary = data[3 : 3 + n]
    earning = data[3 + n : 3 + 2 * n]
    print(solve(n, m, k, salary, earning))


if __name__ == "__main__":
    main()
