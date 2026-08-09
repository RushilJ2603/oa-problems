import sys


def min_magical_terms(n: int) -> int:
    # WRITE YOUR CODE HERE
    return -1


def main() -> None:
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    out = []
    for i in range(1, t + 1):
        out.append(str(min_magical_terms(int(data[i]))))
    print("\n".join(out))


if __name__ == "__main__":
    main()
