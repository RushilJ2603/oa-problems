import sys


def solve(n: int, m: int, grid: list[list[int]]) -> int:
    # WRITE YOUR CODE HERE
    return 0


def main() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    m = int(next(it))
    grid = [[int(next(it)) for _ in range(m)] for _ in range(n)]
    print(solve(n, m, grid))


if __name__ == "__main__":
    main()
