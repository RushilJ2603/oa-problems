import sys
from typing import List


def max_balanced_value(n: int, k: int, a: List[int], b: List[int]) -> int:
    # WRITE YOUR CODE HERE
    return 0


def main() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    k = int(data[1])
    a = [int(x) for x in data[2:2 + n]]
    b = [int(x) for x in data[2 + n:2 + 2 * n]]
    print(max_balanced_value(n, k, a, b))


if __name__ == "__main__":
    main()
