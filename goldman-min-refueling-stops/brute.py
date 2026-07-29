#!/usr/bin/env python3
# Independent O(n^2) DP (different method from the reference's greedy heap):
# dp[t] = the farthest distance reachable using exactly t stops. Process stations in order; a station
# at pos with fuel can be the t-th stop iff some (t-1)-stop plan already reaches pos. The answer is the
# smallest t whose reach >= target.
import sys


def solve(target, start, stations):
    stations = sorted(stations)
    n = len(stations)
    dp = [start] + [0] * n            # dp[t] = max distance with t stops
    for pos, fuel in stations:
        for t in range(n, 0, -1):     # reverse so each station is used at most once
            if dp[t - 1] >= pos and dp[t - 1] + fuel > dp[t]:
                dp[t] = dp[t - 1] + fuel
    for t in range(n + 1):
        if dp[t] >= target:
            return t
    return -1


def main():
    data = sys.stdin.buffer.read().split()
    idx = 0
    target = int(data[idx]); start = int(data[idx + 1]); idx += 2
    n = int(data[idx]); idx += 1
    stations = []
    for _ in range(n):
        stations.append((int(data[idx]), int(data[idx + 1]))); idx += 2
    print(solve(target, start, stations))


main()
