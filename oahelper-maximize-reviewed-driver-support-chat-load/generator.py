#!/usr/bin/env python3
import sys
import random

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    if size <= 3:
        n = random.randint(1, 5)
    elif size <= 10:
        n = random.randint(5, 25)
    elif size <= 40:
        n = random.randint(30, 100)
    elif size <= 150:
        n = random.randint(200, 600)
    else:
        n = min(100000, 2000 + size * 200)  # grows with size; hits ~1e5 at size>=490
    max_k = 6 if n > 5000 else 8
    k = random.randrange(2, max_k + 1, 2)
    # keep values smaller on large n to speed I/O a bit; still valid
    vmax = 10**7 if n < 5000 else 10**5
    chat = [random.randint(0, vmax) for _ in range(n)]
    rev = [random.randint(0, n - 1) for _ in range(k)]
    print(n)
    print(*chat)
    print(k)
    print(*rev)

if __name__ == "__main__":
    main()
