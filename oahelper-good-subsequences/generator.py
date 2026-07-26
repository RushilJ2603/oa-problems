#!/usr/bin/env python3
import random
import sys
import string

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 200:
        n = 10**5
        alphabet = string.ascii_lowercase
    elif size >= 80:
        n = random.randint(500, 5000)
        alphabet = string.ascii_lowercase[: random.randint(3, 26)]
    else:
        # small for bitmask / DFS brute
        n = max(1, min(size, 18))
        alphabet = string.ascii_lowercase[: random.randint(1, min(6, n))]

    word = "".join(random.choice(alphabet) for _ in range(n))
    print(word)

if __name__ == "__main__":
    main()
