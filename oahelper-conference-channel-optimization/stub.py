import sys

def solve(n, m, u, v, w):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    n, m = data[0], data[1]
    u, v, w = [], [], []
    idx = 2
    for _ in range(m):
        u.append(data[idx]); v.append(data[idx + 1]); w.append(data[idx + 2])
        idx += 3
    print(solve(n, m, u, v, w))

if __name__ == "__main__":
    main()
