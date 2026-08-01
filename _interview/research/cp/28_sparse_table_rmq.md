# 28 — Sparse table & RMQ (idempotent range queries, LCA via RMQ)

**Placement value:** Medium — static min/max/GCD queries are the “no updates” twin of Fenwick/segtree in OAs; writing an \(O(1)\) RMQ template is a common CF Div2 D skill. LCA-via-Euler+RMQ is mostly a rating stretch (binary lifting alone covers most interviews).
**Prereq topics:** Prefix sums / difference arrays, bit tricks (`floor(log2)`), GCD, basic rooted trees + DFS (for the LCA half)
**Pattern in one paragraph:** Array never changes and you need many range aggregates of an *idempotent* op (min, max, GCD, AND, OR, LCM) → sparse table: precompute `st[k][i] = op` on \([i, i+2^k)\), then answer \([L,R]\) with **two overlapping** blocks of length \(2^{\lfloor\log_2(R-L+1)\rfloor}\). Overlap is legal exactly because \(op(x,x)=x\). Do **not** use the two-block trick for sum/XOR (use prefix); if updates appear, switch to Fenwick/segtree. Same RMQ on an Euler tour of depths turns LCA into “argmin depth between first occurrences.” Signal words: static array, \(n,q\le 2\cdot10^5\), range min/max/GCD, “no modifications,” binary search + range check, tree distance / lowest common ancestor with huge \(q\).

