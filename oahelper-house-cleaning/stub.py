import sys

def solve(n, houses):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    houses = []
    for _ in range(n):
        x = int(next(it)); y = int(next(it))
        houses.append((x, y))
    print(solve(n, houses))

if __name__ == "__main__":
    main()
