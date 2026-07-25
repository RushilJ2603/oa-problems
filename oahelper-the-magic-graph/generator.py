#!/usr/bin/env python3
import sys
import random

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Keep N,M small enough for O(M^2 N) brute on gate random sizes (<=120).
    # Hit constraint max only at large size.
    if size <= 3:
        N = random.randint(1, 4)
        M = random.randint(1, 4)
    elif size <= 10:
        N = random.randint(2, 8)
        M = random.randint(2, 8)
    elif size <= 40:
        N = random.randint(4, 15)
        M = random.randint(4, 15)
    elif size <= 150:
        N = random.randint(8, 25)
        M = random.randint(8, 25)
    else:
        N = 100000
        M = 100000

    L, R, C = [], [], []
    L.append(1)
    R.append(N)
    C.append(random.randint(1, 10**9 if size >= 400 else max(N * 10, 50)))

    for _ in range(M - 1):
        a = random.randint(1, N)
        b = random.randint(1, N)
        if a > b:
            a, b = b, a
        if random.random() < 0.35 and N > 1:
            a = random.randint(1, N - 1)
            b = min(N, a + random.randint(1, max(1, N // 3)))
        L.append(a)
        R.append(b)
        C.append(random.randint(1, 10**9 if size >= 400 else max(N * 20, 100)))

    idx = list(range(M))
    random.shuffle(idx)
    L = [L[i] for i in idx]
    R = [R[i] for i in idx]
    C = [C[i] for i in idx]

    print(N)
    print(M)
    print("\n".join(map(str, L)))
    print("\n".join(map(str, R)))
    print("\n".join(map(str, C)))

if __name__ == "__main__":
    main()