## Ladder (easy -> hard, ~18-28 problems)
- [ ] [Resort Hotel](https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_j) — `AtCoder` `Tessoku A10` — pref/suf max — warm-up: max outside a blocked segment; same “static range max” mindset before the ST table
- [ ] [Static Range Minimum Queries](https://cses.fi/problemset/task/1647) — `CSES` `Range Queries` — sparse RMQ template — **(core)** CSES / cp-algorithms / USACO-Guide classic; memorize build + two-block query
- [ ] [Union of Two Sets](https://atcoder.jp/contests/abc282/tasks/abc282_f) — `AtCoder` `ABC282 F (500)` — two power-of-two covers — **(core)** interactive; forces the sparse-table covering idea without coding a table
- [ ] [Rorororobot](https://codeforces.com/problemset/problem/1709/D) — `Codeforces` `1700` — sparse max + binsearch — **(core)** column-height max on path; modern Div2 D “ST + check”
- [ ] [Maximum modulo equality](https://codeforces.com/problemset/problem/2050/F) — `Codeforces` `1700` — sparse GCD on diffs — **(core)** \(m=\gcd\) of adjacent \(|a_{i+1}-a_i|\) on \([l,r)\); OA-adjacent GCD-RMQ
- [ ] [Max GEQ Sum](https://codeforces.com/problemset/problem/1691/D) — `Codeforces` `1800` — sparse max + expand — longest subarray with \(\max \ge\) sum; ST answers range max while two pointers / stacks grow
- [ ] [Array Stabilization (GCD version)](https://codeforces.com/problemset/problem/1547/F) — `Codeforces` `1900` — binsearch + range GCD — **(core)** cp-algorithms listed; circular → double array, ST for \(O(1)\) GCD
- [ ] [Skyscrapers (hard version)](https://codeforces.com/problemset/problem/1313/C2) — `Codeforces` `1900` — range max / “peak” — build left/right via stack or ST; rating-builder for static RMQ intuition
- [ ] [Company Queries II](https://cses.fi/problemset/task/1688) — `CSES` `Tree Algorithms` — LCA (Euler+RMQ or binlift) — **(core)** implement LCA; prefer Euler tour + sparse RMQ once for this topic
- [ ] [Distance Queries](https://cses.fi/problemset/task/1135) — `CSES` `Tree Algorithms` — LCA distances — **(core)** `dep[u]+dep[v]-2·dep[lca]`; mandatory after Company Queries II
- [ ] [Tree Queries](https://codeforces.com/problemset/problem/1328/E) — `Codeforces` `1900` — LCA / ancestor checks — **(core)** “do vertices lie on one path?”; tin/tout or LCA casework
- [ ] [Fools and Roads](https://codeforces.com/problemset/problem/191/C) — `Codeforces` `1900` — path +1 via LCA — difference on tree edges; LCA endpoints then push counts up
- [ ] [CGCDSSQ](https://codeforces.com/problemset/problem/475/D) — `Codeforces` `2000` — range GCD segments — **(core)** cp-algorithms staple; how GCD drops along expanding prefixes
- [ ] [New Year Concert](https://codeforces.com/problemset/problem/1632/D) — `Codeforces` `2000` — GCD ST + two pointers — **(core)** count prefixes whose range GCD becomes \(1\); modern GCD-RMQ drill
- [ ] [Pair of Numbers](https://codeforces.com/problemset/problem/359/D) — `Codeforces` `2000` — GCD = range min — longest \([l,r]\) with \(\gcd=\min\); two STs (or ST+scan)
- [ ] [R2D2 and Droid Army](https://codeforces.com/problemset/problem/514/D) — `Codeforces` `2000` — binsearch + multi ST max — **(core)** cp-algorithms listed; \(k\) attribute sparse tables inside check
- [ ] [Yet Another Yet Another Task](https://codeforces.com/problemset/problem/1359/D) — `Codeforces` `2000` — subarray sum − max — maximize sum with a constrained maximum; ST/stack over candidate peaks
- [ ] [Turn Off The TV](https://codeforces.com/problemset/problem/863/E) — `Codeforces` `2000` — coverage + range min — **(stretch)** compress endpoints; ST/segtree to test if a segment is redundant
- [ ] [1-Trees and Queries](https://codeforces.com/problemset/problem/1304/E) — `Codeforces` `2000` — LCA + extra edge — **(stretch)** three path combos with one added edge; O(1) LCA shines
- [ ] [Ant colony](https://codeforces.com/problemset/problem/474/F) — `Codeforces` `2100` — GCD RMQ + count equals — **(stretch)** cp-algorithms / topic-20 adjacent; how many \(a_i\) equal range GCD
- [ ] [Minimum spanning tree for each edge](https://codeforces.com/problemset/problem/609/E) — `Codeforces` `2100` — max on tree path — **(stretch)** Kruskal MST + binary-lift/ST max on path; classic “RMQ on tree”
- [ ] [Cut](https://codeforces.com/problemset/problem/1516/D) — `Codeforces` `2100` — doubling / next coprime — **(stretch)** sparse-table-style \(2^k\) jumps on “next conflict” positions
- [ ] [Blood Cousins](https://codeforces.com/problemset/problem/208/E) — `Codeforces` `2100` — k-th ancestor + depth bags — **(stretch)** lift then count same-depth in subtree (binlift + Euler/DSU-on-tree)
- [ ] [A and B and Lecture Rooms](https://codeforces.com/problemset/problem/519/E) — `Codeforces` `2100` — LCA midpoint counting — **(stretch)** nodes equidistant from two vertices; heavy lifting casework

## Must-internalize checklist (5-10 bullets)
- Idempotent ops only for \(O(1)\) two-block query: min, max, GCD, AND, OR, LCM. Sum/XOR → prefix (or disjoint sparse table `(stretch)`).
- Build: `st[0][i]=a[i]`; `st[k][i]=op(st[k-1][i], st[k-1][i+2^{k-1}])` for all `i+2^k≤n`. Space/time \(O(n\log n)\).
- Query \([L,R]\): `k=floor(log2(R-L+1))`; `op(st[k][L], st[k][R-2^k+1])`. Precompute `lg[]` or use `__builtin_clz`.
- Static vs dynamic: no updates → sparse; point/range updates → Fenwick/segtree. Never rebuild ST per query.
- Indexing: be consistent 0- vs 1-based; empty range / `L>R` guard; `long long` when combining values, `int` fine for indices.
- GCD-RMQ patterns: stabilize arrays (1547F), count bad prefixes (1632D), \(\gcd\) of diffs for modular equality (2050F).
- Binary search + ST check: monotone “length / threshold / shots” predicates (1709D, 514D, 1547F).
- LCA via RMQ: Euler tour of nodes + depth array + `first[v]`; `LCA(u,v)=euler[rmq_argmin(first[u], first[v])]`. Equivalent to binary lifting; prefer ST when \(q\) is huge or you already have Euler.
- Tree path aggregates: distance via depths; max/GCD on path → lift with stored op, or Euler+HLD/segtree (609E / Ant colony style).

## Where it appears in OAs / interviews
- “Many range minimum / maximum queries, array immutable” → CSES Static RMQ / NumArray-without-updates; interviewers expect “sparse table or segtree,” sparse is the sharper answer.
- “Range GCD / AND of a subarray after preprocessing” → 2050F / 1547F shape; sometimes disguised as “largest modulus where all equal.”
- “First index where running GCD becomes 1 / array stabilizes under neighbor GCD” → 1632D / 1547F; OA-adjacent number-theory + DS combo.
- “Lowest common manager / distance in org chart with \(10^5\) queries” → CSES Company/Distance Queries (LCA); Euler+RMQ is acceptable if you can explain the reduction.
