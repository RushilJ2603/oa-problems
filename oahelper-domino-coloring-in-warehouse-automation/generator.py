#!/usr/bin/env python3
import random
import sys
import string

LETTERS = string.ascii_letters


def emit_tiling(n, rng):
    used = set()
    top, bottom = [], []
    letter_idx = [0]

    def next_letter():
        if len(used) >= len(LETTERS):
            used.clear()
        while True:
            ch = LETTERS[letter_idx[0] % len(LETTERS)]
            letter_idx[0] += 1
            if ch not in used:
                used.add(ch)
                return ch

    i = 0
    while i < n:
        if i + 1 < n and rng.random() < 0.5:
            a, b = next_letter(), next_letter()
            top.extend([a, a])
            bottom.extend([b, b])
            i += 2
        else:
            a = next_letter()
            top.append(a)
            bottom.append(a)
            i += 1
    return "".join(top), "".join(bottom)


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    rng = random.Random()
    rng.seed(seed)

    if size <= 3:
        n = rng.randint(1, 3)
    elif size <= 10:
        n = rng.randint(4, 10)
    elif size <= 40:
        n = rng.randint(11, 40)
    elif size <= 150:
        n = rng.randint(41, 150)
    elif size <= 400:
        n = rng.randint(151, 400)
    else:
        n = 100000  # MAX-SCALE at constraint bound

    top, bottom = emit_tiling(n, rng)
    sys.stdout.write(top + "\n" + bottom + "\n")


if __name__ == "__main__":
    main()
