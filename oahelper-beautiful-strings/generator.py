#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Brute is O(N*K). Keep N modest for sizes used in brute cross-check (<=120),
    # but emit max-scale N=1e9 at large size.
    if size <= 3:
        N = random.randint(1, 4)
        K = random.randint(0, min(3, N - 1 if N > 1 else 0))
    elif size <= 10:
        N = random.randint(2, 12)
        K = random.randint(0, min(8, N - 1))
    elif size <= 40:
        N = random.randint(5, 50)
        K = random.randint(0, min(20, N - 1))
    elif size <= 150:
        N = random.randint(10, 200)  # iterative DP still fine
        K = random.randint(0, min(40, N - 1))
    else:
        N = 10**9
        K = random.randint(0, 100)

    # occasional extreme K relative to N
    if seed % 5 == 0 and N > 1 and size <= 150:
        K = N - 1
    if seed % 7 == 0:
        K = 0
    if seed % 11 == 0 and size > 150:
        K = 100

    print(N, K)

if __name__ == "__main__":
    main()
