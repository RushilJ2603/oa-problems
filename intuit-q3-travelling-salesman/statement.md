# Travelling Salesman

> **Not re-judged here — solve it on an external judge.** Be aware of one thing before you click:
> **LeetCode has no literal TSP problem.** The nearest LeetCode twins are listed above and below and
> use the *identical* `dp[mask][last]` recurrence; the one judge that hands you a plain cost matrix
> and asks for the closed tour is **[AtCoder ABC180 E](https://atcoder.jp/contests/abc180/tasks/abc180_e)**.
> Pick whichever you prefer — the DP you write is the same either way.

You are given `n` cities numbered `0 … n-1` and a cost matrix `cost` where `cost[i][j]` is the cost
of travelling directly from city `i` to city `j`.

Starting from city `0`, visit **every** city **exactly once** and return to city `0`. Return the
**minimum total cost** of such a tour.

## Input format

- The first line contains a single integer `n`, the number of cities.
- The next `n` lines each contain `n` space-separated integers — row `i` of the matrix `cost`.

## Output format

A single integer: the minimum cost of a tour that starts at city `0`, visits every city exactly
once, and returns to city `0`.

## Constraints

- `2 <= n <= 15`
- `0 <= cost[i][j] <= 10^6`, `cost[i][i] = 0`
- The matrix is **not** assumed symmetric — `cost[i][j]` may differ from `cost[j][i]`.

## Example

**Input**
```
4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0
```

**Output**
```
80
```

**Explanation:** the tour `0 → 1 → 3 → 2 → 0` costs `10 + 25 + 30 + 15 = 80`. Every other tour costs
at least as much (`0 → 2 → 3 → 1 → 0` also costs 80; the two are the same cycle walked backwards, and
the matrix here happens to be symmetric).

## What the interviewer is checking

That you recognise it is **NP-hard**, so `n <= 15` is not a coincidence — it is the size at which
`O(2^n · n^2)` becomes the intended answer rather than a fallback.

`dp[mask][i]` = the cheapest way to start at city `0`, visit exactly the set of cities `mask`, and be
standing at city `i` (with `i ∈ mask`). Transition to an unvisited `j` with
`dp[mask | 1<<j][j] = min(dp[mask | 1<<j][j], dp[mask][i] + cost[i][j])`, and the answer is
`min over i of dp[full][i] + cost[i][0]`. That is `2^15 · 15 · 15 ≈ 7.4M` operations.

The wrong answers this question exists to catch are the **nearest-neighbour greedy** (walk to the
closest unvisited city) and plain **permutation enumeration** (`14! ≈ 8.7 × 10^10`). Greedy is fast
and wrong; brute force is right and far too slow. Say that out loud before you write anything.

---

👉 **[LeetCode 943 — Find the Shortest Superstring](https://leetcode.com/problems/find-the-shortest-superstring/)**
(same DP; the "cost" is how much of one word the next one fails to overlap) ·
**[LeetCode 847 — Shortest Path Visiting All Nodes](https://leetcode.com/problems/shortest-path-visiting-all-nodes/)**
(the open-walk variant) ·
**[AtCoder ABC180 E](https://atcoder.jp/contests/abc180/tasks/abc180_e)** (literal closed-tour TSP)
