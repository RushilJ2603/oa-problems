import sys

MOD = 10**9 + 7


def solve(plan, n, start_zone, end_zone):
    # WRITE YOUR CODE HERE
    return 0


def main():
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    plan = tokens[0]
    n = int(tokens[1])
    start_zone = int(tokens[2])
    end_zone = int(tokens[3])
    print(solve(plan, n, start_zone, end_zone))


if __name__ == "__main__":
    main()
