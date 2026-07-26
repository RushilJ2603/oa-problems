#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    rng = random.Random(seed)

    if size <= 3:
        n = rng.randint(1, 5)
        m = rng.randint(1, 5)
    elif size <= 10:
        n = rng.randint(5, 12)
        m = rng.randint(5, 15)
    elif size <= 40:
        n = rng.randint(15, 30)
        m = rng.randint(15, 40)
    elif size <= 150:
        # O(m*n) brute must stay fast on gate random cross-checks
        n = rng.randint(30, 50)
        m = rng.randint(30, 60)
    else:
        n = 100000
        m = 100000

    values = [rng.randint(0, 10**9) for _ in range(n)]
    # Ensure at least one '1'
    state = ["0"] * n
    ones = rng.randint(1, max(1, min(n, n // 3 + 1)))
    for i in rng.sample(range(n), ones):
        state[i] = "1"
    # Sometimes force single seed in the middle / ends
    kind = rng.randint(0, 4)
    if kind == 0:
        state = ["0"] * n
        state[rng.randint(0, n - 1)] = "1"
    elif kind == 1:
        state = ["1"] * n
    elif kind == 2:
        state = ["0"] * n
        state[0] = "1"
    elif kind == 3:
        state = ["0"] * n
        state[-1] = "1"

    print(n)
    for v in values:
        print(v)
    print("".join(state))
    print(m)


if __name__ == "__main__":
    main()
