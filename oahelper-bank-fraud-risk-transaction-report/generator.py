#!/usr/bin/env python3
"""Deterministic generator: python3 generator.py <seed> <size>"""
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Scale toward constraint bounds; size>=2000 hits MAX-SCALE.
    if size >= 2000:
        n_acc = 100000
        n_txn = 200000
        n_mer = 10000
        n_dev = 50000
        n_loc = 5000
        reference_day = 1000000
    elif size >= 800:
        n_acc = 3000
        n_txn = 10000
        n_mer = 1000
        n_dev = 5000
        n_loc = 1000
        reference_day = 100000
    elif size >= 300:
        n_acc = min(2000, 2 + size * 5)
        n_txn = min(8000, size * 20)
        n_mer = min(1000, 1 + size)
        n_dev = min(4000, size * 10)
        n_loc = min(1000, 1 + size // 2)
        reference_day = 100000
    elif size >= 100:
        n_acc = max(2, size // 2)
        n_txn = size * 2
        n_mer = max(1, size // 5)
        n_dev = size
        n_loc = max(1, size // 10)
        reference_day = 10000
    else:
        n_acc = max(2, min(size + 1, 20))
        n_txn = max(0, size)
        n_mer = max(1, min(size, 8))
        n_dev = max(0, size // 2)
        n_loc = max(1, min(size, 6))
        reference_day = random.randint(10, 200)

    locs = [f"L{i}" for i in range(n_loc)]
    risk_scores = [random.randint(0, 9) for _ in range(n_loc)]

    accounts = []
    for i in range(n_acc):
        accounts.append((
            f"A{i}",
            f"H{i}",
            random.choice(["SAVINGS", "CURRENT"]),
            random.choice(locs),
        ))

    merchants = []
    for i in range(n_mer):
        merchants.append((
            f"M{i}",
            f"CAT{i}",
            random.choice(["LOW", "MEDIUM", "HIGH"]),
        ))

    # Device activity
    devices = []
    for i in range(n_dev):
        aid = f"A{random.randint(0, n_acc - 1)}"
        # sometimes invalid account
        if random.random() < 0.05:
            aid = f"X{random.randint(0, 99)}"
        did = f"D{random.randint(0, max(1, n_dev // 2))}"
        fud = random.randint(-5, reference_day + 50)
        devices.append((f"DL{i}", aid, did, fud))

    statuses = ["SUCCESS", "SUCCESS", "SUCCESS", "FAILED", "PENDING"]
    txns = []
    for i in range(n_txn):
        aid = f"A{random.randint(0, n_acc - 1)}"
        mid = f"M{random.randint(0, n_mer - 1)}"
        did = f"D{random.randint(0, max(1, n_dev // 2))}"
        loc = random.choice(locs)
        day = random.randint(-2, reference_day + 5)
        amt = random.choice([
            random.randint(1, 10000),
            random.randint(1, 10000),
            0,
            -100,
            random.randint(1, 10**9),
        ])
        # occasionally invalid foreign keys
        if random.random() < 0.03:
            aid = f"X{random.randint(0, 50)}"
        if random.random() < 0.03:
            mid = f"M{n_mer + random.randint(0, 10)}"
        if random.random() < 0.03:
            loc = "ZZZ"
        st = random.choice(statuses)
        txns.append((f"T{i}", aid, mid, did, loc, day, amt, st))

    out = []
    out.append(str(reference_day))
    out.append(str(n_acc))
    out.append(str(n_txn))
    out.append(str(n_mer))
    out.append(str(n_dev))
    out.append(str(n_loc))
    for a in accounts:
        out.append(" ".join(map(str, a)))
    for t in txns:
        out.append(" ".join(map(str, t)))
    for m in merchants:
        out.append(" ".join(map(str, m)))
    for d in devices:
        out.append(" ".join(map(str, d)))
    for loc, rs in zip(locs, risk_scores):
        out.append(f"{loc} {rs}")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
