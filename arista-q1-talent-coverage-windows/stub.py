import sys


def coverage_windows(talent, talents_count):
    # WRITE YOUR CODE HERE
    return [-1] * len(talent)


data = sys.stdin.buffer.read().split()
n, k = int(data[0]), int(data[1])
talent = [int(x) for x in data[2:2 + n]]
print(" ".join(str(x) for x in coverage_windows(talent, k)))
