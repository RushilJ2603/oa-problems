#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    rng = random.Random(seed)

    if size <= 3:
        n = rng.randint(1, 4)
        m = rng.randint(1, 20)
        k = rng.randint(1, min(5, n))
    elif size <= 10:
        n = rng.randint(4, 10)
        m = rng.randint(10, 40)
        k = rng.randint(1, 5)
    elif size <= 40:
        n = rng.randint(10, 25)
        m = rng.randint(20, 80)
        k = rng.randint(1, 5)
    elif size <= 150:
        # Keep brute (memoized recursion) fast during gate cross-checks
        n = rng.randint(25, 50)
        m = rng.randint(50, 120)
        k = rng.randint(1, 5)
    else:
        n = 1000
        m = 1000
        k = 5

    salary = [rng.randint(1, 2000) for _ in range(n)]
    earning = [rng.randint(0, 10**9) for _ in range(n)]
    kind = rng.randint(0, 3)
    if kind == 0:
        earning = [0] * n
    elif kind == 1:
        salary = [rng.randint(1, 5) for _ in range(n)]
    elif kind == 2:
        salary = [rng.randint(100, 2000) for _ in range(n)]

    print(n)
    print(m)
    print(k)
    print(" ".join(map(str, salary)))
    print(" ".join(map(str, earning)))


if __name__ == "__main__":
    main()
