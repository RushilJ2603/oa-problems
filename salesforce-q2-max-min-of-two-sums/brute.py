"""Independent solution.

reference.cpp keeps totA in the state and maximises totB. This one is the MIRROR: it keeps totB in
the state and maximises totA, and it walks the table forward rather than with a descending 0/1 sweep
(a fresh layer per item instead of an in-place reverse loop). An asymmetry bug or an off-by-one in
the knapsack sweep shows up as a disagreement rather than being reproduced identically.

For small instances it skips the DP entirely and enumerates every C(n, k) subset, which assumes
nothing at all.
"""
import itertools
import math
import sys


def exhaustive(n, k, a, b):
    best = 0
    for combo in itertools.combinations(range(n), k):
        ta = sum(a[i] for i in combo)
        tb = sum(b[i] for i in combo)
        v = ta if ta < tb else tb
        if v > best:
            best = v
    return best


def mirrored_dp(n, k, a, b):
    SB = sum(b)
    NEG = -1
    # dp[j][t] = largest totA using exactly j indices whose totB is exactly t
    dp = [[NEG] * (SB + 1) for _ in range(k + 1)]
    dp[0][0] = 0
    for i in range(n):
        ai, bi = a[i], b[i]
        nxt = [row[:] for row in dp]          # fresh layer, no in-place reverse sweep
        for j in range(min(i, k - 1), -1, -1):
            cur = dp[j]
            tgt = nxt[j + 1]
            for t in range(SB - bi + 1):
                if cur[t] < 0:
                    continue
                cand = cur[t] + ai
                if cand > tgt[t + bi]:
                    tgt[t + bi] = cand
        dp = nxt
    best = 0
    for t in range(SB + 1):
        if dp[k][t] < 0:
            continue
        v = t if t < dp[k][t] else dp[k][t]
        if v > best:
            best = v
    return best


def main() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    k = int(data[1])
    a = [int(x) for x in data[2:2 + n]]
    b = [int(x) for x in data[2 + n:2 + 2 * n]]

    if math.comb(n, k) <= 200000:
        print(exhaustive(n, k, a, b))
    else:
        print(mirrored_dp(n, k, a, b))


main()
