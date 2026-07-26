import sys

def solve(n, values, state, m):
    # WRITE YOUR CODE HERE
    return []

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    values = [int(next(it)) for _ in range(n)]
    state = next(it)
    m = int(next(it))
    result = solve(n, values, state, m)
    if not result:
        sys.stdout.write("\n")
    else:
        sys.stdout.write(" ".join(map(str, result)) + "\n")

if __name__ == "__main__":
    main()
