# 26 — Advanced segment tree: lazy propagation, segtree-beats, merge-sort tree

**Placement value:** Medium — plain range-add / range-assign + range-sum shows up in harder OAs and Div2 D; beats and merge-sort tree are almost pure CF rating-builders (CM stretch) Striver never covers.
**Prereq topics:** Range queries (topic 20: Fenwick + basic segtree), binary search, coordinate compression, recursion / tree walk
**Pattern in one paragraph:** When updates touch a *range* (not a point), push work into lazy tags and only `push` when you descend — compose tags carefully (assign kills prior adds; affine \(x \mapsto bx+c\) composes as matrix-like). When the update is *not* a clean monoid action (range \(a_i \bmod x\), range chmin/chmax, “replace by \(d(a_i)\)”), maintain max / 2nd-max (or min) and only recurse when the update can still change something — amortized “segtree beats”. When queries ask order-statistic / count-of-values on a static index range (“how many \(a_i \le x\) on \([L,R]\)”, k-th, 2D dominance), store a **sorted vector** (or Fenwick of compressed values) in each segtree node — merge-sort tree, query \(O(\log^2 n)\). Signal words: range add/set then range sum/min, range XOR/flip, “modulo each element”, “set \(a_i=\min(a_i,x)\)”, count pairs / inversions / values \(\le k\) on subarrays.

