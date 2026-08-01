# 05 — Binary Search & Parametric Search (Depth Pass)

**Placement value:** High (second wave of CF-style BS-on-answer / parametric checks beyond the classic OA templates)
**Prereq topics:** Arrays, Sorting, Prefix Sums, Greedy feasibility checks; light graphs for reachability-in-check

**Pattern in one paragraph:** After the standard ladder (Koko / ship packages / Hamburgers / min-max partition), contest problems stop announcing “binary search” and instead hide a monotonic decision problem: guess a threshold $X$ (time, capacity, strength, median, party size), then answer a YES/NO with greedy, two pointers, prefix/diff arrays, or BFS. Recognize it when the answer range is huge ($10^9$–$10^{18}$) but a fixed $X$ can be validated in near-linear time, and feasibility is monotone in $X$.

## Ladder (easy -> hard, 25 problems)
- [ ] [Wooden Toy Festival](https://codeforces.com/problemset/problem/1840/D) — `Codeforces` `1400` — BS on answer + greedy cover — Maximize min gap with ≤3 “centers”; clean post-basics parametric. **(core)**
- [ ] [Jumping Through Segments](https://codeforces.com/problemset/problem/1907/D) — `Codeforces` `1400` — BS on max step — Maintain feasible position interval while walking segments; classic “expand search space until path exists.” **(core)**
- [ ] [The Delivery Dilemma](https://codeforces.com/problemset/problem/1443/C) — `Codeforces` `1400` — BS on time — Sort courier times; decide which orders to self-pick vs courier under deadline $T$. **(core)**
- [ ] [Sagheer and Nubian Market](https://codeforces.com/problemset/problem/812/C) — `Codeforces` `1500` — BS max $k$ + cost rewrite — Cost of taking $k$ items becomes $a_i + i\cdot k$; sort and prefix-sum inside check. **(core)**
- [ ] [Cellular Network](https://codeforces.com/problemset/problem/702/C) — `Codeforces` `1500` — BS radius + two pointers — Cover sorted cities with sorted towers; textbook coverage predicate. **(core)**
- [ ] [Final Boss](https://codeforces.com/problemset/problem/1985/F) — `Codeforces` `1500` — BS on turns — Damage-per-turn with cooldowns; careful `long long` overflow in check. **(core)**
- [ ] [Quests](https://codeforces.com/problemset/problem/1760/F) — `Codeforces` `1500` — BS on cooldown $k$ — Greedy take largest rewards under “reuse every $k$ days”; OA-adjacent resource pacing. **(core)**
- [ ] [The Meeting Place Cannot Be Changed](https://codeforces.com/problemset/problem/780/B) — `Codeforces` `1600` — floating-point BS — Min time for all to meet on a line; fixed ~100 iterations, not EPS loops. **(core)**
- [ ] [Keshi Is Throwing a Party](https://codeforces.com/problemset/problem/1610/C) — `Codeforces` `1600` — BS party size + greedy — For size $m$, scan with richer-people / poorer-people caps; high-consensus Div2 C. **(core)**
- [ ] [Mafia](https://codeforces.com/problemset/problem/348/A) — `Codeforces` `1600` — BS on games — “Everyone plays all but one game” reformulates to a clean sum check. **(core)**
- [ ] [Set or Decrease](https://codeforces.com/problemset/problem/1622/C) — `Codeforces` `1600` — BS / math on ops — Sort, decide how many large elements to collapse to the minimum; mix of BS and closed form. **(core)**
- [ ] [To Become Max](https://codeforces.com/problemset/problem/1856/C) — `Codeforces` `1600` — BS target max — Check whether value $x$ is reachable by cascading $+1$ ops from the right; non-obvious DP-flavored check. **(core)**
- [ ] [Tracking Segments](https://codeforces.com/problemset/problem/1843/E) — `Codeforces` `1600` — BS on prefix of updates — After $t$ flips, some segment becomes majority-1; prefix + range count in check.
- [ ] [Jumping Takahashi 2](https://atcoder.jp/contests/abc257/tasks/abc257_d) — `AtCoder` `ABC D (~1600)` — parametric + reachability — BS strength $S$, build edges $P_i S \ge$ Manhattan, test if some root reaches all. **(core)**
- [ ] [Present](https://codeforces.com/problemset/problem/460/C) — `Codeforces` `1700` — BS height + diff array — Water flowers so every height $\ge h$; sliding window / difference array inside check. **(stretch)**
- [ ] [String Game](https://codeforces.com/problemset/problem/778/A) — `Codeforces` `1700` — BS deletions — Delete first $mid$ characters (by given order), still keep $t$ as subsequence. **(stretch)**
- [ ] [Valiant's New Map](https://codeforces.com/problemset/problem/1731/D) — `Codeforces` `1700` — BS side + 2D prefix — Largest square where every cell $\ge mid$; binary grid + 2D sums. **(stretch)**
- [ ] [Yet Another Monster Killing Problem](https://codeforces.com/problemset/problem/1257/D) — `Codeforces` `1700` — BS days + sparse max — Heroes’ endurance/power; greedy segment cover with RMQ/`max` suffix. **(stretch)**
- [ ] [Pond](https://atcoder.jp/contests/abc203/tasks/abc203_d) — `AtCoder` `ABC D (~1700)` — BS median + 2D prefix — Minimize median of $K\times K$ block; count cells $>X$ via cumulative sums. **(stretch)**
- [ ] [Multiplication Table](https://codeforces.com/problemset/problem/448/D) — `Codeforces` `1800` — BS $k$-th value — Count entries $\le mid$ as $\sum_i \min(n,\lfloor mid/i\rfloor)$; same idea as [CSES Multiplication Table](https://cses.fi/problemset/task/2422). **(stretch)**
- [ ] [Office Keys](https://codeforces.com/problemset/problem/830/A) — `Codeforces` `1800` — BS time + matching — People/keys on a line; sorted assignment of a contiguous key window. **(stretch)**
- [ ] [Friends and Presents](https://codeforces.com/problemset/problem/483/B) — `Codeforces` `1800` — BS on max + inclusion — How many integers $\le mid$ avoid multiples of $x$/$y$ enough for both friends. **(stretch)**
- [ ] [Magic Ship](https://codeforces.com/problemset/problem/1117/C) — `Codeforces` `1900` — BS days + wind prefix — Apply wind for $mid$ days, remaining Manhattan distance must be $\le$ free moves left. **(stretch)**
- [ ] [Salary Changing](https://codeforces.com/problemset/problem/1251/D) — `Codeforces` `1900` — BS median salary — Force enough people $\ge mid$ under budget; sort + greedy spend from the top half. **(stretch)**
- [ ] [Max Median](https://codeforces.com/problemset/problem/1486/D) — `Codeforces` `2100` — BS median + prefix — Map $a_i\mapsto \pm 1$ vs mid; need a subarray length $\ge k$ with positive prefix balance. **(stretch)**

## Must-internalize checklist (technique notes)
- Rewrite the check until it is obviously monotone: “can we achieve median/height/time $\ge X$?” beats inventing a direct formula.
- Cost-depends-on-$k$ (Sagheer): when taking $k$ items changes each item’s cost, **re-sort for that $k$** inside the check — do not reuse one global order.
- Coverage checks (Cellular / Wooden Toy / Office Keys): sort both sides, then two-pointer or “next uncovered” greedy; if the greedy fails, $mid$ is impossible.
- Integer overflow: damage $\times$ turns, $n\cdot mid$, and $\sum mid/i$ all need `i64`; prefer `mid = lo + (hi-lo)/2`.
- Float / continuous answers: run a fixed 80–100 iterations (Meeting Place); never `while (hi-lo > 1e-9)` under tight TL.
- $k$-th in an implicit sorted list (multiplication table / pair products): BS the value $v$, count how many entries $\le v$ in $O(n)$ or $O(n\log)$.
- Diff-array / sliding window inside check (Present): “add $+1$ on $[i,i+w)$” is $O(1)$ amortized per index after a difference array, so total check stays $O(n)$.
- Parametric + graph (Jumping Takahashi): edges appear as $S$ grows; BS $S$ and only rebuild/BFS the threshold graph — do not Dijkstra over all $S$.

## Where it appears in OAs / interviews
- **Threshold scheduling:** “Minimum days so every monster/task is cleared by some worker with cooldown/endurance” (Final Boss / Monster Killing family).
- **Facility radius:** “Smallest Wi-Fi/tower radius covering all clients” — Cellular Network clone, common in OA rounds.
- **Budgeted median:** “Raise salaries so the median is at least $X$ without exceeding budget $S$” — Salary Changing pattern.
- **Hidden $k$-th:** “What is the $k$-th product / table entry / pair sum?” without materializing $O(n^2)$ pairs — classic phone-screen follow-up to plain binary search.
