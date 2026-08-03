import sys


def solve(reference_day, accounts, txns, merchants, devices, locations):
    # WRITE YOUR CODE HERE
    return "NA"


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    p = 0

    def nxt():
        nonlocal p
        v = data[p]
        p += 1
        return v

    reference_day = int(nxt())
    n_acc = int(nxt())
    n_txn = int(nxt())
    n_mer = int(nxt())
    n_dev = int(nxt())
    n_loc = int(nxt())

    accounts = []
    for _ in range(n_acc):
        accounts.append((nxt(), nxt(), nxt(), nxt()))

    txns = []
    for _ in range(n_txn):
        txns.append((nxt(), nxt(), nxt(), nxt(), nxt(), int(nxt()), int(nxt()), nxt()))

    merchants = []
    for _ in range(n_mer):
        merchants.append((nxt(), nxt(), nxt()))

    devices = []
    for _ in range(n_dev):
        devices.append((nxt(), nxt(), nxt(), int(nxt())))

    locations = []
    for _ in range(n_loc):
        locations.append((nxt(), int(nxt())))

    print(solve(reference_day, accounts, txns, merchants, devices, locations))


if __name__ == "__main__":
    main()
