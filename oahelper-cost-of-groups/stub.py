import sys


def solve(n, a, edges):
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.buffer.read().split()
    pos = 0
    t = int(data[pos]); pos += 1
    out = []
    for _ in range(t):
        n = int(data[pos]); pos += 1
        a = [int(data[pos + i]) for i in range(n)]
        pos += n
        edges = []
        for _ in range(n - 1):
            u = int(data[pos]); v = int(data[pos + 1]); pos += 2
            edges.append((u, v))
        out.append(str(solve(n, a, edges)))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
