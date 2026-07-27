import sys


def solve_one(s):
    # Return a permutation of s that maximizes the final reverse-and-append string.
    # WRITE YOUR CODE HERE
    return s


def main():
    data = sys.stdin.read().split()
    T = int(data[0])
    print('\n'.join(solve_one(data[i]) for i in range(1, T + 1)))


main()
