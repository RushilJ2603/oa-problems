#!/usr/bin/env python3
"""Generate one random valid input. CLI: python3 generator.py <seed> <size>"""
import random
import sys

DAY = 86400


def main():
    random.seed(int(sys.argv[1]))
    size = int(sys.argv[2]) if len(sys.argv) > 2 else 10

    if size >= 80:
        n = 100
        m = 100
    elif size >= 40:
        n = min(100, max(10, size // 2))
        m = min(100, size)
    else:
        n = random.randint(1, max(1, min(10, size)))
        m = random.randint(1, max(1, min(20, size * 2)))

    balances = [random.randint(0, 10**5) for _ in range(n)]
    # Work on a shadow copy so we emit mostly-valid sequences (invalid cases still useful)
    shadow = balances[:]

    print(n)
    print(" ".join(map(str, balances)))
    print(m)

    t = 0
    pending_cb = []  # (due, holder_idx0, amt) for shadow sim
    for i in range(m):
        # advance time; occasionally jump by a full day so cashbacks land
        if size >= 80:
            gap = random.randint(1, DAY // 2)
        else:
            gap = random.choice([1, 2, 10, 100, DAY - 1, DAY, DAY + 1, random.randint(1, 5000)])
        t += gap
        if t > 2 * 10**9:
            t = 2 * 10**9 - (m - i)

        # apply due cashbacks on shadow
        still = []
        for due, j, a in pending_cb:
            if due <= t:
                shadow[j] += a
            else:
                still.append((due, j, a))
        pending_cb = still

        # choose account: usually valid, sometimes invalid
        if random.random() < 0.08:
            h = random.choice([0, n + 1, -1, n + 5])
            op = random.choice(["deposit", "withdraw"])
            amt = random.randint(0, 10**5)
            print(f"{op} {t} {h} {amt}")
            # after invalid, remaining requests still printed (gate only needs valid input format)
            # but shadow stops updating meaningfully — keep generating syntactically valid lines
            continue

        h = random.randint(1, n)
        j = h - 1
        if random.random() < 0.55 and shadow[j] > 0:
            op = "withdraw"
            # mix: exact balance, overdraft, partial
            r = random.random()
            if r < 0.1:
                amt = shadow[j] + random.randint(1, 1000)
            elif r < 0.2:
                amt = shadow[j]
            else:
                amt = random.randint(0, shadow[j])
            print(f"{op} {t} {h} {amt}")
            if amt <= shadow[j]:
                shadow[j] -= amt
                pending_cb.append((t + DAY, j, (amt * 2) // 100))
        else:
            op = "deposit"
            amt = random.randint(0, 10**5)
            print(f"{op} {t} {h} {amt}")
            shadow[j] += amt


if __name__ == "__main__":
    main()
