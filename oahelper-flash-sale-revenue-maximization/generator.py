#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size <= 3:
        n = random.randint(1, 3)
        max_stock = random.randint(1, 8)
    elif size <= 10:
        n = random.randint(2, 8)
        max_stock = random.randint(5, 40)
    elif size <= 40:
        n = random.randint(5, 40)
        max_stock = random.randint(10, 200)
    elif size <= 150:
        # Keep stocks modest so heap-brute finishes on gate random checks
        n = random.randint(20, min(120, size))
        max_stock = random.randint(20, 80)
    elif size <= 400:
        n = random.randint(1000, 5000)
        max_stock = 100000
    else:
        n = 100000
        max_stock = 100000

    stock = [random.randint(1, max_stock) for _ in range(n)]
    total = sum(stock)
    # orders in [1, total]
    if size <= 150:
        # Prefer moderate orders for brute speed while still varying
        orders = random.randint(1, min(total, max(1, n * max_stock // 4)))
    else:
        orders = random.randint(1, total)

    print(n)
    for s in stock:
        print(s)
    print(orders)


if __name__ == "__main__":
    main()
