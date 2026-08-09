import sys
from typing import List


def top_k_frequent(tags: List[str], k: int) -> List[str]:
    # WRITE YOUR CODE HERE
    return []


def main() -> None:
    data = sys.stdin.read().split()
    n = int(data[0])
    tags = data[1:1 + n]
    k = int(data[1 + n])
    print(" ".join(top_k_frequent(tags, k)))


if __name__ == "__main__":
    main()
