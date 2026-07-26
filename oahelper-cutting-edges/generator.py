#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    if size <= 3:
        n = random.randint(1, 8)
    elif size <= 10:
        n = random.randint(5, 30)
    elif size <= 40:
        n = random.randint(20, 80)
    elif size <= 150:
        n = random.randint(50, 200)  # still OK for O(n^2) brute
    elif size <= 400:
        n = random.randint(100, 400)
    else:
        n = 100000  # MAX-SCALE
    # Mix digit distributions so partitions vary
    mode = seed % 5
    if mode == 0:
        chars = [str(random.randint(0, 9)) for _ in range(n)]
    elif mode == 1:
        chars = [str(random.choice([0, 3, 6, 9])) for _ in range(n)]
    elif mode == 2:
        chars = [str(random.choice([1, 2, 4, 5, 7, 8])) for _ in range(n)]
    elif mode == 3:
        chars = ['0'] * n
    else:
        chars = [str((i + seed) % 10) for i in range(n)]
    print(''.join(chars))

if __name__ == "__main__":
    main()
