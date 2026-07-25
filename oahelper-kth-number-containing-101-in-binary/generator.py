#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # size controls magnitude of R and span
    if size <= 3:
        Rmax = 20
    elif size <= 10:
        Rmax = 200
    elif size <= 40:
        Rmax = 5000
    elif size <= 150:
        Rmax = 10**6
    elif size <= 400:
        Rmax = 10**12
    else:
        # MAX-SCALE: full constraint bound
        Rmax = 10**18

    mode = seed % 5
    if mode == 0:
        L = random.randint(1, max(1, Rmax // 2))
        R = random.randint(L, Rmax)
        K = random.randint(1, min(10**18, max(1, (R - L) // 2 + 1)))
    elif mode == 1:
        # tiny range / likely -1
        L = random.randint(1, min(Rmax, 10))
        R = L + random.randint(0, min(3, max(0, Rmax - L)))
        K = random.randint(1, 5)
    elif mode == 2:
        # K larger than possible
        L = random.randint(1, max(1, Rmax // 3))
        R = random.randint(L, min(Rmax, L + max(1, Rmax // 10)))
        K = 10**18
    elif mode == 3:
        # near upper bound
        R = Rmax
        L = max(1, R - random.randint(0, min(R - 1, max(1, Rmax // 100))))
        K = random.randint(1, 10**6)
    else:
        L = 1
        R = Rmax
        K = random.randint(1, min(10**18, max(1, size * 1000)))

    print(L, R, K)

if __name__ == "__main__":
    main()
