#!/usr/bin/env python3
"""Generate one random lowercase string.
CLI: python3 generator.py <seed> <size>
At large size, emit a MAX-SCALE string of length 500.
"""
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    MAX_N = 500
    alphabet = "abcdefghijklmnopqrstuvwxyz"

    if size >= 200:
        n = MAX_N
    else:
        n = max(1, min(MAX_N, size))

    # Mix patterns for adversarial variety
    mode = seed % 5
    if mode == 0:
        # random
        s = "".join(random.choice(alphabet[: max(2, min(26, n))]) for _ in range(n))
    elif mode == 1:
        # few distinct letters (encourages merges)
        k = random.randint(1, min(4, 26))
        letters = random.sample(alphabet, k)
        s = "".join(random.choice(letters) for _ in range(n))
    elif mode == 2:
        # alternating two letters
        a, b = random.sample(alphabet, 2)
        s = "".join(a if i % 2 == 0 else b for i in range(n))
    elif mode == 3:
        # runs of identical letters
        s = []
        while len(s) < n:
            ch = random.choice(alphabet)
            run = random.randint(1, min(8, n - len(s)))
            s.extend([ch] * run)
        s = "".join(s[:n])
    else:
        # sorted / almost sorted blocks
        letters = list(alphabet)
        random.shuffle(letters)
        s = []
        per = max(1, n // 26)
        for ch in letters:
            s.extend([ch] * per)
            if len(s) >= n:
                break
        while len(s) < n:
            s.append(random.choice(alphabet))
        s = "".join(s[:n])

    print(s)


if __name__ == "__main__":
    main()
