# 06 — Sorting-based Techniques, Custom Comparators & Coordinate Compression

**Placement value:** High (sort-then-scan, custom order, and rank-compressing values underpin a huge share of OA array/interval problems)
**Prereq topics:** Arrays, pairs/tuples, basic greedy intuition
**Pattern in one paragraph:** Sort (often with a custom key) so the hard part becomes a linear scan, a greedy choice, or an event sweep; when values are huge but few, map them to ranks `0..k-1` (coordinate compression) so arrays / Fenwick / segment trees fit in memory. Spot it when the statement cares about relative order, “after sorting…”, multi-key ranking, interval nesting/sweep, or when you need to index by values up to `1e9` with only `n ≤ 1e5` distinct points.

## Ladder (easy -> hard, 25 problems)
- [ ] [Halloumi Boxes](https://codeforces.com/problemset/problem/1903/A) — `Codeforces` `800` — sortability check — CP-31 staple: when a reverse-window lets you fully sort.
- [ ] [Gravity Flip](https://codeforces.com/problemset/problem/405/A) — `Codeforces` `900` — basic sort — A2OJ classic “just sort it” warm-up. **(core)**
- [ ] [Puzzles](https://codeforces.com/problemset/problem/337/A) — `Codeforces` `900` — sort + window — A2OJ staple: sort then minimize `a[i+k-1]-a[i]`. **(core)**
- [ ] [Dragons](https://codeforces.com/problemset/problem/230/A) — `Codeforces` `1000` — sort then greedy — Sort by strength and simulate (A2OJ Div2-A ladder energy). **(core)**
- [ ] [Distinct Numbers](https://cses.fi/problemset/task/1621) — `CSES` `Sorting and Searching` — sort + unique — Canonical `sort`/`unique` (or set) intro (CSES). **(core)**
- [ ] [Rank List](https://codeforces.com/problemset/problem/166/A) — `Codeforces` `1100` — multi-key comparator — A2OJ classic custom order (points ↓, time ↑). **(core)**
- [ ] [Laptops](https://codeforces.com/problemset/problem/456/A) — `Codeforces` `1100` — sort pairs + scan — Sort by price, check if quality ever decreases.
- [ ] [Substrings Sort](https://codeforces.com/problemset/problem/988/B) — `Codeforces` `1100` — custom string order — Sort by length / containment; forces a real comparator.
- [ ] [Rank Transform of an Array](https://leetcode.com/problems/rank-transform-of-an-array/) — `LeetCode` `Easy` — coordinate compression — Cleanest OA intro to rank-mapping (placement). **(core)**
- [ ] [Vanya and Lanterns](https://codeforces.com/problemset/problem/492/B) — `Codeforces` `1200` — sort + gaps — Sort positions, max adjacent/boundary gap (A2OJ).
- [ ] [Movie Festival](https://cses.fi/problemset/task/1629) — `CSES` `Sorting and Searching` — sort by end time — The activity-selection sort key everyone must own (CSES). **(core)**
- [ ] [Restaurant Customers](https://cses.fi/problemset/task/1619) — `CSES` `Sorting and Searching` — event sort / sweep — +1/−1 events sorted by time (CSES, USACO Guide). **(core)**
- [ ] [Merge Intervals](https://leetcode.com/problems/merge-intervals/) — `LeetCode` `Medium` — sort intervals — NeetCode / Striver OA staple. **(core)**
- [ ] [Cinema](https://codeforces.com/problemset/problem/670/C) — `Codeforces` `1300` — frequency map / compress — A2OJ classic: rank languages via counts (compression precursor). **(core)**
- [ ] [Reorder Cards](https://atcoder.jp/contests/abc213/tasks/abc213_c) — `AtCoder` `ABC-C` — coordinate compression — Famous “compress rows & cols independently” teach-piece. **(core)**
- [ ] [Nested Ranges Check](https://cses.fi/problemset/task/2168) — `CSES` `Sorting and Searching` — custom range comparator — Sort by L↑ / R↓ then scan (CSES).
- [ ] [Exams](https://codeforces.com/problemset/problem/479/C) — `Codeforces` `1400` — sort + greedy day — A2OJ milestone: sort by `a`, greedily take `b` when possible. **(core)**
- [ ] [Largest Number](https://leetcode.com/problems/largest-number/) — `LeetCode` `Medium` — concat comparator — Striver classic: order by `a+b` vs `b+a` (strict weak order).
- [ ] [Standings](https://atcoder.jp/contests/abc308/tasks/abc308_c) — `AtCoder` `ABC-C` — fractional custom comparator — Compare `a/(a+b)` via cross-multiply; float WA trap.
- [ ] [Little Girl and Maximum Sum](https://codeforces.com/problemset/problem/276/C) — `Codeforces` `1500` — sort rearrange — Frequency of index hits → pair largest values with hottest indices.
- [ ] [The Smallest String Concatenation](https://codeforces.com/problemset/problem/632/C) — `Codeforces` `1700` — concat comparator — USACO Guide custom-cmp milestone. **(stretch)**
- [ ] [Covered Points Count](https://codeforces.com/problemset/problem/1000/C) — `Codeforces` `1700` — sweep + compression — USACO Guide; discrete events on compressed coords. **(stretch)**
- [ ] [Nested Ranges Count](https://cses.fi/problemset/task/2169) — `CSES` `Sorting and Searching` — sort + Fenwick — Same order as Check, then rank-compressed BIT counts (CSES). **(stretch)**
- [ ] [Pashmak and Parmida's problem](https://codeforces.com/problemset/problem/459/D) — `Codeforces` `1800` — compression + Fenwick — Offline left/right frequency counts after ranking. **(stretch)**
- [ ] [Enemy is weak](https://codeforces.com/problemset/problem/61/E) — `Codeforces` `1900` — compression + Fenwick — Canonical inversion-style triple count with ranks. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- Write a **custom comparator / lambda** that is a strict weak ordering (`cmp(a,a)==false`; transitive; no float keys when avoidable).
- Multi-key sorts: primary key, then tie-break (e.g. points desc, penalty asc) via `pair`/`tuple` or explicit `if`.
- Interval / activity keys: sort by **end** for greedy selection; by **start** (with end tie-break) for merge / nesting scans.
- Event sweep template: emit `(time, +1/-1)` (or open before close with a secondary key), sort, scan a running counter.
- Coordinate compression template: copy → `sort` → `unique` → `lower_bound` ranks (or `map` for sparse offline use).
- Know when compression is needed: values as Fenwick/seg-tree indices with `a[i] ≤ 1e9` but `n ≤ 1e5`.
- Stable vs unstable sort awareness; prefer keys over ad-hoc swaps when reconstructing permutations/indices.
- Concatenation order: compare `a+b` vs `b+a` (or cross-multiply fractions) instead of floating ratios.

## Where it appears in OAs / interviews
- **Meeting / booking merge:** “Merge overlapping meeting slots” → sort by start (Merge Intervals / Movie Festival family).
- **Leaderboard / ranking:** “Sort by score then by name/time” → multi-key comparator (Rank List).
- **Form largest number / custom order:** “Arrange tokens so the concatenation is maximal” → Largest Number–style cmp.
- **Sparse timeline / heatmap:** “Values up to 1e9, only n distinct points matter” → compress then prefix / Fenwick (Reorder Cards / Covered Points).
