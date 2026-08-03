#!/usr/bin/env python3
"""Deterministic generator: python3 generator.py <seed> <size>"""
import random
import sys

HOLDERS = ["Alice", "Bob", "Charu", "Dev", "Esha", "Farhan", "Gita", "Hari", "Isha", "Jai",
           "Kiran", "Lata", "Manoj", "Neha", "Omar"]
TYPES = ["SAVINGS", "CURRENT"]
CATS = ["FOOD", "CRYPTO", "RETAIL", "TRAVEL", "GAMING"]
TIERS = ["LOW", "MEDIUM", "HIGH"]
STATUSES = ["SUCCESS", "FAILED", "PENDING", "success"]

# Practical OA bounds used by this package
MAX_ACC, MAX_TXN, MAX_MER, MAX_DEV, MAX_LOC = 5000, 10000, 2000, 5000, 2000


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 800:
        n_acc, n_txn, n_mer, n_dev, n_loc = MAX_ACC, MAX_TXN, MAX_MER, MAX_DEV, MAX_LOC
    elif size >= 400:
        n_acc = min(MAX_ACC, 800)
        n_txn = min(MAX_TXN, 2000)
        n_mer = min(MAX_MER, 400)
        n_dev = min(MAX_DEV, 800)
        n_loc = min(MAX_LOC, 400)
    elif size >= 150:
        n_acc = max(2, min(200, size))
        n_txn = max(0, min(400, size * 2))
        n_mer = max(1, min(100, size // 2))
        n_dev = max(0, min(200, size))
        n_loc = max(1, min(100, size // 2))
    else:
        n_acc = max(2, min(80, size + 1))
        n_txn = max(0, min(160, size * 2))
        n_mer = max(1, min(40, max(1, size)))
        n_dev = max(0, min(80, size))
        n_loc = max(1, min(30, max(1, size)))

    reference_day = random.randint(1, max(1, min(1000000, size * 100 + 10)))

    out = []
    out.append(str(reference_day))
    out.append(str(n_acc))
    out.append(str(n_txn))
    out.append(str(n_mer))
    out.append(str(n_dev))
    out.append(str(n_loc))

    acc_ids = [f"A{i+1}" for i in range(n_acc)]
    loc_ids = [f"L{i+1}" for i in range(n_loc)]
    mer_ids = [f"M{i+1}" for i in range(n_mer)]
    bogus_acc = [f"AX{i}" for i in range(5)]
    bogus_mer = [f"MX{i}" for i in range(5)]
    bogus_loc = [f"LZZ{i}" for i in range(3)]

    for i, aid in enumerate(acc_ids):
        out.append(f"{aid} {HOLDERS[i % len(HOLDERS)]}{i % 9} {TYPES[i % 2]} {loc_ids[i % n_loc]}")

    for i in range(n_txn):
        tid = f"T{i+1}"
        r = random.random()
        if r < 0.7:
            aid = acc_ids[random.randrange(n_acc)]
            mid = mer_ids[random.randrange(n_mer)]
            loc = loc_ids[random.randrange(n_loc)]
            day = random.randint(1, max(1, reference_day))
            amount = random.randint(1, 5000)
            status = "SUCCESS"
        else:
            aid = random.choice(acc_ids + bogus_acc)
            mid = random.choice(mer_ids + bogus_mer)
            loc = random.choice(loc_ids + bogus_loc)
            day = random.randint(-5, reference_day + 5)
            amount = random.choice([0, -1, random.randint(1, 10**9)])
            status = random.choice(STATUSES)
        did = f"D{random.randint(1, max(3, min(2000, n_dev // 2 + 1)))}"
        out.append(f"{tid} {aid} {mid} {did} {loc} {day} {amount} {status}")

    for mid in mer_ids:
        out.append(f"{mid} {random.choice(CATS)} {random.choice(TIERS)}")

    for i in range(n_dev):
        act = f"V{i+1}"
        aid = random.choice(acc_ids + bogus_acc)
        did = f"D{random.randint(1, max(3, min(2000, n_dev // 2 + 1)))}"
        day = random.randint(-3, reference_day + 10)
        out.append(f"{act} {aid} {did} {day}")

    for loc in loc_ids:
        out.append(f"{loc} {random.randint(0, 10)}")

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
