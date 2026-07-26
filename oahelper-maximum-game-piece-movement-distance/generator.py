#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 300:
        n = 40000
    elif size >= 150:
        n = min(5000, max(200, size * 20))
    else:
        n = max(1, size)

    # Vary piece density with seed so outputs differ.
    mode = seed % 7
    if mode == 0:
        # sparse pieces
        k = max(0, min(n, n // 10 + (seed % 5)))
    elif mode == 1:
        # dense pieces
        k = max(0, min(n, n - n // 10 - (seed % 3)))
    elif mode == 2:
        # half
        k = n // 2
    elif mode == 3:
        # all empty / all full extremes
        k = 0 if seed % 2 == 0 else n
    elif mode == 4:
        # single piece
        k = 1 if n >= 1 else 0
    elif mode == 5:
        # block of pieces then empties
        k = max(1, min(n, n // 3 + 1))
    else:
        k = random.randint(0, n)

    board = [0] * n
    if mode == 5 and k > 0:
        # contiguous block placed depending on seed
        start = 0 if seed % 2 == 0 else max(0, n - k)
        for i in range(start, start + k):
            board[i] = 1
    elif mode == 6:
        # alternating-ish
        for i in range(n):
            board[i] = 1 if (i + seed) % 3 == 0 else 0
        # adjust to roughly k? just leave pattern
    else:
        idxs = list(range(n))
        random.shuffle(idxs)
        for i in idxs[:k]:
            board[i] = 1

    print(n)
    print(" ".join(map(str, board)))


if __name__ == "__main__":
    main()
