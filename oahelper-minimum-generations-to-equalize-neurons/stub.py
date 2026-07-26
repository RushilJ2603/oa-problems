import sys


def solve(n: int, layer: list[int]) -> int:
    # WRITE YOUR CODE HERE
    return 0


def main() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    layer = [int(x) for x in data[1 : n + 1]]
    print(solve(n, layer))


if __name__ == "__main__":
    main()
