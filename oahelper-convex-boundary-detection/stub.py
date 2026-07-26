import sys
from typing import List, Tuple


def solve(n: int, points: List[Tuple[int, int]]) -> List[Tuple[int, int]]:
    # WRITE YOUR CODE HERE
    return []


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    n = data[0]
    points = []
    idx = 1
    for _ in range(n):
        if idx + 1 < len(data):
            points.append((data[idx], data[idx + 1]))
        idx += 2
    ans = solve(n, points)
    sys.stdout.write("\n".join(f"{x} {y}" for x, y in ans))


if __name__ == "__main__":
    main()
