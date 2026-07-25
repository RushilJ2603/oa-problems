import sys


def solve(N, W, K, t, u):
    # WRITE YOUR CODE HERE
    return [(0, -1)] * N


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    idx = 0
    N = int(data[idx]); idx += 1
    W = int(data[idx]); idx += 1
    K = int(data[idx]); idx += 1
    t = [0] * N
    u = [0] * N
    for i in range(N):
        t[i] = int(data[idx]); idx += 1
        u[i] = int(data[idx]); idx += 1
    for flag, sniper in solve(N, W, K, t, u):
        print(flag, sniper)


if __name__ == "__main__":
    main()
