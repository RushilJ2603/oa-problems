import sys


def solve(m, d):
    # m chairs in a circle, guests with demands d. Each guest needs at least demand[i] empty chairs on
    # both sides before the next guest. Return True iff everyone can be seated.
    # WRITE YOUR CODE HERE
    return False


def main():
    data = sys.stdin.buffer.read().split()
    m = int(data[0])
    n = int(data[1])
    d = [int(x) for x in data[2:2 + n]]
    print("YES" if solve(m, d) else "NO")


main()
