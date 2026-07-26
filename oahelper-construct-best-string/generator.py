#!/usr/bin/env python3
import random
import sys
import string

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 200:
        # MAX-SCALE: large limit, small automaton
        n = random.randint(1, 3)
        alphabet = "ab"
        strings = []
        for i in range(n):
            L = random.randint(1, 4)
            strings.append("".join(random.choice(alphabet) for _ in range(L)))
        points = [random.randint(1, 10000) for _ in range(n)]
        limit = 10**6
    elif size >= 60:
        n = random.randint(1, 8)
        alphabet = string.ascii_lowercase[: random.randint(2, 8)]
        strings = []
        total = 0
        for _ in range(n):
            L = random.randint(1, min(10, 40 - total if total < 40 else 1))
            total += L
            strings.append("".join(random.choice(alphabet) for _ in range(L)))
        points = [random.randint(1, 100) for _ in range(n)]
        limit = random.randint(20, min(size * 2, 500))
    else:
        if random.random() < 0.1:
            print(0)
            print(random.randint(0, max(1, size)))
            return
        n = random.randint(1, min(4, max(1, size // 2 + 1)))
        alphabet = string.ascii_lowercase[: random.randint(1, 4)]
        strings = []
        for _ in range(n):
            L = random.randint(1, 4)
            strings.append("".join(random.choice(alphabet) for _ in range(L)))
        points = [random.randint(1, 20) for _ in range(n)]
        limit = random.randint(0, min(size, 30))

    print(n)
    print(" ".join(strings))
    print(" ".join(map(str, points)))
    print(limit)

if __name__ == "__main__":
    main()
