#!/usr/bin/env python3
import random
import sys


def main():
    random.seed(int(sys.argv[1]))
    size = int(sys.argv[2])

    if size <= 3:
        n = random.randint(1, 4)
    elif size <= 10:
        n = random.randint(3, 12)
    elif size <= 40:
        n = random.randint(10, 40)
    elif size <= 120:
        n = random.randint(20, 80)  # O(n^2) brute feasible
    elif size <= 400:
        n = random.randint(200, 2000)
    else:
        n = 100000  # MAX-SCALE

    mode = random.randrange(6)
    if mode == 0:
        # identity permutation-ish: 0..n-1 capped
        a = list(range(n))
        random.shuffle(a)
        a = [x % n for x in a]
    elif mode == 1:
        # all same value
        v = random.randrange(n)
        a = [v] * n
    elif mode == 2:
        # mostly zeros
        a = [0] * n
        for i in range(n // 3):
            a[i] = random.randrange(n)
    elif mode == 3:
        # consecutive with duplicates near mex gap
        a = [min(i, n - 1) for i in range(n)]
        if n > 2:
            a[n // 2] = a[n // 2 - 1]
    elif mode == 4:
        # all max value n-1
        a = [n - 1] * n
    else:
        a = [random.randrange(n) for _ in range(n)]

    print(n)
    print(*a)


if __name__ == "__main__":
    main()
