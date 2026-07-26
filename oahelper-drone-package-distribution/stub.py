import sys


def solve(N, packages, totalZones, maxPackages, maxWeight):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    idx = 0
    N = data[idx]; idx += 1
    packages = []
    for _ in range(N):
        packages.append((data[idx], data[idx + 1]))
        idx += 2
    totalZones = data[idx]
    maxPackages = data[idx + 1]
    maxWeight = data[idx + 2]
    print(solve(N, packages, totalZones, maxPackages, maxWeight))


if __name__ == "__main__":
    main()
