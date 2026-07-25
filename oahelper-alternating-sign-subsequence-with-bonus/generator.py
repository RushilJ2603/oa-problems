#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size <= 12:
        n = random.randint(1, max(1, size + 2))
    elif size <= 60:
        n = random.randint(5, min(40, size))
    elif size <= 150:
        n = random.randint(20, 80)
    elif size < 400:
        n = random.randint(50, 120)
    else:
        n = 100000

    b = random.choice([0, 1, 10, 100, 10**9, random.randint(0, 10**9)])
    print(n)
    print(b)
    for i in range(n):
        # Prefer mixed signs; occasionally all-positive / all-negative.
        mode = random.random()
        if mode < 0.08:
            x = random.randint(1, 10**9)
        elif mode < 0.16:
            x = -random.randint(1, 10**9)
        else:
            x = random.randint(-10**9, 10**9)
            if x == 0:
                x = 1 if random.random() < 0.5 else -1
        print(x)


if __name__ == "__main__":
    main()
