#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Constraints: n,m <= 50. Large size hits the bound.
    if size <= 3:
        n = random.randint(1, 3)
        m = random.randint(1, 3)
    elif size <= 10:
        n = random.randint(2, 8)
        m = random.randint(2, 8)
    elif size <= 40:
        n = random.randint(5, 30)
        m = random.randint(5, 30)
    else:
        n = 50
        m = 50

    print(n)
    for _ in range(n):
        s = "".join(str(random.randint(0, 9)) for _ in range(m))
        print(s)


if __name__ == "__main__":
    main()
