#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size -> n; large size hits max constraint
    if size <= 3:
        n = random.randint(1, 3)
    elif size <= 10:
        n = random.randint(3, 10)
    elif size <= 40:
        n = random.randint(10, 40)
    elif size <= 150:
        n = random.randint(50, min(150, size))
    elif size <= 400:
        n = random.randint(200, min(400, size))
    else:
        n = 100000  # MAX-SCALE

    mode = seed % 7
    weights = []
    if mode == 0:
        # all equal
        w = random.randint(1, 10**9)
        weights = [w] * n
        max_wt = w + random.randint(0, min(n + 5, 10**9 - w)) if w < 10**9 else w
    elif mode == 1:
        # sorted ascending
        weights = sorted(random.randint(1, 10**9) for _ in range(n))
        max_wt = random.randint(1, 10**9)
    elif mode == 2:
        # reverse sorted
        weights = sorted((random.randint(1, 10**9) for _ in range(n)), reverse=True)
        max_wt = random.randint(1, 10**9)
    elif mode == 3:
        # many tiny, few huge
        weights = [1] * (n // 2) + [10**9] * (n - n // 2)
        random.shuffle(weights)
        max_wt = random.randint(2, max(2, min(n + 2, 10**9)))
    elif mode == 4:
        # max_wt tiny
        weights = [random.randint(1, 10**9) for _ in range(n)]
        max_wt = random.randint(1, 5)
    elif mode == 5:
        # max_wt huge — can ship everything feasible
        weights = [random.randint(1, 10**6) for _ in range(n)]
        max_wt = 10**9
    else:
        weights = [random.randint(1, 10**9) for _ in range(n)]
        max_wt = random.randint(1, 10**9)

    print(n)
    for w in weights:
        print(w)
    print(max_wt)

if __name__ == "__main__":
    main()
