#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Brute is O(n^2); keep generated cases small for cross-check sizes,
    # but emit max-scale n=3e5 at large size for TLE discrimination.
    if size <= 3:
        n = random.randint(1, 4)
    elif size <= 10:
        n = random.randint(4, 12)
    elif size <= 40:
        n = random.randint(10, 40)
    elif size <= 150:
        n = random.randint(20, 80)  # still ok for O(n^2) brute
    else:
        n = 300000

    mode = seed % 8
    if mode == 0:
        s = '0' * (n // 2) + '1' * (n - n // 2)
    elif mode == 1:
        s = '1' * (n // 2) + '0' * (n - n // 2)
    elif mode == 2:
        s = ''.join('01'[i % 2] for i in range(n))
    elif mode == 3:
        s = '1' * n
    elif mode == 4:
        s = '0' * n
    elif mode == 5:
        s = '0' * (n - 1) + '1'
    elif mode == 6:
        s = '1' + '0' * (n - 1)
    else:
        s = ''.join(random.choice('01') for _ in range(n))

    print(s)

if __name__ == "__main__":
    main()
