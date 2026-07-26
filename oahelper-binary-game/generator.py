#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2]) if len(sys.argv) > 2 else 10
    random.seed(seed)

    # Keep max_length small for small size (brute cross-check); hit 1e5 only at large size.
    if size <= 3:
        max_length = random.randint(1, 8)
    elif size <= 10:
        max_length = random.randint(5, 25)
    elif size <= 40:
        max_length = random.randint(20, 80)
    elif size <= 150:
        max_length = random.randint(40, 180)
    elif size <= 400:
        max_length = random.randint(500, 5000)
    else:
        max_length = 100000

    min_length = random.randint(1, max_length)

    mode = seed % 7
    if mode == 0:
        one_group = random.randint(1, min(2000, max(1, max_length)))
        zero_group = random.randint(1, min(2000, max(1, max_length)))
    elif mode == 1:
        # Equal groups
        g = random.randint(1, min(2000, max(1, max_length)))
        one_group = zero_group = g
    elif mode == 2:
        # Tiny groups (dense DP)
        one_group = random.randint(1, 3)
        zero_group = random.randint(1, 3)
    elif mode == 3:
        # Groups larger than max_length -> answer often 0
        one_group = random.randint(max_length + 1, max_length + 50) if max_length < 2000 else 2000
        zero_group = random.randint(max_length + 1, max_length + 50) if max_length < 2000 else 2000
        one_group = min(one_group, 2000)
        zero_group = min(zero_group, 2000)
    elif mode == 4:
        one_group = 1
        zero_group = random.randint(1, min(20, 2000))
    elif mode == 5:
        one_group = random.randint(1, min(20, 2000))
        zero_group = 1
    else:
        one_group = random.randint(1, min(2000, 100))
        zero_group = random.randint(1, min(2000, 100))

    # Occasionally force full-range / single-length extremes
    if seed % 11 == 0:
        min_length = 1
    if seed % 13 == 0:
        min_length = max_length

    print(min_length)
    print(max_length)
    print(one_group)
    print(zero_group)


if __name__ == "__main__":
    main()
