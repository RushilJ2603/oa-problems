#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    # Map size arg to grid dimension; large size -> max-scale 100x100
    if size <= 3:
        n = m = 2
    elif size <= 10:
        n = random.randint(2, 4)
        m = random.randint(2, 4)
    elif size <= 40:
        n = random.randint(4, 12)
        m = random.randint(4, 12)
    elif size <= 150:
        n = random.randint(20, 40)
        m = random.randint(20, 40)
    else:
        n = m = 100

    # Vary infection density with seed
    dens = [0.05, 0.15, 0.3, 0.5, 0.7, 0.9, 0.0, 1.0][seed % 8]
    print(n, m)
    for i in range(n):
        row = []
        for j in range(m):
            if dens <= 0:
                row.append(0)
            elif dens >= 1:
                row.append(1)
            else:
                row.append(1 if random.random() < dens else 0)
        # checkerboard pattern sometimes
        if seed % 11 == 0:
            row = [((i + j) % 2) for j in range(m)]
        print(*row)


if __name__ == "__main__":
    main()
