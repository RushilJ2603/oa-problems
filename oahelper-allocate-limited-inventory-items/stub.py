import sys


def solve(requests, total_inventory):
    # WRITE YOUR CODE HERE
    return []


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    cols = int(next(it))
    requests = []
    for _ in range(n):
        requests.append([int(next(it)) for _ in range(cols)])
    total_inventory = int(next(it))
    res = solve(requests, total_inventory)
    print(" ".join(map(str, res)))


if __name__ == "__main__":
    main()
