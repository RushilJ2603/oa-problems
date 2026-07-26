#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size -> string length; large size hits constraint max 2e5
    if size <= 3:
        n = random.randint(1, 5)
    elif size <= 10:
        n = random.randint(5, 20)
    elif size <= 40:
        n = random.randint(20, 80)
    elif size <= 150:
        n = random.randint(80, 400)
    elif size <= 400:
        n = random.randint(1000, 5000)
    else:
        n = 200000  # MAX-SCALE

    # Build string with varied run structure depending on seed
    mode = seed % 5
    chars = []
    if mode == 0:
        # Long monochromatic
        chars = [random.choice("ab")] * n
    elif mode == 1:
        # Strictly alternating
        a, b = "ab" if seed % 2 == 0 else "ba"
        chars = [a if i % 2 == 0 else b for i in range(n)]
    elif mode == 2:
        # Random runs of length 1..10
        while len(chars) < n:
            c = "a" if (not chars or chars[-1] == "b") else "b"
            if random.random() < 0.3:
                c = random.choice("ab")
            run = random.randint(1, min(10, n - len(chars)))
            chars.extend([c] * run)
        chars = chars[:n]
    elif mode == 3:
        # Few very long runs
        rem = n
        cur = "a"
        while rem > 0:
            L = rem if rem < 3 else random.randint(max(1, rem // 4), rem)
            chars.extend([cur] * L)
            rem -= L
            cur = "b" if cur == "a" else "a"
    else:
        chars = [random.choice("ab") for _ in range(n)]

    switch_count = random.randint(1, n)
    sys.stdout.write("".join(chars) + "\n")
    sys.stdout.write(str(switch_count) + "\n")


if __name__ == "__main__":
    main()