## Ladder (easy -> hard, ~18-28 problems)
- [ ] [Range Update Queries](https://cses.fi/problemset/task/1651) — `CSES` `Range Queries` — range add + point query — **(core)** CSES / USACO Guide RURQ entry; BIT-as-difference or first lazy tag
- [ ] [029 - Long Bricks（★5）](https://atcoder.jp/contests/typical90/tasks/typical90_ac) — `AtCoder` `Typical90 ★5` — range assign / chmax + point max — **(core)** kyopro classic; pending “paint height” tags
- [ ] [Range Updates and Sums](https://cses.fi/problemset/task/1735) — `CSES` `Range Queries` — lazy add + assign + sum — **(core)** CSES / USACO Guide focus; *the* compose-tags template (assign overrides add)
- [ ] [Range Affine Range Sum](https://atcoder.jp/contests/practice2/tasks/practice2_k) — `AtCoder` `ACL Practice K` — \(a_i \leftarrow b\cdot a_i+c\), range sum — **(core)** ACL `lazy_segtree` drill; monoid = (sum, len), tag compose \((b,c)\)
- [ ] [Lazy Segment Tree](https://atcoder.jp/contests/practice2/tasks/practice2_l) — `AtCoder` `ACL Practice L` — range flip + range inversions — **(core)** custom node (zeros, ones, inv); flip swaps and remaps inv
- [ ] [Polynomial Queries](https://cses.fi/problemset/task/1736) — `CSES` `Range Queries` — add AP \(1,2,3,\ldots\) on range — **(core)** CSES; two lazy params (base + slope) or affine-on-index
- [ ] [Prefix Sum Queries](https://cses.fi/problemset/task/2166) — `CSES` `Range Queries` — max prefix on subarray — **(core)** CSES / USACO Guide; merge `(sum, best_pref)` (or lazy on prefix array)
- [ ] [Replace Digits](https://atcoder.jp/contests/abl/tasks/abl_e) — `AtCoder` `ABL E` — range digit-assign, print number mod \(998244353\) — lazy assign + place-value powers in node
- [ ] [Two Sequence Queries](https://atcoder.jp/contests/abc357/tasks/abc357_f) — `AtCoder` `ABC357 F` — range add on A/B, query \(\sum A_i B_i\) — maintain \((\sum A,\sum B,\sum AB,\mathrm{len})\) + lazy
- [ ] [Vacation Query](https://atcoder.jp/contests/abc322/tasks/abc322_f) — `AtCoder` `ABC322 F` — range assign 0/1 + longest run of 1s — custom merge (pref/suf/best) + assign tag
- [ ] [Interesting Array](https://codeforces.com/problemset/problem/482/B) — `Codeforces` `1800` — build array from OR constraints — **(core)** assign bits via lazy OR, verify with AND; classic constructive+lazy
- [ ] [Pashmak and Parmida's problem](https://codeforces.com/problemset/problem/459/D) — `Codeforces` `1800` — count \(f(\mathrm{prefix}) > f(\mathrm{suffix})\) — **(core)** Fenwick / merge-sort tree on frequencies; MST entry
- [ ] [Copying Data](https://codeforces.com/problemset/problem/292/E) — `Codeforces` `1900` — copy subarray \(a\to b\) — **(core)** lazy “which source offset covers this segment”
- [ ] [Restore Permutation](https://codeforces.com/problemset/problem/1208/D) — `Codeforces` `1900` — recover perm from prefix sums — **(core)** walk largest remaining on lazy/Fenwick sums
- [ ] [Enemy is weak](https://codeforces.com/problemset/problem/61/E) — `Codeforces` `1900` — count 3-way inversions — **(core)** two Fenwicks or merge-sort tree; USACO-Guide-adjacent
- [ ] [Tufurama](https://codeforces.com/problemset/problem/961/E) — `Codeforces` `1900` — count pairs with index/value bounds — **(core)** *the* merge-sort tree / Fenwick offline classic
- [ ] [XOR on Segment](https://codeforces.com/problemset/problem/242/E) — `Codeforces` `2000` — range XOR + range sum — **(core)** 20 bit-segtrees or lazy XOR flipping bit-counts
- [ ] [SUM and REPLACE](https://codeforces.com/problemset/problem/920/F) — `Codeforces` `2000` — replace \(a_i\) by \(d(a_i)\), range sum — **(core)** beats-adjacent: skip if segment already all \(\le 2\); divisor chain is short
- [ ] [Danil and a Part-time Job](https://codeforces.com/problemset/problem/877/E) — `Codeforces` `2000` — subtree flip + count 1s — Euler tour + lazy XOR on binary array
- [ ] [Infinite Inversions](https://codeforces.com/problemset/problem/540/E) — `Codeforces` `2100` — inversions after sparse swaps — **(stretch)** compress + Fenwick / merge-sort count
- [ ] [New Year Tree](https://codeforces.com/problemset/problem/620/E) — `Codeforces` `2100` — subtree color assign + distinct colors — **(stretch)** Euler + lazy assign bitmask (≤60 colors)
- [ ] [Circular RMQ](https://codeforces.com/problemset/problem/52/C) — `Codeforces` `2200` — circular range add + range min — **(stretch)** lazy add/min; split wrap-around into ≤2 segments
- [ ] [Army Creation](https://codeforces.com/problemset/problem/813/E) — `Codeforces` `2200` — count with last-\(k\) occurrence constraint — **(stretch)** merge-sort tree / persistent on previous positions
- [ ] [Valera and Queries](https://codeforces.com/problemset/problem/369/E) — `Codeforces` `2200` — how many segments cover \([x,y]\) fully — **(stretch)** offline + Fenwick / merge-sort on endpoints
- [ ] [The Child and Sequence](https://codeforces.com/problemset/problem/438/D) — `Codeforces` `2300` — range mod + point set + range sum — **(stretch)** USACO Guide beats intro; break if `max < mod`
- [ ] [A Simple Task](https://codeforces.com/problemset/problem/558/E) — `Codeforces` `2300` — range sort substring — **(stretch)** 26 lazy count-segtrees (or one with assign); CF lazy milestone

## Must-internalize checklist (5-10 bullets)
- Lazy skeleton: on update/query, if fully covered apply tag + return; else `push`, recurse, `pull`. Never read a child without pushing the parent first.
- Tag algebra: identity + `compose(new, old)` + `apply(tag, node, len)`. Assign overrides everything; add stacks; affine \((b_1,c_1)\circ(b_2,c_2)=(b_1b_2,\ b_1c_2+c_1)\).
- Node payloads beyond sum/min: `(sum, len)`, `(sum, best_pref)`, `(zeros, ones, inv)`, `(pref_ones, suf_ones, best, len)` — merge must be associative.
- Walk / descent: first index with prefix sum \(\ge x\) (Restore Permutation / Hotel-style) still works with lazy if you push on the way down.
- Beats rule of thumb: store `max` (and often `max2` / `cnt_max`); `break` if update cannot change the node; `tag` if update is uniform on the node; else recurse. Prove via potential (\(\sum \log a_i\), distinct values, …).
- Merge-sort tree: each node holds sorted values of its range; build \(O(n\log n)\) memory/time; count \(\le x\) = binary-search on \(O(\log n)\) nodes \(\Rightarrow O(\log^2 n)\). Prefer Fenwick+offline when it fits — same answers, lighter constants.
- Euler tour + lazy: subtree = contiguous `[tin, tout)` — flip/assign/color problems reduce to 1D lazy (Danil, New Year Tree, Water Tree family).
- Defaults that WA: forget `push` before recurse; wrong assign/add priority; `int` overflow on sum; off-by-one on half-open ACL ranges vs inclusive CSES/CF.

## Where it appears in OAs / interviews
- “Support range increment and range sum on \(n,q\le 10^5\)” → CSES Range Updates and Sums / Horrible Queries shape (backend analytics / spreadsheet cell ranges).
- “Flip bits on a range / XOR a range, then query sum” → CF 242E / Danil-style; bitset or 20 parallel trees.
- “Count inversions / how many values in \([L,R]\) are \(\le x\)” → Fenwick or merge-sort tree (Enemy is weak / Tufurama family); interview cousin of LC 315.
- Full segtree-beats (range mod / chmin) almost never appears in placement OAs — treat as CF Div1/ Div2 D–E rating stretch after lazy is automatic.
