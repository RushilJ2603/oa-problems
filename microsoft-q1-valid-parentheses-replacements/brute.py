#!/usr/bin/env python3
# Independent DP cross-check (different method from the reference greedy).
# For each ')' we branch: keep it (balance-1, allowed only if balance stays >=0) or
# upgrade it to "()" (balance unchanged, cost +1). dp maps reachable balance -> min
# upgrades to get there with every prefix >= 0. Feasible iff balance 0 is reachable
# at the end using <= k upgrades.
import sys


def solve(s, k):
    dp = {0: 0}  # balance -> min upgrades used
    for c in s:
        nxt = {}
        if c == '(':
            for b, u in dp.items():
                nb = b + 1
                if nb not in nxt or u < nxt[nb]:
                    nxt[nb] = u
        else:  # ')'
            for b, u in dp.items():
                if b - 1 >= 0:                       # keep as ')'
                    nb = b - 1
                    if nb not in nxt or u < nxt[nb]:
                        nxt[nb] = u
                nb2, u2 = b, u + 1                    # upgrade to "()"
                if nb2 not in nxt or u2 < nxt[nb2]:
                    nxt[nb2] = u2
        dp = nxt
        if not dp:
            return 0
    return 1 if (0 in dp and dp[0] <= k) else 0


def main():
    data = sys.stdin.read().split()
    s = data[0]
    k = int(data[1])
    print(solve(s, k))


main()
