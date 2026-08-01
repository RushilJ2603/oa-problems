# 09 — Recursion & Backtracking (Depth Pass)

**Placement value:** Medium–High (Second ladder: CF-style exhaustive search, digit DFS, and meet-in-the-middle — the post-Striver skill of turning “$N\le 40$ / tiny grid” into a pruned search, not an LC template).
**Prereq topics:** Subsets / permutations / grid DFS templates (finished the standard Recursion & Backtracking ladder), bitmasks, basic modular arithmetic; light DP for the stretch tail.
**Pattern in one paragraph:** After Subsets / N-Queens / Word Search, contest problems hide the same recursion behind **constraints, pruning, and half-space tricks**. You still build a partial assignment (digits, tiles, team membership, signed subset, path from both ends) and abandon it early — but the win often comes from **splitting the search** (meet-in-the-middle), **canonicalizing order** (process largest tile / lexicographically smallest unused index first), or **reformulating into base-$k$ / ternary digits** so each “choice” is a digit, not a raw $2^n$ branch. Recognize them when $n\le 40$ with a sum/XOR target, “nearest number with $\le k$ distinct digits”, small tiling / team-partition constraints, or a grid path that is too long for one-sided DFS.

**Non-obvious tricks (internalize):**
1. $n\le 40$ subset-sum / max under mod → split into two halves of $n/2$, enumerate $2^{n/2}$, sort + two-pointer / binary search the complement (Maximum Subsequence).
2. Factorial-boosted MITM: each element has states `{skip, take, take·k!}` → still $\sim 3^{n/2}$ per half (Anya and Cubes).
3. Grid XOR/path MITM: walk from start to mid-diagonal and from end to mid; match on cell + XOR (Xor-Paths).
4. Ternary balance / “good numbers”: each weight digit $\in\{-1,0,1\}$ (left / unused / right) or base-3 digits only $0/1$ — recurse on digit position, not on items (Vanya and Scales / Good Numbers).
5. Digit DFS for “nearest valid”: fill prefix equal to $n$, then first free position, then greedy min/max; track used-digit mask and “already smaller/larger” flag (Nearest Beautiful Number).
6. Partition / tiling: always place into the **lexicographically first empty cell / unused person**; try pieces largest-first so failures prune early (Tiling / Peaceful Teams / Knight’s Tour Warnsdorff).
7. Signed-subset certificate: $a$ is reachable as $\sum \varepsilon_i a_i$ with $\varepsilon_i\in\{-1,0,1\}$ (or subset difference $0$) iff a non-trivial combination hits $0$ — often enough for existence (Array Differentiation).
8. Reverse search from target: when forward branching is huge, invert the recurrence (Pairs of Numbers: from $(a,b)$ only step $(a+b,b)$ or $(a,a+b)$ backward via Euclidean-style cuts).

