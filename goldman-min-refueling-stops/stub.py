import sys


def solve(target, start, stations):
    # stations is a list of (pos, fuel). Return the minimum number of refueling stops, or -1.
    # WRITE YOUR CODE HERE
    return -1


def main():
    data = sys.stdin.buffer.read().split()
    idx = 0
    target = int(data[idx]); start = int(data[idx + 1]); idx += 2
    n = int(data[idx]); idx += 1
    stations = []
    for _ in range(n):
        stations.append((int(data[idx]), int(data[idx + 1]))); idx += 2
    print(solve(target, start, stations))


main()
