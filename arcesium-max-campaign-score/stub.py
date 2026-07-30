import sys


def solve(n, k, a):
    # Launch exactly k distinct campaigns (windows [i, j]); each scores max(a[i..j]) - min(a[i..j]).
    # Return the maximum achievable total score.
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    k = int(data[1])
    a = [int(x) for x in data[2:2 + n]]
    print(solve(n, k, a))


main()
