#!/usr/bin/env python3
import random
import sys

def build_magical(rng, n):
    """Return a magical binary string of exact even length n."""
    assert n % 2 == 0 and n >= 2

    def rec(target):
        if target == 2:
            return "10"
        # Prefer nesting for larger targets so top-level fan-out stays small
        if target >= 4 and (target > 16 or rng.random() < 0.55):
            return "1" + rec(target - 2) + "0"
        left = rng.randrange(2, target, 2)
        return rec(left) + rec(target - left)

    return rec(n)

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    rng = random.Random(seed)

    if size <= 3:
        n = rng.choice([2, 4, 6])
    elif size <= 10:
        n = rng.choice(list(range(4, 14, 2)))
    elif size <= 40:
        n = rng.choice(list(range(10, 26, 2)))
    elif size <= 150:
        n = rng.choice(list(range(20, 42, 2)))
    else:
        n = 50  # MAX-SCALE constraint bound

    print(build_magical(rng, n))

if __name__ == "__main__":
    main()
