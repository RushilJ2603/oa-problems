#!/usr/bin/env python3
import sys
import random

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size <= 3:
        n = random.randint(2, 4)
    elif size <= 10:
        n = random.randint(2, 8)
    elif size <= 40:
        n = random.randint(4, 14)
    elif size <= 150:
        n = random.randint(8, 18)  # bit-brute friendly
    else:
        n = 200000

    t = [random.randint(0, n - 1) for _ in range(n)]
    # inject structured patterns sometimes
    kind = random.randint(0, 4)
    if kind == 0:
        t = list(range(n))  # 0..n-1 clipped
        t = [min(x, n - 1) for x in t]
    elif kind == 1:
        t = [n - 1] * n
    elif kind == 2:
        t = [0] * n
    elif kind == 3 and n >= 4:
        t = [i // 2 * 2 for i in range(n)]
        t = [min(x, n - 1) for x in t]

    print(n)
    print("\n".join(map(str, t)))

if __name__ == "__main__":
    main()
