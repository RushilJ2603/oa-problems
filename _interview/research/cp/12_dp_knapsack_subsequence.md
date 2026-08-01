# 12 — DP III: Knapsack Variants & Subsequence (LCS, Edit Distance, Subset-Sum, Partition)

**Placement value:** High (0/1 / unbounded knapsack, subset-sum, partition, LCS, and edit distance are among the most reused OA / interview DP patterns)
**Prereq topics:** Intro DP / recurrence thinking, 1D & 2D arrays, basic modular arithmetic; bitset optional for stretch

**Pattern in one paragraph:** Treat choices as filling a capacity (weight / sum / time) or aligning two sequences. Knapsack / subset-sum / partition: `dp[w]` = best value, reachability, or number of ways with capacity `w`, updating **backward** for 0/1 and **forward** for unbounded; swap the DP dimension when `W` is huge but values are small. Subsequence string DP: `dp[i][j]` on prefixes of two strings — match/skip for LCS, insert/delete/replace for edit distance, consume both or one for interleaving / distinct subsequences. Spot it when you see “maximum value under a budget”, “can you make sum / split equally”, “longest common …”, or “minimum operations to transform”.

## Ladder (easy -> hard, 24 problems)
- [ ] [Minimizing Coins](https://cses.fi/problemset/task/1634) — `CSES` `Dynamic Programming` — unbounded knapsack (min coins) — USACO Guide / CSES focus problem; identical pattern to LeetCode Coin Change. (core)
- [ ] [Coin Combinations I](https://cses.fi/problemset/task/1635) — `CSES` `Dynamic Programming` — unbounded count (order matters) — CSES / USACO Guide; teaches the “outer capacity, inner coin” loop. (core)
- [ ] [Coin Combinations II](https://cses.fi/problemset/task/1636) — `CSES` `Dynamic Programming` — unbounded count (combinations) — CSES / USACO Guide; loop-order twin of I; OA classic. (core)
- [ ] [Cut Ribbon](https://codeforces.com/problemset/problem/189/A) — `Codeforces` `1300` — unbounded knapsack (maximize pieces) — Famous A2OJ ladder intro to “max pieces with lengths a,b,c”. (core)
- [ ] [Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/) — `LeetCode` `Medium` — 0/1 subset-sum / partition — NeetCode / Striver signature OA problem; reduce to subset sum of `total/2`. (core)
- [ ] [Knapsack 1](https://atcoder.jp/contests/dp/tasks/dp_d) — `AtCoder` `Educational DP` — classical 0/1 knapsack — AtCoder DP Contest D; the template everyone memorizes. (core)
- [ ] [Book Shop](https://cses.fi/problemset/task/1158) — `CSES` `Dynamic Programming` — 0/1 knapsack (max pages) — CSES / USACO Guide; space-optimized 1D backward update. (core)
- [ ] [Money Sums](https://cses.fi/problemset/task/1745) — `CSES` `Dynamic Programming` — subset-sum reachability — CSES / USACO Guide; list all achievable sums. (core)
- [ ] [Target Sum](https://leetcode.com/problems/target-sum/) — `LeetCode` `Medium` — count subsets with signed sum — NeetCode / Striver; algebra → count subsets summing to `(sum+target)/2`.
- [ ] [Two Sets II](https://cses.fi/problemset/task/1093) — `CSES` `Dynamic Programming` — partition counting — CSES / USACO Guide; ways to split `1..n` into equal sums (mod `10^9+7`). (core)
- [ ] [Knapsack 2](https://atcoder.jp/contests/dp/tasks/dp_e) — `AtCoder` `Educational DP` — knapsack with value as state — AtCoder DP Contest E; when `W` is huge, minimize weight for each value. (core)
- [ ] [Ones and Zeroes](https://leetcode.com/problems/ones-and-zeroes/) — `LeetCode` `Medium` — 2D 0/1 knapsack — Striver classic; two capacities (zeros & ones) at once.
- [ ] [Palindrome Basis](https://codeforces.com/problemset/problem/1673/C) — `Codeforces` `1500` — unbounded knapsack on filtered coins — Count ways using only palindromic summands; clean CF placement drill.
- [ ] [Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/) — `LeetCode` `Medium` — LCS length — NeetCode / Striver OA staple; the base 2-string DP. (core)
- [ ] [LCS](https://atcoder.jp/contests/dp/tasks/dp_f) — `AtCoder` `Educational DP` — LCS reconstruction — AtCoder DP Contest F; recover one actual LCS string, not only length. (core)
- [ ] [Edit Distance](https://cses.fi/problemset/task/1639) — `CSES` `Dynamic Programming` — Levenshtein DP — CSES (= LeetCode 72); insert / delete / replace transitions. (core)
- [ ] [Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/) — `LeetCode` `Hard` — count ways `t` forms from `s` — NeetCode subsequence-counting milestone.
- [ ] [Make Them Equal](https://codeforces.com/problemset/problem/1633/D) — `Codeforces` `1600` — BFS distances + 0/1 knapsack — Precompute op costs, then knapsack under budget `k`; strong placement CF C.
- [ ] [Baby Ehab Partitions Again](https://codeforces.com/problemset/problem/1516/C) — `Codeforces` `1700` — partition + constructive — CF twist on equal-sum partition: remove the minimum elements to break it.
- [ ] [The Values You Can Make](https://codeforces.com/problemset/problem/687/C) — `Codeforces` `1900` — nested subset-sum DP — USACO Guide knapsack list; all `x` achievable inside a subset summing to `k`. (stretch)
- [ ] [Dima and Salad](https://codeforces.com/problemset/problem/366/C) — `Codeforces` `1900` — knapsack on signed difference — Classic “taste − k·calories = 0” offset-knapsack. (stretch)
- [ ] [Modulo Sum](https://codeforces.com/problemset/problem/577/B) — `Codeforces` `1900` — subset-sum modulo `m` — Pigeonhole + DP; yes if some nonempty subsequence ≡ 0 (mod `m`). (stretch)
- [ ] [Fire](https://codeforces.com/problemset/problem/864/E) — `Codeforces` `2000` — knapsack with deadlines — Sort by burn time, then 0/1 knapsack with path recovery. (stretch)
- [ ] [Round Subset](https://codeforces.com/problemset/problem/837/D) — `Codeforces` `2100` — 2D knapsack on factors — USACO Guide; maximize trailing zeros via counts of 2s and 5s. (stretch)

## Must-internalize checklist (5-10 bullets)
- Write 0/1 knapsack in `O(nW)` with a 1D array updated **descending** so each item is used at most once.
- Write unbounded knapsack / coin DP with a 1D array updated **ascending**; know when order-of-loops counts combinations vs permutations.
- Reduce partition / Target Sum / Last-Stone-style problems to “does a subset sum to `T`?” (or count such subsets).
- Flip the state when capacity is huge: `dp[value] = min weight` (AtCoder Knapsack 2 pattern).
- Code LCS length and (on demand) reconstruct the string by backtracking parents.
- Code edit distance: `dp[i][j] = dp[i-1][j-1]` on match, else `1 + min(insert, delete, replace)`.
- Recognize 2-capacity knapsacks (Ones and Zeroes) and difference-offset knapsacks (Dima and Salad).
- Know bitset `dp |= dp << w` as a fast subset-sum reachability trick when only yes/no matters.

## Where it appears in OAs / interviews
- **Budget / resource selection:** “Pick projects / courses / items under a cost cap to maximize score” → straight 0/1 knapsack (Book Shop / Knapsack 1).
- **Equal split / fair division:** “Can you split the array into two teams with equal strength?” → Partition Equal Subset Sum; often with a twist (remove one element, minimize difference).
- **Change-making / ways to pay:** “Minimum coins” or “number of ways to make amount” → Coin Change / CSES coin trio; loop-order bugs are a common reject reason.
- **String transform / alignment:** “Minimum edits to turn A into B”, “longest common subsequence of two logs”, “number of ways S generates T as a subsequence” → Edit Distance / LCS / Distinct Subsequences disguised as product or DNA strings.
