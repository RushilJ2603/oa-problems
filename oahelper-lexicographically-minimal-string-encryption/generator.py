#!/usr/bin/env python3
import random
import string
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    if size <= 3:
        n = random.randint(1, 5)
    elif size <= 10:
        n = random.randint(6, 20)
    elif size <= 40:
        n = random.randint(30, 200)
    elif size <= 150:
        n = random.randint(500, 5000)
    else:
        n = 200000  # max-scale
    mode = random.randint(0, 5)
    if mode == 0:
        s = "".join(random.choice(string.ascii_lowercase) for _ in range(n))
    elif mode == 1:
        s = "a" * n
    elif mode == 2:
        s = "z" * n
    elif mode == 3:
        s = "".join(reversed(string.ascii_lowercase)) * (n // 26 + 1)
        s = s[:n]
    elif mode == 4:
        s = (string.ascii_lowercase) * (n // 26 + 1)
        s = s[:n]
    else:
        # mostly sorted with a few inversions
        s = list("".join(random.choice(string.ascii_lowercase) for _ in range(n)))
        s.sort()
        for _ in range(min(n, 20)):
            i = random.randrange(n)
            j = random.randrange(n)
            s[i], s[j] = s[j], s[i]
        s = "".join(s)
    sys.stdout.write(s + "\n")

if __name__ == "__main__":
    main()