## Ladder (easy -> hard, ~22 problems)
- [ ] [Chessboard](https://codeforces.com/problemset/problem/961/C) — `Codeforces` `1400` — combinatorial brute / rotations — **(core)** try all $4^4$ orientation sets of four $n\times n$ boards; count black/white mismatches on the $2n\times 2n$ assembly.
- [ ] [D - Peaceful Teams](https://atcoder.jp/contests/abc310/tasks/abc310_d) — `AtCoder` `ABC310 D (~1370)` — partition backtracking — **(core)** assign $N$ people into exactly $K$ non-empty teams avoiding forbidden pairs; canonical “first unassigned → try teams”.
- [ ] [D - Tiling](https://atcoder.jp/contests/abc345/tasks/abc345_d) — `AtCoder` `ABC345 D (~1420)` — rectangle tiling BT — **(core)** place given tiles (rotations allowed) to fill $H\times W$; fill next empty cell, try tiles largest-first.
- [ ] [D - Polyomino](https://atcoder.jp/contests/abc322/tasks/abc322_d) — `AtCoder` `ABC322 D (~1310)` — shape placement BT — pack three fixed polyominoes into $4\times 4$ with rotations/translations; tiny state space, sharp prune practice.
- [ ] [Kayaking](https://codeforces.com/problemset/problem/863/B) — `Codeforces` `1500` — choose-then-greedy — **(core)** pick which two people sit alone ($O(n^2)$), sort the rest and pair adjacent; teaches “search the discrete choice, greed the rest”.
- [ ] [Good Numbers (hard version)](https://codeforces.com/problemset/problem/1249/C2) — `Codeforces` `1500` — base-3 digit search — **(core)** numbers whose ternary digits are only $0/1$; bump the first $2$-digit and clear below — recursive digit rewrite, not $3^{40}$ brute.
- [ ] [Undoubtedly Lucky Numbers](https://codeforces.com/problemset/problem/244/B) — `Codeforces` `1600` — digit DFS generation — **(core)** generate all numbers with $\le 2$ distinct digits up to $10^9$; classic constrained digit recursion.
- [ ] [Dima and a Bad XOR](https://codeforces.com/problemset/problem/1151/B) — `Codeforces` `1600` — row-pick search / constructive — **(core)** choose one entry per row so XOR $\ne 0$; fix free rows, branch only where needed — OA-flavored existence search.
- [ ] [Baby Ehab Partitions Again](https://codeforces.com/problemset/problem/1516/C) — `Codeforces` `1700` — subset-sum partition — **(core)** detect half-sum subset; if partitionable, remove one odd-parity / minimal-valuation element — bridges BT ↔ knapsack DP.
- [ ] [Maximum Subsequence](https://codeforces.com/problemset/problem/888/E) — `Codeforces` `1800` — meet-in-the-middle — **(core)** *the* CF MITM drill: max subset sum $\bmod\, m$ for $n\le 35$; half-enumerate + sort complements.
- [ ] [Array Differentiation](https://codeforces.com/problemset/problem/1552/D) — `Codeforces` `1800` — signed-subset search — **(core)** existence of multiset $b$ with $a_i=b_j-b_k$; reduces to a non-empty $\{+1,-1,0\}$ combo summing to $0$.
- [ ] [E - Permutation](https://atcoder.jp/contests/abc199/tasks/abc199_e) — `AtCoder` `ABC199 E (~1814)` — constrained perm count — **(core)** $N\le 18$: build perm left-to-right with bitmask + prefix constraints; memoized recursion ≡ bitmask DP.
- [ ] [Knight's Tour](https://cses.fi/problemset/task/1689) — `CSES` `Graph Algorithms` — Warnsdorff backtracking — **(core)** $8\times 8$ knight tour; degree-heuristic move order is the prune that makes pure BT finish.
- [ ] [Vanya and Scales](https://codeforces.com/problemset/problem/552/C) — `Codeforces` `1900` — ternary balance recursion — **(stretch)** powers of $w$ on left/right/unused; greedy digit or recurse on residue $\bmod\, w$.
- [ ] [Nearest Beautiful Number (easy version)](https://codeforces.com/problemset/problem/1560/F1) — `Codeforces` `1900` — digit backtracking — **(stretch)** smallest $\ge n$ using at most $k$ distinct digits; prefix DFS with used-mask.
- [ ] [Pairs of Numbers](https://codeforces.com/problemset/problem/134/B) — `Codeforces` `1900` — reverse Euclidean search — **(stretch)** min ops from $(1,1)$ to $(n,?)$ / $(?,n)$; search backward from $n$ by subtracting multiples.
- [ ] [Dr. Evil Underscores](https://codeforces.com/problemset/problem/1285/D) — `Codeforces` `1900` — bit-trie recursion — **(stretch)** choose $x$ minimizing $\max(a_i\oplus x)$; recurse MSB→LSB, partition by bit, take $\min$ branch cost.
- [ ] [Roman and Numbers](https://codeforces.com/problemset/problem/401/D) — `Codeforces` `2000` — digit-perm / bitmask DP — **(stretch)** count permutations of digits of $n$ divisible by $m$; state `(mask, mod)` — BT with memo.
- [ ] [Hamiltonian Flights](https://cses.fi/problemset/task/1690) — `CSES` `Graph Algorithms` — Hamiltonian paths bitmask — **(stretch)** count $1\to n$ Hamilton paths; the DP form of “perm BT on a digraph”.
- [ ] [Anya and Cubes](https://codeforces.com/problemset/problem/525/E) — `Codeforces` `2100` — MITM + factorials — **(stretch)** each cube: skip / take / take $a_i!$ (limited); split $n\le 25$, match sums to $S$.
- [ ] [Xor-Paths](https://codeforces.com/problemset/problem/1006/F) — `Codeforces` `2100` — grid path MITM — **(stretch)** paths $(1,1)\to(n,m)$ with XOR $k$; meet on mid anti-diagonal, hash by (cell, xor).
- [ ] [Nearest Beautiful Number (hard version)](https://codeforces.com/problemset/problem/1560/F2) — `Codeforces` `2100` — digit BT hardened — **(stretch)** same as F1 with larger $k$/tighter TL; forces careful greedy-after-branch and no redundant masks.

## Must-internalize checklist (5-10 bullets)
- Write **meet-in-the-middle** from memory: split, enumerate, sort one half, query complements in $O(2^{n/2}n)$.
- Digit DFS skeleton: `pos`, `tight`/`started`, `used-mask` / distinct-count; generate *or* find nearest.
- Partition/tiling skeleton: find first hole → try all legal pieces/rotations → recurse → undo.
- Canonical labeling: assign person $i$ only to teams $1..\mathrm{used}(+1)$ so team sets are unordered.
- Prune order: largest tile / lowest Warnsdorff degree / descending $a_i$ first — fail fast.
- Know when BT becomes **bitmask DP**: $n\le 20$ Hamilton / constrained perms → memoize on `mask` (+ aux).
- Ternary / base-$w$ digit view of balance and “good numbers” — one digit choice per weight, not subset of items.
- Undo discipline: mutate board/mask/sum, recurse, restore; same habit as Word Search / Sudoku.

## Where it appears in OAs / interviews
- **“Split into $K$ groups with conflict pairs”** → Peaceful Teams / Matchsticks-style partition with adjacency bans (Amazon/Meta scheduling flavors).
- **“Can you tile / place shapes on a small board?”** → Tiling / Polyomino; interviewers care about first-empty-cell + undo, not fancy DS.
- **“Largest subset sum under mod / closest to target, $n\sim 40$”** → MITM (Maximum Subsequence); classic hard phone-screen once they see $2^{40}$ is impossible.
- **“Smallest number ≥ $n$ with ≤ $k$ distinct digits”** → Nearest Beautiful Number digit DFS; common “don’t use DP, just recurse on digits” follow-up.
