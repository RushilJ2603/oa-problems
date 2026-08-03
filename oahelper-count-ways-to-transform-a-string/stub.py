import sys

def solve(s: str, t: str, k: int) -> int:
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.read().split()
    if len(data) < 3:
        return
    s, t, k = data[0], data[1], int(data[2])
    print(solve(s, t, k))


if __name__ == "__main__":
    main()
