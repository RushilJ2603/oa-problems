import sys


def calibration_value(s: str) -> int:
    # WRITE YOUR CODE HERE
    return 0


def main() -> None:
    data = sys.stdin.buffer.read().decode().split()
    n = int(data[0])
    total = 0
    for q in data[1:1 + n]:
        total += calibration_value(q)
    print(total)


main()
