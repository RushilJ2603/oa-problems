import sys


def conway_cubes(T: int, slice_rows: list) -> int:
    # WRITE YOUR CODE HERE
    return 0


def main() -> None:
    data = sys.stdin.read().split()
    R, T = int(data[0]), int(data[1])
    rows = data[2:2 + R]
    print(conway_cubes(T, rows))


main()
