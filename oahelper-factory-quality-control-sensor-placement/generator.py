#!/usr/bin/env python3
import random
import sys


def main():
    random.seed(int(sys.argv[1]))
    size = int(sys.argv[2]) if len(sys.argv) > 2 else 10

    if size >= 400:
        N = 100000
    elif size >= 150:
        N = min(5000, max(200, size * 20))
    elif size >= 40:
        N = min(500, max(40, size * 5))
    else:
        N = max(2, size)

    max_pairs = N * (N - 1) // 2
    # Keep K in a range that is interesting but valid
    if max_pairs <= 1:
        K = 1
    else:
        # Prefer modest K so D is often non-zero; occasionally large K
        roll = random.randrange(5)
        if roll == 0:
            K = random.randint(1, min(max_pairs, max(1, N // 2)))
        elif roll == 1:
            K = random.randint(1, min(max_pairs, N))
        else:
            K = random.randint(1, min(max_pairs, max(1, N * 2)))

    mode = random.randrange(6)
    if mode == 0:
        A = [random.randint(0, 10**9) for _ in range(N)]
    elif mode == 1:
        A = sorted(random.randint(0, 10**9) for _ in range(N))
    elif mode == 2:
        A = sorted((random.randint(0, 10**9) for _ in range(N)), reverse=True)
    elif mode == 3:
        v = random.randint(0, 10**9)
        A = [v] * N
    elif mode == 4:
        # zigzag peaks / valleys
        A = []
        for i in range(N):
            if i % 2 == 0:
                A.append(random.randint(5 * 10**8, 10**9))
            else:
                A.append(random.randint(0, 10**8))
    else:
        # small values for more zero-drop edge cases
        A = [random.randint(0, 1000) for _ in range(N)]

    print(N, K)
    print(" ".join(map(str, A)))


if __name__ == "__main__":
    main()
