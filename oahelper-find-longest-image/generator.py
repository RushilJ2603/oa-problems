#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    # Map size -> (n, m). At large size hit m = 1e5 max-scale.
    if size <= 3:
        n = random.randint(1, 2)
        m = random.randint(1, 3)
    elif size <= 12:
        n = random.randint(1, min(5, size))
        m = random.randint(2, size)
    elif size <= 60:
        n = random.randint(1, min(10, 20))
        m = size
    elif size <= 150:
        n = random.randint(5, 20)
        m = size
    elif size <= 400:
        n = 20
        m = min(10000, size * 20)
    else:
        # MAX-SCALE
        n = 20
        m = 100000
    k = random.randint(0, 10**9) if seed % 7 != 0 else random.randint(0, 100)
    mode = seed % 6
    colors = [[0] * m for _ in range(n)]
    if mode == 0:
        for i in range(n):
            for j in range(m):
                colors[i][j] = random.randint(1, 10**9)
    elif mode == 1:
        # mostly flat rows
        for i in range(n):
            base = random.randint(1, 10**6)
            for j in range(m):
                colors[i][j] = base + random.randint(0, max(0, k))
    elif mode == 2:
        # sorted ascending per row
        for i in range(n):
            for j in range(m):
                colors[i][j] = j + 1
    elif mode == 3:
        # reverse-ish spikes
        for i in range(n):
            for j in range(m):
                colors[i][j] = (m - j) * (i + 1)
    elif mode == 4:
        # all equal
        v = random.randint(1, 10**9)
        for i in range(n):
            for j in range(m):
                colors[i][j] = v
    else:
        # adversarial: windows break every few columns
        for i in range(n):
            for j in range(m):
                colors[i][j] = 1 if j % 5 != 0 else 10**9
    print(k)
    print(n, m)
    for row in colors:
        print(" ".join(map(str, row)))

if __name__ == "__main__":
    main()
