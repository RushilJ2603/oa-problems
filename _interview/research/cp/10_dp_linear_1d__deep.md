# 10 — DP I: Linear / 1D (Depth Pass)

**Placement value:** High (second wave of CF-style 1D DP after frog/rob/coins/LIS/knapsack templates — Div2 C–D “state on index/value” contests)
**Prereq topics:** Base linear DP ladder (take/skip, unbounded/0-1 knapsack, LIS $O(n\log n)$); prefix sums; light number theory (divisors) for a few items

**Pattern in one paragraph:** Same engine as the standard ladder — `dp[i]` / `dp[sum]` / `dp[value]` with local transitions — but statements hide the axis: recolor so neighbors differ, fall trees left/right, decode `n`/`u` runs like Climbing Stairs, LIS only along multiples, knapsack on BFS distances, ways with a “at least one long edge” constraint, or partition an array into three equal-sum pieces. Recognize it when a left-to-right (or value-sorted) scan has optimal substructure and $n\cdot(\text{small state})$ or $n\sqrt{A}$ fits.

## Ladder (easy -> hard, 24 problems)
- [ ] [Basketball Exercise](https://codeforces.com/problemset/problem/1195/C) — `Codeforces` `1400` — 2-row Vacation / take-skip — Height from row 1 or 2, never same row twice; twin of AtCoder Vacation with only two activities. **(core)**
- [ ] [Constanze's Machine](https://codeforces.com/problemset/problem/1245/C) — `Codeforces` `1400` — fib / decode-ways on runs — `m`/`w` forbidden; runs of `n`/`u` contribute Fibonacci ways. **(core)**
- [ ] [Orac and Models](https://codeforces.com/problemset/problem/1350/B) — `Codeforces` `1400` — LIS on multiples — `dp[i]=1+max dp[j]` over $j\mid i$; divisor-chain LIS, not value-LIS. **(core)**
- [ ] [Mashmokh and ACM](https://codeforces.com/problemset/problem/414/B) — `Codeforces` `1400` — sequences with divisibility — `dp[len][val]` += from divisors; classic counting 1D×length DP. **(core)**
- [ ] [Journey Planning](https://codeforces.com/problemset/problem/1320/A) — `Codeforces` `1400` — group by $a_i-i$ — Beauty is constant on $a_i-i$; map-sum, not full LIS. **(core)**
- [ ] [Diverse Garland](https://codeforces.com/problemset/problem/1108/D) — `Codeforces` `1400` — recolor adjacent — Min changes so no two neighbors match; 3-state DP or greedy recolor. **(core)**
- [ ] [I Hate 1111](https://codeforces.com/problemset/problem/1526/B) — `Codeforces` `1400` — unbounded “coins” 1,11,111,… — Reachability with numbers of form $(10^k-1)/9$; DP or math cutoff. **(core)**
- [ ] [Woodcutters](https://codeforces.com/problemset/problem/545/C) — `Codeforces` `1500` — fall L/R/stay — Greedy left-first with position occupancy; House-Robber geometry. **(core)**
- [ ] [Mortal Kombat Tower](https://codeforces.com/problemset/problem/1418/C) — `Codeforces` `1500` — skip-budget take/skip — You/friend alternate; friend kills 1–2 bosses; `dp[i][whose_turn]`. **(core)**
- [ ] [Tetrahedron](https://codeforces.com/problemset/problem/166/E) — `Codeforces` `1500` — ways on 4 states — Steps on a tetrahedron ending at D; collapse to `at_D` / `not_D` recurrence. **(core)**
- [ ] [Bubble Sort Graph](https://codeforces.com/problemset/problem/340/D) — `Codeforces` `1500` — LIS as DAG width — Longest path in “can stay after one bubble pass” = LIS; forces $O(n\log n)$.
- [ ] [Array Description](https://cses.fi/problemset/task/1746) — `CSES` `Dynamic Programming` — adjacent $|x_i-x_{i+1}|\le 1$ — Fill zeros under band constraint; rolling `dp[pos][val]`. **(core)**
- [ ] [k-Tree](https://codeforces.com/problemset/problem/431/C) — `Codeforces` `1600` — path-weight ways + threshold — Ways to sum $n$ with edges $1..k$, subtract/complement those with no edge $\ge d$. **(core)**
- [ ] [Hard problem](https://codeforces.com/problemset/problem/706/C) — `Codeforces` `1600` — reverse-or-not chain — Cost to make strings non-decreasing by optional reverse; two states per index. **(core)**
- [ ] [Make Them Equal](https://codeforces.com/problemset/problem/1633/D) — `Codeforces` `1600` — BFS distance + 0/1 knapsack — Op-cost to raise $1\to b_i$ via $x+\lfloor x/y\rfloor$; then knapsack under budget. **(core)**
- [ ] [DZY Loves Sequences](https://codeforces.com/problemset/problem/446/A) — `Codeforces` `1600` — LIS with one edit — Left/right strict-increasing runs; merge across one change.
- [ ] [Candies](https://atcoder.jp/contests/dp/tasks/dp_m) — `AtCoder` `DP contest M` — bounded sum ways + prefix — Distribute $K$ candies with caps $a_i$; range-sum transitions in $O(NK)$. **(stretch)**
- [ ] [Number of Ways](https://codeforces.com/problemset/problem/466/C) — `Codeforces` `1700` — 3 equal-sum cuts — Prefix $=S/3$ then $=2S/3$; count pairs of cuts. **(stretch)**
- [ ] [Caesar's Legions](https://codeforces.com/problemset/problem/118/D) — `Codeforces` `1700` — place with run caps — `dp[n1][n2][last][run]`; small state, careful bounds. **(stretch)**
- [ ] [Sleeping Schedule](https://codeforces.com/problemset/problem/1324/E) — `Codeforces` `1700` — modular hour DP — Sleep $a_i$ or $a_i-1$; count hours in $[l,r]$ mod $h$. **(stretch)**
- [ ] [George and Job](https://codeforces.com/problemset/problem/467/C) — `Codeforces` `1700` — choose $k$ length-$m$ segments — Prefix sums + `dp[i][taken]`; classic segment knapsack. **(stretch)**
- [ ] [Make The Fence Great Again](https://codeforces.com/problemset/problem/1221/D) — `Codeforces` `1800` — raise heights, adjacent ≠ — Only need $+0/+1/+2$ per post; 3-state rolling DP. **(stretch)**
- [ ] [Modulo Sum](https://codeforces.com/problemset/problem/577/B) — `Codeforces` `1900` — subset sum mod $m$ — If $n\ge m$ pigeonhole; else 0/1 knapsack on residues. **(stretch)**
- [ ] [Red-Green Towers](https://codeforces.com/problemset/problem/478/D) — `Codeforces` `2000` — height knapsack — Max height $h$ with $h(h+1)/2\le r+g$; DP ways over rows. **(stretch)**

## Must-internalize checklist (technique notes)
- **Rewrite the axis:** Boredom/Delete-and-Earn style — DP on *value*, not index — also powers Orac (multiples of index) and Journey Planning ($a_i-i$ buckets).
- **Fibonacci on runs:** Constanze / Decode Ways — if a block of identical letters has length $L$, ways $=F_{L+1}$; multiply independent blocks; abort on forbidden letters.
- **Two states beat full history:** Hard problem / Fence / Garland / Basketball — keep only “last choice” (reversed?, color, row, height-offset); never store the whole string.
- **Complement counting (k-Tree):** often easier to compute all paths of weight $n$, then subtract (or parallel-DP) paths that never use an edge $\ge d$.
- **Precompute transition costs:** Make Them Equal — BFS once from 1 for all op-distances up to $\max b_i$, then one 0/1 knapsack; do not Dijkstra per test.
- **Prefix for range transitions:** Candies / George and Job — `dp[i][s]` needs a sum of previous `dp[i-1][s-x]`; maintain prefix so each state is $O(1)$.
- **Pigeonhole before knapsack:** Modulo Sum — $n\ge m$ ⇒ some nonempty subset $\equiv 0\pmod m$; only run $O(nm)$ residue DP when $n<m$.
- **Local height/raise tricks:** Fence Great Again — proving $+0..+2$ suffices collapses an infinite raise space to 3 layers per index.

## Where it appears in OAs / interviews
- **Decode / keyboard / broken keys:** “number of ways to type a string when `nn` can be one or two presses” → Constanze / Climbing Stairs family (Meta/Amazon OA clones).
- **Adjacent constraint coloring:** “recolor minimum so no two neighbors share a type” → Diverse Garland / House-Robber-with-colors.
- **Budgeted upgrades:** “each item needs `ops[i]` upgrades, total ops ≤ $k$, maximize value” → Make Them Equal pattern (BFS/metric + knapsack).
- **Equal split / payroll:** “split array into 2 or 3 parts with equal sum” → Number of Ways / Partition Equal Subset Sum contest form.
