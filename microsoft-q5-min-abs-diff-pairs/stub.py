import sys


def solve(a):
    # Return the list of (x, y) pairs with x < y achieving the minimum absolute difference,
    # sorted ascending by x then y.
    # WRITE YOUR CODE HERE
    return []


def main():
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    a = list(map(int, data[1:1 + n]))
    sys.stdout.write(''.join(f'{x} {y}\n' for x, y in solve(a)))


main()
