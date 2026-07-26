#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size <= 3:
        n = random.randint(1, 3)
    elif size <= 10:
        n = random.randint(3, 12)
    elif size <= 40:
        n = random.randint(10, 50)
    elif size <= 150:
        n = random.randint(40, 120)
    elif size <= 400:
        n = random.randint(1000, 8000)
    else:
        n = 100000

    k = random.randint(0, min(n + random.randint(0, 50), 100000))
    x = random.choice([0, 1, 3, 7, 15, 31, 63, 127, 255, 1023, 65535, random.randint(0, 100000)])

    # Mix value ranges for bit diversity
    mode = random.randrange(5)
    a = []
    for _ in range(n):
        if mode == 0:
            a.append(random.randint(0, 100))
        elif mode == 1:
            a.append(random.randint(0, 10**9))
        elif mode == 2:
            a.append(random.choice([0, x, x ^ random.randint(0, 20)]))
        elif mode == 3:
            a.append(random.randint(0, 1) * random.randint(0, 10**9))
        else:
            a.append(random.randint(0, max(1, x * 2)))

    print(n)
    print(k)
    print(x)
    for v in a:
        print(v)


if __name__ == "__main__":
    main()
