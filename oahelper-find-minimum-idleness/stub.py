import sys


def solve(shader: str, switch_count: int) -> int:
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.read().split()
    if len(data) < 2:
        return
    shader = data[0]
    switch_count = int(data[1])
    print(solve(shader, switch_count))


if __name__ == "__main__":
    main()
