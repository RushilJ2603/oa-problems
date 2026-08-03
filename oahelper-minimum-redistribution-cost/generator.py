#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 1000:
        n = 100000
    else:
        n = max(1, min(size, 100000))

    # Build an array whose sum is divisible by n.
    avg = random.randint(0, 100000) if n < 100000 else random.randint(0, 1000)
    products = [avg] * n
    # Sprinkle surplus/deficit pairs so the equalisation is non-trivial.
    ops = min(n, max(1, size if size < 1000 else 5000))
    for _ in range(ops):
        i = random.randrange(n)
        j = random.randrange(n)
        if i == j:
            continue
        delta = random.randint(0, min(products[i], 100000 - products[j], 1000 if n >= 100000 else 100000))
        products[i] -= delta
        products[j] += delta

    # Rare all-equal / all-zero / single-spike variants
    mode = random.randrange(8)
    if mode == 0 and n > 1:
        products = [0] * n
        products[random.randrange(n)] = n * random.randint(1, 100)
    elif mode == 1:
        products = [avg] * n

    print(n)
    for x in products:
        print(x)

if __name__ == "__main__":
    main()
