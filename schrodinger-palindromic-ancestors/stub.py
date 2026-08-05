import sys


def solve(n, tree_from, tree_to, letters, queries):
    """Return the answer for every query, in order."""
    # WRITE YOUR CODE HERE
    return [0] * len(queries)


def main() -> None:
    data = sys.stdin.read().split()
    p = 0
    n = int(data[p]); p += 1
    tree_from = [int(data[p + i]) for i in range(n - 1)]; p += n - 1
    tree_to = [int(data[p + i]) for i in range(n - 1)]; p += n - 1
    letters = data[p]; p += 1
    q = int(data[p]); p += 1
    queries = [int(data[p + i]) for i in range(q)]
    sys.stdout.write("\n".join(map(str, solve(n, tree_from, tree_to, letters, queries))) + "\n")


if __name__ == "__main__":
    main()
