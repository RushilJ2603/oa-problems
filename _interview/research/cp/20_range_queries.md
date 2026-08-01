# 20 — Range queries: prefix, sparse table, Fenwick/BIT, segment tree (lazy stretch)

**Placement value:** High — static range aggregates, point-update range queries, and inversion / order-statistic counting are staples of OAs and Div2 C–D; Fenwick + basic segtree are the interview DS upgrade past plain prefix sums.
**Prereq topics:** Prefix sums & difference arrays (topic 04), binary search, sorting / coordinate compression, basic recursion
**Pattern in one paragraph:** When many queries ask for an associative aggregate on contiguous indices (sum / min / max / XOR / GCD), precompute or maintain a structure instead of scanning. Static + idempotent (min/max/GCD) → sparse table \(O(1)\) after \(O(n\log n)\). Point updates + range sum → Fenwick (BIT) or segment tree. Arbitrary associative merges / “walk to first index with …” → segment tree. Range updates with range queries → lazy propagation `(stretch)`. Signal words: many queries on `[l,r]`, update index then re-query, k-th element in a multiset, count inversions / nested segments, assign to first hotel with enough rooms.

## Ladder (easy -> hard, ~18-28 problems)
- [ ] [Static Range Sum Queries](https://cses.fi/problemset/task/1646) — `CSES` `Range Queries` — 1D prefix — **(core)** CSES / USACO Guide; bridge from topic 04 into query DS
- [ ] [Odd Queries](https://codeforces.com/problemset/problem/1807/D) — `Codeforces` `900` — prefix parity — **(core)** modern Div2 B; many queries force `long long` prefixes
- [ ] [Static Range Minimum Queries](https://cses.fi/problemset/task/1647) — `CSES` `Range Queries` — sparse table RMQ — **(core)** CSES / cp-algorithms classic; \(O(1)\) idempotent query
- [ ] [Range Xor Queries](https://cses.fi/problemset/task/1650) — `CSES` `Range Queries` — prefix XOR — **(core)** CSES; XOR is its own inverse (`pref[r] ^ pref[l−1]`)
- [ ] [RMQ (Range Maximum Queries)](https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_bf) — `AtCoder` `Tessoku A58` — point update + range max — kyopro textbook segtree drill
- [ ] [Dynamic Range Sum Queries](https://cses.fi/problemset/task/1648) — `CSES` `Range Queries` — Fenwick / segtree PURS — **(core)** CSES / USACO Guide Gold PURS focus
- [ ] [Range Sum Query - Mutable](https://leetcode.com/problems/range-sum-query-mutable/) — `LeetCode` `Medium` — Fenwick / segtree API — **(core)** NeetCode / Striver; OA NumArray-with-updates
- [ ] [Dynamic Range Minimum Queries](https://cses.fi/problemset/task/1649) — `CSES` `Range Queries` — point set + range min — **(core)** CSES; same tree as sum, change the merge
- [ ] [Range Xor Query](https://atcoder.jp/contests/abc185/tasks/abc185_f) — `AtCoder` `ABC185 F` — Fenwick XOR — **(core)** modern ABC F; BIT with XOR as “sum”
- [ ] [Knight Tournament](https://codeforces.com/problemset/problem/356/A) — `Codeforces` `1500` — paint next survivor — **(core)** set / segtree “next alive”; classic CF DS B
- [ ] [Distinct Characters Queries](https://codeforces.com/problemset/problem/1234/D) — `Codeforces` `1600` — 26 BITs / segtree OR — **(core)** char presence on `[l,r]`; very common OA shape
- [ ] [Range Update Queries](https://cses.fi/problemset/task/1651) — `CSES` `Range Queries` — range add + point query — **(core)** CSES; BIT-as-difference or lazy; USACO Guide adjacent
- [ ] [Nested Ranges Count](https://cses.fi/problemset/task/2169) — `CSES` `Sorting and Searching` — Fenwick + sort — **(core)** CSES / USACO Guide; compress + count contained ranges
- [ ] [Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) — `LeetCode` `Hard` — Fenwick inversions — **(core)** NeetCode; *the* interview inversion / BIT count pattern
- [ ] [Hotel Queries](https://cses.fi/problemset/task/1143) — `CSES` `Range Queries` — walk first ≥ x — **(core)** CSES / CF-EDU-adjacent; binary-lift on segtree max
- [ ] [List Removals](https://cses.fi/problemset/task/1749) — `CSES` `Range Queries` — order-statistic BIT — **(core)** CSES; find k-th alive then delete
- [ ] [Salary Queries](https://cses.fi/problemset/task/1144) — `CSES` `Range Queries` — compress + Fenwick freq — **(core)** CSES; dynamic “how many in [a,b]” after point changes
- [ ] [Xenia and Bit Operations](https://codeforces.com/problemset/problem/339/D) — `Codeforces` `1700` — OR/XOR by layer — **(core)** CF classic; tree height encodes alternating ops
- [ ] [Rorororobot](https://codeforces.com/problemset/problem/1709/D) — `Codeforces` `1700` — sparse max + binsearch — sparse table on column heights; USACO-Guide-style combo
- [ ] [Flowers](https://atcoder.jp/contests/dp/tasks/dp_q) — `AtCoder` `DP contest Q` — BIT for LIS-style DP — AtCoder DP contest; max beauty with increasing height
- [ ] [Nested Segments](https://codeforces.com/problemset/problem/652/D) — `Codeforces` `1800` — Fenwick containment — **(stretch)** USACO Guide; sort endpoints, count insides
- [ ] [Pashmak and Parmida's problem](https://codeforces.com/problemset/problem/459/D) — `Codeforces` `1800` — Fenwick on frequencies — **(stretch)** classic “f(prefix) vs f(suffix)” count
- [ ] [Multiset](https://codeforces.com/problemset/problem/1354/D) — `Codeforces` `1900` — BIT find-k-th — **(stretch)** interactive-adjacent multiset; CF BIT tutorial problem
- [ ] [Enemy is weak](https://codeforces.com/problemset/problem/61/E) — `Codeforces` `1900` — 3-way inversions — **(stretch)** Fenwick / merge-sort tree milestone
- [ ] [Sereja and Brackets](https://codeforces.com/problemset/problem/380/C) — `Codeforces` `2000` — merge node (open/close) — **(stretch)** *the* custom-merge segtree classic
- [ ] [Range Updates and Sums](https://cses.fi/problemset/task/1735) — `CSES` `Range Queries` — lazy add + assign — **(stretch)** CSES / USACO Guide RURQ; full lazy template
- [ ] [XOR on Segment](https://codeforces.com/problemset/problem/242/E) — `Codeforces` `2000` — lazy XOR per bit — **(stretch)** 20 bit-segtrees or lazy bitmasks
- [ ] [Ant colony](https://codeforces.com/problemset/problem/474/F) — `Codeforces` `2100` — GCD RMQ + count — **(stretch)** sparse/segtree; how many equals range GCD

## Must-internalize checklist (5-10 bullets)
- Prefix vs DS: static sum/XOR → prefix; static min/max/GCD → sparse table; updates appear → Fenwick or segtree.
- Sparse table: `st[k][i] = op(st[k−1][i], st[k−1][i+2^{k−1}])`; idempotent query with two overlapping blocks of length `2^{floor(log(r−l+1))}`.
- Fenwick (1-indexed): `add(i,δ)` via `i += i & −i`; `sum(i)` via `i −= i & −i`; range = `sum(r) − sum(l−1)`; always `long long` on CF.
- Fenwick as frequency / order statistic: compress values, `add(pos, ±1)`, find k-th by binary lifting on prefix sums (List Removals / Multiset).
- Segment tree template: build / point-update / range-query with associative `merge` (sum, min, XOR, or a struct); iterative or recursive both fine.
- Walk / descent: first index with `tree[node] ≥ x` (Hotel Queries); same idea as CF EDU “first at least X”.
- Coordinate compression before BIT/segtree when values are up to \(10^9\) (Salary Queries, inversions).
- Lazy `(stretch)`: store pending add/assign tags; `push` before recursing; compose tags correctly (assign kills prior adds).
- Off-by-one + overflow: inclusive `[l,r]`, 0- vs 1-index, and `n ≤ 2·10^5` ⇒ \(O((n+q)\log n)\) only.

## Where it appears in OAs / interviews
- “Design NumArray: update index, query range sum” → LC 307 / CSES Dynamic Range Sum (Amazon/Meta-style API questions).
- “Count inversions / how many smaller to the right” → LC 315 / Fenwick or merge sort (classic hard OA).
- “Many range min/max or XOR queries, array never changes” → sparse table or prefix XOR (CSES Static RMQ / Range Xor).
- “First seat/hotel/server that can take load `x`, then decrease capacity” → Hotel Queries / walk-on-segtree (system-design-flavored DS).
