"""Independent solution.

reference.cpp leans on the insight that the powers-of-two part of the answer is exactly popcount of
the remainder, and only enumerates the ten factorials that are NOT powers of two. This one assumes
neither: it builds the plain SET of magical values (so 1 and 2 collapse to one entry each, which is
where a distinctness bug would hide) and searches it directly.

  n small  -> 0/1 knapsack over the value set, dp[s] = fewest distinct magical numbers summing to s
  n large  -> exhaustive DFS over the ~40 values, largest first, pruned by the best answer so far and
              by the suffix sum still available
"""
import sys


def magical_values(n):
    vals = set()
    p = 1
    while p <= n:
        vals.add(p)
        p *= 2
    f, a = 1, 1
    while f <= n:
        vals.add(f)
        a += 1
        f *= a
    return sorted(vals)


def knapsack(n, vals):
    INF = float("inf")
    dp = [INF] * (n + 1)
    dp[0] = 0
    for v in vals:                       # each value offered once
        for s in range(n, v - 1, -1):
            if dp[s - v] + 1 < dp[s]:
                dp[s] = dp[s - v] + 1
    return -1 if dp[n] == INF else dp[n]


def dfs_search(n, vals):
    vals = sorted(vals, reverse=True)
    m = len(vals)
    suffix = [0] * (m + 1)
    for i in range(m - 1, -1, -1):
        suffix[i] = suffix[i + 1] + vals[i]

    best = [float("inf")]

    def go(i, remaining, count):
        if remaining == 0:
            if count < best[0]:
                best[0] = count
            return
        if i >= m or count + 1 >= best[0]:
            return
        if remaining > suffix[i]:
            return
        if vals[i] <= remaining:
            go(i + 1, remaining - vals[i], count + 1)
        go(i + 1, remaining, count)

    go(0, n, 0)
    return -1 if best[0] == float("inf") else best[0]


def main() -> None:
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    out = []
    for i in range(1, t + 1):
        n = int(data[i])
        vals = magical_values(n)
        out.append(str(knapsack(n, vals) if n <= 200000 else dfs_search(n, vals)))
    print("\n".join(out))


main()
