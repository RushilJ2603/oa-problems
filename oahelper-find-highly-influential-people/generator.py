#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    # Map size -> n in [3, 149]; large size hits max constraint
    if size >= 150:
        n = 149
    elif size >= 40:
        n = min(149, max(3, size // 2 + random.randint(0, 10)))
    else:
        n = min(149, max(3, size if size >= 3 else 3))
    # Vary density with seed
    density = 0.1 + (seed % 7) * 0.12
    print(n)
    for i in range(n):
        row = []
        for j in range(n):
            if random.random() < density:
                row.append(1)
            else:
                row.append(0)
        print(' '.join(map(str, row)))

if __name__ == "__main__":
    main()
