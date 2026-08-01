# 11 — DP II: Grid DP & Interval DP

**Placement value:** High (Extremely common in OAs, especially path-finding grids and substring palindromes)
**Prereq topics:** DP I (1D DP, Knapsack), Prefix Sums
**Pattern in one paragraph:** Grid DP involves navigating a 2D matrix (usually moving right/down) where the state `dp[r][c]` depends on adjacent cells, often tracking min/max path sum or combinations. Interval DP (or Range DP) operates on subarrays/substrings, where the state `dp[L][R]` relies on strictly smaller intervals like `dp[L+1][R]` or `dp[L][k] + dp[k+1][R]`. You recognize Interval DP when you must merge adjacent elements, partition an array, or solve palindrome/game-theory questions on a substring, meaning you process intervals ordered by length from shortest to longest.

## Ladder (easy -> hard, ~23 problems)
- [ ] [Unique Paths](https://leetcode.com/problems/unique-paths/) — LeetCode Medium — Grid DP — The "Hello World" of grid DP, foundational for counting paths. **(core)**
- [ ] [Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/) — LeetCode Medium — Grid DP — Standard shortest path DP on a grid, identical to OA questions. **(core)**
- [ ] [Triangle](https://leetcode.com/problems/triangle/) — LeetCode Medium — Grid DP — Jagged grid DP, teaches bottom-up optimization for triangular DAGs. **(core)**
- [ ] [Grid Paths](https://cses.fi/problemset/task/1638) — CSES Medium — Grid DP — Codeforces/CSES classic for counting paths with obstacles. **(core)**
- [ ] [Grid 1](https://atcoder.jp/contests/dp/tasks/dp_h) — AtCoder Medium — Grid DP — The AtCoder DP contest standard for 2D combinations with obstacles. **(core)**
- [ ] [Minimum Falling Path Sum](https://leetcode.com/problems/minimum-falling-path-sum/) — LeetCode Medium — Grid DP — 3-way transition DP, extremely common in Amazon/Microsoft OAs. **(core)**
- [ ] [Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/) — LeetCode Medium — Interval DP — The most fundamental intro to Interval DP, building solutions from shorter substrings. **(core)**
- [ ] [Deque](https://atcoder.jp/contests/dp/tasks/dp_l) — AtCoder Medium — Interval DP — Canonical minimax interval DP game from the AtCoder Educational DP contest. **(core)**
- [ ] [Removal Game](https://cses.fi/problemset/task/1097) — CSES Medium — Interval DP — Identical to LC Stone Game, teaches the state `dp[L][R]` for zero-sum games. **(core)**
- [ ] [Clear the String](https://codeforces.com/problemset/problem/1132/F) — Codeforces 1600 — Interval DP — Classic problem on merging adjacent identical characters, famous in CF. **(core)**
- [ ] [Zuma](https://codeforces.com/problemset/problem/607/B) — Codeforces 1600 — Interval DP — CF staple on destroying palindromic subsegments. **(stretch)**
- [ ] [Working out](https://codeforces.com/problemset/problem/429/B) — Codeforces 1600 — Grid DP — Teaches how to compute and combine multiple DP grids from different starting corners. **(core)**
- [ ] [The Sports Festival](https://codeforces.com/problemset/problem/1509/C) — Codeforces 1600 — Interval DP — Excellent rating-builder for interval DP on sorted arrays. **(core)**
- [ ] [Slimes](https://atcoder.jp/contests/dp/tasks/dp_n) — AtCoder Medium — Interval DP — The standard Matrix Chain Multiplication (MCM) pattern using prefix sums. **(core)**
- [ ] [Minimum Score Triangulation of Polygon](https://leetcode.com/problems/minimum-score-triangulation-of-polygon/) — LeetCode Medium — Interval DP — Teaches how to pick a middle element `k` to split the interval `[i, j]`. **(stretch)**
- [ ] [Zero Path](https://codeforces.com/problemset/problem/1695/C) — Codeforces 1700 — Grid DP — Requires tracking reachable max/min sums in a bipartite grid, great for rating. **(stretch)**
- [ ] [Array Shrinking](https://codeforces.com/problemset/problem/1312/E) — Codeforces 1700 — Interval DP — Complex interval merging logic, highly recommended in CP-31. **(stretch)**
- [ ] [The least round way](https://codeforces.com/problemset/problem/2/B) — Codeforces 1700 — Grid DP — Requires 3D DP / tuple states to track factors of 2 and 5, classic CF milestone. **(stretch)**
- [ ] [Queries for Number of Palindromes](https://codeforces.com/problemset/problem/245/H) — Codeforces 1800 — Interval DP — 2D prefix sums over a boolean interval DP table to answer range queries. **(stretch)**
- [ ] [Dungeon Game](https://leetcode.com/problems/dungeon-game/) — LeetCode Hard — Grid DP — Forces bottom-up thinking because forward state is insufficient to guarantee survival. **(stretch)**
- [ ] [Minimum Cost to Cut a Stick](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/) — LeetCode Hard — Interval DP — MCM pattern with a twist, frequently tested in high-tier company OAs. **(stretch)**
- [ ] [Burst Balloons](https://leetcode.com/problems/burst-balloons/) — LeetCode Hard — Interval DP — The hardest standard MCM variation where the subproblems depend on the boundary. **(stretch)**
- [ ] [Cherry Pickup II](https://leetcode.com/problems/cherry-pickup-ii/) — LeetCode Hard — Grid DP — Multi-agent grid DP tracking two simultaneous paths, strong test of state design. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- Write standard 2D Grid DP using `dp[r][c]` and checking `(r-1, c)` and `(r, c-1)` boundaries cleanly.
- Optimize Grid DP from `O(N*M)` space to `O(M)` space by only keeping the previous row.
- Loop over interval lengths `length = 2...N` and then start index `L = 0...(N - length)`, establishing `R = L + length - 1`.
- Write Matrix Chain Multiplication (MCM) DP loops: `for L, for R, for k in L...R-1`.
- Know how to evaluate `dp[L][R]` as a zero-sum game by taking `max(val[L] - dp[L+1][R], val[R] - dp[L][R-1])`.
- Process palindromic DP optimally by matching ends `if S[L] == S[R]: dp[L][R] = dp[L+1][R-1] + ...`.
- Recognize that when multiple grid agents move simultaneously, `r1 + c1 = r2 + c2 = step` cuts a dimension from the state space.

## Where it appears in OAs / interviews
- **Robot navigation / Game boards:** "A robot moves right/down to collect max coins" is just basic Grid DP. (Very common at Amazon / Citadel).
- **Array partitioning / Merging:** "You can merge adjacent slimes/stones for a cost equal to their sum. Find min cost to merge all." This is pure Interval DP (MCM pattern).
- **String Palindromes:** "Find the longest palindromic subsequence" or "Min insertions to make string palindrome" (common at Google, Microsoft).
- **Turn-based games:** "Two players pick items from the ends of an array, assuming optimal play." This screams `dp[L][R]` minimax interval DP.
