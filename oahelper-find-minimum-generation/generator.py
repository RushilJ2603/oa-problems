#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size -> n; at large size hit n = 1e5 (constraint max)
    if size <= 3:
        n = random.randint(1, 3)
    elif size <= 10:
        n = random.randint(3, 10)
    elif size <= 40:
        n = random.randint(10, 40)
    elif size <= 150:
        n = random.randint(50, min(150, size + 20))
    else:
        n = 10**5  # MAX-SCALE

    if n <= 20:
        lo, hi = 1, 50
    elif n <= 150:
        lo, hi = 1, 10**6
    else:
        lo, hi = 1, 10**9

    layer = [random.randint(lo, hi) for _ in range(n)]

    # Occasionally force adversarial patterns
    mode = random.randint(0, 5)
    if mode == 0 and n >= 2:
        # all equal
        v = random.randint(lo, hi)
        layer = [v] * n
    elif mode == 1 and n >= 2:
        # one max, rest much smaller (parity-heavy)
        mx = random.randint(lo + 1, hi) if hi > lo else hi
        layer = [random.randint(lo, mx) for _ in range(n)]
        layer[random.randint(0, n - 1)] = mx
    elif mode == 2 and n >= 2:
        # sorted ascending
        layer.sort()
    elif mode == 3 and n >= 2:
        # reverse sorted
        layer.sort(reverse=True)

    print(n)
    print(" ".join(map(str, layer)))

if __name__ == "__main__":
    main()
