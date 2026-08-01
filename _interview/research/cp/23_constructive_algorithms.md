# 23 — Constructive Algorithms

**Placement value:** High — Div2 B/C (often D) constantly ask “build any valid array/string/graph/ops”; OAs rephrase the same as “return one feasible configuration / -1”.
**Prereq topics:** Arrays & strings, greedy sorting, basic parity/math, BFS/DFS on grids & trees, XOR / bit ops (no fancy DS required).
**Pattern in one paragraph:** You must **output an object** (array, permutation, string, coloring, edge labels, operation list) that meets stated constraints — not just decide YES/NO. Recognize it from “construct any”, “print one example”, “find a sequence of ≤K ops”, or “impossible → -1”. Workflow: (1) find a clean **existence condition**, (2) invent the **simplest** family of answers (period, powers of two, checkerboard, SPF labels, greedy heap), (3) prove/adjust edge cases by small hand constructions — judge accepts any valid object.

## Ladder (easy -> hard, 27 problems)

- [ ] [Binary String Constructing](https://codeforces.com/problemset/problem/1003/B) — `Codeforces` `1300` — 0/1 string with exact adjacent diffs — **(core)** — classic “place the scarcer bit to create exactly `x` transitions”
- [ ] [Dividing the numbers](https://codeforces.com/problemset/problem/899/C) — `Codeforces` `1300` — partition `{1..n}` into two close sums — **(core)** — OA-style set construction; sum parity + take every other / greedy from `n`
- [ ] [Ehab and a Special Coloring Problem](https://codeforces.com/problemset/problem/1174/C) — `Codeforces` `1300` — label `2..n` by smallest prime factor — **(core)** — sieve-flavored construction; colors = distinct primes used
- [ ] [Labs](https://codeforces.com/problemset/problem/1236/C) — `Codeforces` `1300` — fill `n×n` so row sums are unique — zigzag columns; teaches “shape the matrix, don’t search”
- [ ] [Nastia and a Good Array](https://codeforces.com/problemset/problem/1521/B) — `Codeforces` `1300` — ops so every adjacent `gcd > 1` — replace with min and multiples; CF Div2 B constructive staple
- [ ] [Team](https://codeforces.com/problemset/problem/401/C) — `Codeforces` `1400` — build 01-string under run limits — **(core)** — place majority bit in blocks then inject the other; impossible-case first
- [ ] [Game With Array](https://codeforces.com/problemset/problem/1355/D) — `Codeforces` `1400` — sum `S`, no subsequence sum `S/2` — **(core)** — `S−n+1` then `1`s; YES iff `S` odd or `S ≥ 2n`
- [ ] [Make Good](https://codeforces.com/problemset/problem/1270/C) — `Codeforces` `1400` — append ≤3 nums so `sum = 2·xor` — **(core)** — XOR/sum invariant construction; very common Div2 C trick
- [ ] [Phoenix and Towers](https://codeforces.com/problemset/problem/1515/C) — `Codeforces` `1400` — assign blocks to `m` towers, height diff ≤`x` — **(core)** — always put next block on current shortest (heap); “any” + feasibility check
- [ ] [Not Assigning](https://codeforces.com/problemset/problem/1627/C) — `Codeforces` `1400` — label tree edges with primes, path gcd >1 iff length ≥2 — path graph only; alternate `2` and `3` on the chain
- [ ] [Binary String To Subsequences](https://codeforces.com/problemset/problem/1399/D) — `Codeforces` `1500` — split into min increasing 01-subsequences — **(core)** — queue of free colors ending in `0`/`1`; OA-flavored greedy assign
- [ ] [Ehab and Path-etic MEXs](https://codeforces.com/problemset/problem/1325/C) — `Codeforces` `1500` — edge labels maximizing min path-MEX — put `0,1,2` on a degree-≥3 vertex’s three edges (else line)
- [ ] [Binary String Reconstruction](https://codeforces.com/problemset/problem/1352/F) — `Codeforces` `1500` — build string from `(n0,n1,n2)` pair-counts — **(core)** — chain `00…011…11` / handle pure `n1`; Div2 F constructive
- [ ] [Special Permutation](https://codeforces.com/problemset/problem/1352/G) — `Codeforces` `1600` — perm with `2 ≤ |p_i−p_{i+1}| ≤ 4` — **(core)** — pattern `n-1,n-3,…` then odds/evens; impossible for `n≤3`
- [ ] [Constructing the Array](https://codeforces.com/problemset/problem/1353/D) — `Codeforces` `1600` — fill zeros by longest-mid priority — **(core)** — max-heap of segments; famous Div2 D construction
- [ ] [Balance the Bits](https://codeforces.com/problemset/problem/1503/A) — `Codeforces` `1600` — two RBS agreeing where `s[i]='1'` — force `(` on first `1`, mirror/`swap` on `0`s; count `1`s even
- [ ] [Fence Painting](https://codeforces.com/problemset/problem/1481/C) — `Codeforces` `1600` — assign painters; last paint must stick — map each color → positions still needing it; last painter is the bottleneck
- [ ] [Construct Sequences](https://atcoder.jp/contests/agc007/tasks/agc007_b) — `AtCoder` `AGC007 B (400)` — incr `a`, decr `b`, ordered `a+b` along perm — **(core)** — `a_i=i·N+q_i`, `b_i=(N+1−i)·N+q_i`; AtCoder construction classic
- [ ] [Ehab the Xorcist](https://codeforces.com/problemset/problem/1325/D) — `Codeforces` `1700` — array with given XOR `u` and sum `v` — **(stretch)** — empty / `[u]` / `[x,x]` / `[u,x,x]` by parity of `v−u`
- [ ] [Link Cut Centroids](https://codeforces.com/problemset/problem/1406/C) — `Codeforces` `1700` — one edge move → unique centroid — **(stretch)** — find centroids; if two, rehang a leaf onto one
- [ ] [Diane](https://codeforces.com/problemset/problem/1554/D) — `Codeforces` `1800` — string with exactly `n` distinct substrings — **(stretch)** — `a…aba…a` (or all `a`); substring-count constructions
- [ ] [Edge Weight Assignment](https://codeforces.com/problemset/problem/1338/B) — `Codeforces` `1800` — min/max #distinct path-XORs on tree — **(stretch)** — min is `1` or `3` by leaf-parity; max = `n−1−(#non-leaf edges skipped)`
- [ ] [Extreme Subtraction](https://codeforces.com/problemset/problem/1442/A) — `Codeforces` `1800` — subtract prefixes/suffixes to zero — **(stretch)** — diff-array / monotone residual; “can construct ops” ↔ inequality
- [ ] [A/B Matrix](https://codeforces.com/problemset/problem/1360/G) — `Codeforces` `1900` — `0/1` matrix with given row/col sums — **(stretch)** — cyclic diagonal bands; existence `n·a = m·b`
- [ ] [Replace by MEX](https://codeforces.com/problemset/problem/1375/D) — `Codeforces` `1900` — sort array using MEX replacements — **(stretch)** — while unsorted, write MEX into a wrong index (or park `n`); ≤`2n` ops
- [ ] [Engineer Artem](https://codeforces.com/problemset/problem/1438/C) — `Codeforces` `2000` — +0/+1 so no equal adjacent — **(stretch)** — checkerboard parity bump; always possible
- [ ] [Coloring Edges](https://codeforces.com/problemset/problem/1217/D) — `Codeforces` `2100` — edge-color digraph so no mono cycle — **(stretch)** — `1` color if DAG; else `2` (tree-edge vs back-edge by DFS timestamp)

## Must-internalize checklist (5-10 bullets)

- Existence first: write the `NO`/`-1` condition (parity, sum bounds, degree, count of `1`s even, `n` small) before inventing the object.
- Prefer a **simple parametric family**: periods, powers of two, all-`1`s + one big, SPF/prime labels, checkerboard, zigzag columns.
- Casework on `n mod k` / parity / “has a high-degree vertex?” — most Div2 constructive splits into 2–4 cases, each with a fixed pattern.
- “Any answer”: do not minimize unless asked; loose length/ops bounds (`≤2n`, `≤1e4`) are invitations to a dumb correct construction.
- Operation constructions: prove an **upper bound** on ops, then emit a sequence that always stays under it (Prefix-Flip / MEX-sort / centroid-move style).
- Graph/tree constructions: put extreme labels on a star/centroid/degree-3 vertex; paths and bipartite 2-colorings are the default toolkit.
- Bracket / 01 / RBS constructions: maintain balance counters; build both strings together when they must agree on a mask.
- Debug by writing a local checker for small `n` (brute all outputs vs your pattern) — constructive bugs are almost always missed edge cases.

## Where it appears in OAs / interviews

- “Return any array of length `n` with sum `S` and no subarray / subset equal to `X`” → Game With Array / Make Good style existence + one explicit array.
- “Rearrange / rebuild a binary string under run or transition constraints” → Team / Binary String Constructing; common phone-screen variant.
- “Assign tasks/blocks to `k` workers so loads differ by at most `x`” → Phoenix and Towers (greedy to current minimum).
- “Output operations that transform A into B / sort A under a weird op (MEX, prefix flip, paint)” → operation-list constructive with a proven `O(n)` bound (Replace by MEX / Fence Painting).
