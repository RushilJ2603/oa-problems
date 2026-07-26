#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Cap n,m for small sizes so O(m*n) brute finishes (gate uses sizes up to 120).
    if size <= 3:
        n = random.randint(1, 5)
        m = random.randint(0, 5)
    elif size <= 10:
        n = random.randint(3, 15)
        m = random.randint(0, 20)
    elif size <= 40:
        n = random.randint(10, 60)
        m = random.randint(0, 80)
    elif size <= 120:
        n = random.randint(30, 200)
        m = random.randint(0, 200)
    elif size <= 400:
        n = random.randint(500, 5000)
        m = random.randint(0, 5000)
    else:
        n = 100000
        m = 100000

    mode = seed % 7
    if mode == 0:
        values = [random.randint(1, 10**12) for _ in range(n)]
        state = "".join(random.choice("01") for _ in range(n))
    elif mode == 1:
        # all ones
        values = [random.randint(1, 10**9) for _ in range(n)]
        state = "1" * n
    elif mode == 2:
        # all zeros (often impossible)
        values = [random.randint(1, 10**9) for _ in range(n)]
        state = "0" * n
    elif mode == 3:
        # single source at left, unlocking chain
        values = [random.randint(1, 10**12) for _ in range(n)]
        state = "1" + "0" * (n - 1)
    elif mode == 4:
        # alternating
        values = [random.randint(1, 10**9) for _ in range(n)]
        state = "".join("10"[i % 2] for i in range(n))
    elif mode == 5:
        # sparse ones
        values = sorted([random.randint(1, 10**12) for _ in range(n)], reverse=True)
        state = ["0"] * n
        for i in range(0, n, max(1, n // 5)):
            state[i] = "1"
        state = "".join(state)
    else:
        # duplicates + large values
        base = random.randint(1, 10**12)
        values = [base if i % 3 else random.randint(1, 10**12) for i in range(n)]
        state = "".join(random.choice("01") for _ in range(n))
        if "1" not in state and n > 0:
            state = list(state)
            state[0] = "1"
            state = "".join(state)

    # occasionally force m=0
    if seed % 11 == 0 and size <= 120:
        m = 0

    print(n)
    print(" ".join(map(str, values)))
    print(state)
    print(m)

if __name__ == "__main__":
    main()
