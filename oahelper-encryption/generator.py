#!/usr/bin/env python3
import random
import string
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    # scale |S| with size; hit constraint bound at large size
    if size <= 3:
        n = random.randint(1, 4)
    elif size <= 10:
        n = random.randint(5, 15)
    elif size <= 40:
        n = random.randint(20, 80)
    elif size <= 150:
        n = random.randint(100, 400)
    else:
        n = 1000  # max-scale
    alphabet = string.ascii_letters + "_"
    # sometimes force a tight / wide spread of codes
    mode = random.randint(0, 4)
    if mode == 0:
        chars = [random.choice(alphabet) for _ in range(n)]
    elif mode == 1:
        base = random.choice(alphabet)
        chars = [base] * n
    elif mode == 2:
        pool = alphabet[: random.randint(2, 8)]
        chars = [random.choice(pool) for _ in range(n)]
    elif mode == 3:
        # wide spread (likely some pairs exceed 17)
        chars = [random.choice(alphabet) for _ in range(n)]
    else:
        # consecutive-ish block
        start = random.randint(0, max(0, len(alphabet) - 10))
        pool = alphabet[start : start + 10]
        chars = [random.choice(pool) for _ in range(n)]
    sys.stdout.write("".join(chars) + "\n")

if __name__ == "__main__":
    main()
