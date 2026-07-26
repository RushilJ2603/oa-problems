#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size → n; large size hits the constraint max (1e5) for TLE/overflow coverage.
    if size <= 3:
        n = random.randint(1, 3)
    elif size <= 10:
        n = random.randint(2, 10)
    elif size <= 40:
        n = random.randint(10, 40)
    elif size <= 150:
        n = random.randint(40, min(150, size + 20))
    elif size <= 400:
        n = random.randint(200, 400)
    else:
        n = 100000  # MAX-SCALE

    print(n)
    row0 = [random.randint(1, 100000) for _ in range(n)]
    row1 = [random.randint(1, 100000) for _ in range(n)]

    # Occasional patterned boards so seeds differ in structure as well as values.
    mode = seed % 5
    if mode == 1 and n > 1:
        row0 = sorted(row0)
        row1 = sorted(row1, reverse=True)
    elif mode == 2:
        row0 = [1] * n
        row1 = [1] * n
    elif mode == 3:
        row0 = [100000] * n
        row1 = [random.randint(1, 100000) for _ in range(n)]
    elif mode == 4 and n >= 2:
        # High values on one diagonal-ish pattern
        for i in range(n):
            if i % 2 == 0:
                row0[i] = 100000
                row1[i] = 1
            else:
                row0[i] = 1
                row1[i] = 100000

    print(" ".join(map(str, row0)))
    print(" ".join(map(str, row1)))

if __name__ == "__main__":
    main()
