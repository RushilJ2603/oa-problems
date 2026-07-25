#!/usr/bin/env python3
import random
import sys


def main():
    random.seed(int(sys.argv[1]))
    size = int(sys.argv[2])

    # Keep n small for O(n*k) brute when size <= 120 (gate uses these sizes)
    if size <= 3:
        n = random.randint(1, 3)
    elif size <= 10:
        n = random.randint(2, 8)
    elif size <= 40:
        n = random.randint(5, 25)
    elif size <= 120:
        n = random.randint(10, 40)
    elif size <= 400:
        n = random.randint(200, 2000)
    else:
        n = 100000  # MAX-SCALE

    if size <= 120:
        k = random.randint(1, max(1, (n + 1) // 2))
    elif size <= 400:
        k = random.randint(1, min(n, 5000))
    else:
        k = random.randint(1, 100000)

    mode = random.randrange(6)
    a = []
    if mode == 0:
        # all positive
        a = [random.randint(1, 10**9) for _ in range(n)]
    elif mode == 1:
        # all negative
        a = [random.randint(-(10**9), -1) for _ in range(n)]
    elif mode == 2:
        # alternating
        for i in range(n):
            v = random.randint(1, 10**9)
            a.append(v if i % 2 == 0 else -v)
    elif mode == 3:
        # near overflow bounds
        a = [random.choice([10**9, -(10**9), 0, 1, -1]) for _ in range(n)]
    elif mode == 4:
        # mostly zeros / small
        a = [random.randint(-5, 5) for _ in range(n)]
    else:
        a = [random.randint(-(10**9), 10**9) for _ in range(n)]

    print(n)
    print(k)
    for x in a:
        print(x)


if __name__ == "__main__":
    main()
