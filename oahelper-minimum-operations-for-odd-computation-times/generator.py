#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size -> n; large size hits the constraint bound (2e5)
    if size <= 3:
        n = random.randint(1, 3)
    elif size <= 10:
        n = random.randint(4, 12)
    elif size <= 40:
        n = random.randint(15, 40)
    elif size <= 150:
        n = random.randint(50, min(150, size + 20))
    elif size <= 400:
        n = random.randint(200, 400)
    else:
        n = 200000  # MAX-SCALE

    mode = seed % 7
    a = []
    if mode == 0:
        # all odd
        a = [random.randrange(1, 10**9, 2) for _ in range(n)]
    elif mode == 1:
        # pure powers of two (single odd base)
        a = [1 << random.randint(0, 30) for _ in range(n)]
    elif mode == 2:
        # many duplicates of one large even
        v = random.randrange(2, 10**9 + 1, 2)
        a = [v] * n
    elif mode == 3:
        # chain of related halvings (same odd base, mixed exponents)
        base = random.randrange(1, 5000, 2)
        a = [base * (1 << random.randint(0, 20)) for _ in range(n)]
        a = [min(x, 10**9) for x in a]
    elif mode == 4:
        # sorted ascending mixed
        a = sorted(random.randint(1, 10**9) for _ in range(n))
    elif mode == 5:
        # reverse-sorted
        a = sorted((random.randint(1, 10**9) for _ in range(n)), reverse=True)
    else:
        # fully random
        a = [random.randint(1, 10**9) for _ in range(n)]

    # occasionally force max value bound
    if seed % 11 == 0 and n >= 1:
        a[random.randrange(n)] = 10**9
    if seed % 13 == 0 and n >= 1:
        a[0] = 1

    print(n)
    print(" ".join(map(str, a)))

if __name__ == "__main__":
    main()
