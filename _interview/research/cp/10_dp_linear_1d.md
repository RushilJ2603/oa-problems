# 10 — DP I: Linear / 1D (LIS, Coin Change, House-Robber, 1D Knapsack)

**Placement value:** High (the single most reused OA/interview DP family — fib stairs, rob houses, coin change, subset-sum knapsack, LIS)
**Prereq topics:** Arrays, Recursion/memoization basics, Prefix sums (helpful)

**Pattern in one paragraph:** State lives on a 1D index (position, sum, value, or length). Transitions are local — take/skip the current element, extend from a previous sum by a coin/item, or append to a better prior subsequence. Signal words: "number of ways / min coins to make sum $X$", "max points if adjacent choices conflict", "subset with sum = half / capacity $W$", "longest increasing subsequence". If `dp[i]` only needs `dp[i-1]`, `dp[i-2]`, or a loop over coins/items into a sum array, it belongs here.

## Ladder (easy -> hard, 27 problems)
- [ ] [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) — `LeetCode` `Easy` — fib / ways DP — NeetCode #1 intro to 1D recurrence `dp[i]=dp[i-1]+dp[i-2]`. **(core)**
- [ ] [Frog 1](https://atcoder.jp/contests/dp/tasks/dp_a) — `AtCoder` `DP contest A` — min-cost jump DP — AtCoder Educational DP Contest; first real cost-minimization 1D drill.
- [ ] [House Robber](https://leetcode.com/problems/house-robber/) — `LeetCode` `Medium` — take/skip adjacent — NeetCode / Striver OA classic; template for every "can't pick neighbors" problem. **(core)**
- [ ] [Frog 2](https://atcoder.jp/contests/dp/tasks/dp_b) — `AtCoder` `DP contest B` — jump up to $K$ — AtCoder DP Contest; generalizes Frog 1 to a sliding window of prior states.
- [ ] [Cut Ribbon](https://codeforces.com/problemset/problem/189/A) — `Codeforces` `1300` — unbounded max pieces — A2OJ classic; coin-change style maximize cuts with lengths $a,b,c$. **(core)**
- [ ] [Dice Combinations](https://cses.fi/problemset/task/1633) — `CSES` `Dynamic Programming` — ways with faces 1..6 — CSES / USACO Guide knapsack module focus problem. **(core)**
- [ ] [Vacation](https://atcoder.jp/contests/dp/tasks/dp_c) — `AtCoder` `DP contest C` — 3-choice daily max — AtCoder DP Contest; state = (day, last activity).
- [ ] [Vacations](https://codeforces.com/problemset/problem/698/A) — `Codeforces` `1400` — rest/contest/gym conflicts — CF placement band; same family as House Robber with constrained choices.
- [ ] [House Robber II](https://leetcode.com/problems/house-robber-ii/) — `LeetCode` `Medium` — circular take/skip — NeetCode; reduce circle to two linear House Robber runs.
- [ ] [Minimizing Coins](https://cses.fi/problemset/task/1634) — `CSES` `Dynamic Programming` — unbounded min coins — CSES / USACO Guide; canonical `dp[x]=min(dp[x-c])+1`. **(core)**
- [ ] [Coin Change](https://leetcode.com/problems/coin-change/) — `LeetCode` `Medium` — unbounded min coins — NeetCode / Striver OA staple (same recurrence as Minimizing Coins). **(core)**
- [ ] [Coin Combinations I](https://cses.fi/problemset/task/1635) — `CSES` `Dynamic Programming` — unordered ways — CSES / USACO Guide; outer sum, inner coins → permutations of coins.
- [ ] [Coin Combinations II](https://cses.fi/problemset/task/1636) — `CSES` `Dynamic Programming` — ordered ways — CSES / USACO Guide; outer coins, inner sum → combinations (order fixed).
- [ ] [Boredom](https://codeforces.com/problemset/problem/455/A) — `Codeforces` `1500` — value-axis House Robber — A2OJ / CF classic; freq[v] then `dp[v]=max(dp[v-1], dp[v-2]+v·cnt)`. **(core)**
- [ ] [Delete and Earn](https://leetcode.com/problems/delete-and-earn/) — `LeetCode` `Medium` — value-axis House Robber — NeetCode; LC twin of Boredom — map values → points, then rob.
- [ ] [Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/) — `LeetCode` `Medium` — 0/1 subset-sum — NeetCode / Striver; boolean knapsack to target `sum/2`. **(core)**
- [ ] [Knapsack 1](https://atcoder.jp/contests/dp/tasks/dp_d) — `AtCoder` `DP contest D` — classic 0/1 knapsack — AtCoder Educational DP Contest; weight-indexed max value.
- [ ] [Book Shop](https://cses.fi/problemset/task/1158) — `CSES` `Dynamic Programming` — 0/1 knapsack — CSES / USACO Guide; pages vs price, 1D rolling array. **(core)**
- [ ] [Money Sums](https://cses.fi/problemset/task/1745) — `CSES` `Dynamic Programming` — all achievable sums — CSES / USACO Guide; list every reachable subset sum.
- [ ] [Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) — `LeetCode` `Medium` — LIS $O(n^2)$ / $O(n\log n)$ — NeetCode / Striver interview staple. **(core)**
- [ ] [Increasing Subsequence](https://cses.fi/problemset/task/1145) — `CSES` `Dynamic Programming` — LIS $O(n\log n)$ — CSES / USACO Guide; forces patience-sorting / binary-search tails. **(core)**
- [ ] [Two Sets II](https://cses.fi/problemset/task/1093) — `CSES` `Dynamic Programming` — count partitions — CSES / USACO Guide; knapsack ways to `n(n+1)/4`, divide by 2.
- [ ] [Flowers](https://codeforces.com/problemset/problem/474/D) — `Codeforces` `1700` — linear ways + prefix — white flowers in blocks of $k$; DP + prefix sums for range queries. **(stretch)**
- [ ] [Consecutive Subsequence](https://codeforces.com/problemset/problem/977/F) — `Codeforces` `1700` — map-DP LIS variant — longest consecutive-values subsequence + reconstruct indices. **(stretch)**
- [ ] [Knapsack 2](https://atcoder.jp/contests/dp/tasks/dp_e) — `AtCoder` `DP contest E` — value-dimension knapsack — AtCoder DP Contest; flip state when $W$ is huge but $\sum v$ is small. **(stretch)**
- [ ] [The Values You Can Make](https://codeforces.com/problemset/problem/687/C) — `Codeforces` `1900` — 2D knapsack reachability — USACO Guide; which subset sums are achievable *and* as a sub-subset. **(stretch)**
- [ ] [Subsequences](https://codeforces.com/problemset/problem/597/C) — `Codeforces` `1900` — count LIS of length $k$ — Fenwick/segment over value for DP transitions. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- Write take/skip templates: `dp[i] = max(dp[i-1], dp[i-2] + a[i])` (House Robber / Boredom).
- Unbounded knapsack (coins): loop sum outer or coin outer correctly — know which gives permutations vs combinations.
- 0/1 knapsack: iterate capacity **downward** in a 1D array so each item is used at most once.
- Subset-sum / partition: boolean or count DP to target; watch `sum` odd → impossible for equal partition.
- LIS: both $O(n^2)$ ending-at-$i$ DP and $O(n\log n)$ tails + `lower_bound` (patience sorting).
- Space-optimize fib / rob / frog to $O(1)$ or $O(K)$ previous states when only a window is needed.
- When reconstructing (path / subsequence indices), store `prev[i]` or parent pointers alongside `dp[i]`.
- Flip knapsack dimensions: if weight capacity is $10^9$ but values are small, DP on value and store min weight.

## Where it appears in OAs / interviews
- **Stairs / tickets / days:** "min cost to reach day $n$ buying 1/7/30-day passes" → Frog / Climbing Stairs family (Amazon, Uber).
- **Loot / delete-and-earn:** "max points if taking $x$ deletes $x\pm 1$" → House Robber on a frequency axis (NeetCode → many FAANG screens).
- **Coin / change-making:** "fewest denominations to make amount" or "number of combinations" → unbounded knapsack (nearly every OA bank).
- **Partition / knapsack disguise:** "split array into two teams with equal skill sum" or "max value under budget $W$" → 0/1 knapsack / Partition Equal Subset Sum (Google, Microsoft, product companies).
