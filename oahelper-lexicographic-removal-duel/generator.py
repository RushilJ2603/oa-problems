#!/usr/bin/env python3
import random
import string
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    if size >= 400:
        n = 200000
    elif size >= 150:
        n = min(200000, size * 200)
    else:
        n = max(1, min(200000, size))
    mode = seed % 7
    alphabet = string.ascii_lowercase
    if mode == 0:
        s = "".join(random.choice(alphabet) for _ in range(n))
    elif mode == 1:
        s = "".join(sorted(random.choice(alphabet) for _ in range(n)))
    elif mode == 2:
        s = "".join(reversed(sorted(random.choice(alphabet) for _ in range(n))))
    elif mode == 3:
        s = "a" * n
    elif mode == 4:
        s = ("ab" * ((n + 1) // 2))[:n]
    elif mode == 5:
        s = ("zyx" * ((n + 2) // 3))[:n]
    else:
        # few distinct letters
        letters = random.sample(alphabet, k=random.randint(2, 5))
        s = "".join(random.choice(letters) for _ in range(n))
    print(s)

if __name__ == "__main__":
    main()
