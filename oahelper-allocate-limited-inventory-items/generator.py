#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 150:
        n = 9999
    elif size >= 40:
        n = min(200, max(20, size))
    else:
        n = max(1, min(30, size))

    # Keep inventory modest so the one-by-one brute stays fast on random checks.
    if size >= 150:
        inv = min(10**7, n * 50)
    else:
        inv = random.randint(1, max(1, n * 5))

    mode = seed % 5
    reqs = []
    used_ids = set()
    for i in range(n):
        while True:
            cid = random.randint(1, 10**7) if mode != 0 else (i + 1)
            if cid not in used_ids:
                used_ids.add(cid)
                break
        if mode == 1:
            # all same bid — pure round-robin by timestamp
            qty = random.randint(1, 20)
            bid = 100
            ts = i if seed % 2 == 0 else random.randint(1, 10**6)
        elif mode == 2:
            qty = random.randint(1, 10)
            bid = random.randint(1, 5)
            ts = random.randint(1, 10**6)
        elif mode == 3:
            qty = 10**7 - 1
            bid = random.randint(1, 100)
            ts = i
            inv = min(inv, n)  # tiny inventory vs huge qty
        else:
            qty = random.randint(1, 100)
            bid = random.randint(1, 1000)
            ts = random.randint(1, 10**6)
        reqs.append((cid, qty, bid, ts))

    print(n)
    print(4)
    for r in reqs:
        print(*r)
    print(max(1, inv))


if __name__ == "__main__":
    main()
