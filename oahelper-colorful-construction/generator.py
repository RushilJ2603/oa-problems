#!/usr/bin/env python3
import sys
import random

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size <= 3:
        r = random.randint(0, 8)
        b = random.randint(0, 8)
    elif size <= 10:
        r = random.randint(0, 30)
        b = random.randint(0, 30)
    elif size <= 40:
        r = random.randint(0, 80)
        b = random.randint(0, 80)
    elif size <= 150:
        # keep meet-in-middle feasible: h ~ sqrt(2*(r+b)) <= ~40 => r+b <= ~800
        r = random.randint(0, 400)
        b = random.randint(0, 400)
    else:
        r = 200000
        b = 200000

    if r + b == 0:
        r = 1
    print(r, b)

if __name__ == "__main__":
    main()
