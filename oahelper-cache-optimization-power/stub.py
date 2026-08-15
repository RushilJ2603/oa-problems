import sys

def solve(n: int, power: list[int]) -> int:
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    power = [int(x) for x in data[1:1+n]]
    print(solve(n, power))

if __name__ == '__main__':
    main()
