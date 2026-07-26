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
        n = random.randint(3, 10)
    elif size <= 40:
        n = random.randint(10, 40)
    elif size <= 150:
        n = random.randint(40, min(150, size))
    else:
        n = 10**5  # max-scale

    mode = seed % 5
    if mode == 0:
        a = [random.randint(1, 10**9) for _ in range(n)]
    elif mode == 1:
        a = sorted(random.randint(1, 10**9) for _ in range(n))
    elif mode == 2:
        a = sorted((random.randint(1, 10**9) for _ in range(n)), reverse=True)
    elif mode == 3:
        v = random.randint(1, 10**9)
        a = [v] * n
    else:
        a = [random.randint(1, 100) for _ in range(n)]

    print(n)
    print(" ".join(map(str, a)))

if __name__ == "__main__":
    main()
