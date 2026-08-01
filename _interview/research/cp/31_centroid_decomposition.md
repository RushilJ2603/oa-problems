# 31 — Centroid decomposition on trees

**Placement value:** Medium — almost never a literal OA template; shows up as “balanced root / subtree ≤ n/2” intuition and as a Candidate Master tree-path / offline-query weapon Striver never covers.
**Prereq topics:** Tree DFS + subtree sizes, basic tree DP (path aggregates), Fenwick/BIT (for range path counts), binary lifting / LCA helpful for distance queries on the centroid tree
**Pattern in one paragraph:** A **centroid** is a node whose removal leaves every component of size ≤ ⌊n/2⌋ (every tree has 1 or 2 adjacent centroids). **Centroid decomposition** repeatedly finds a centroid, processes all paths that pass through it, marks it removed, and recurses on the remaining components — depth O(log n), total work typically O(n log n) times the per-centroid scan. Build an explicit **centroid tree** (parent = previous centroid) of height O(log n) when you need updates/queries: every original path is covered by some centroid ancestor. Signal words: count/sum paths with a property (length, XOR, GCD, palindrome mask), paint/update a node then query nearest / best path, assign ranks so same-rank pairs are separated by a higher rank, “make the centroid unique”, or construct a balanced rooted tree whose LCAs lie on original paths.

## Ladder (easy -> hard, 20 problems)

- [ ] [Finding a Centroid](https://cses.fi/problemset/task/2079) — `CSES` `Tree Algorithms` — find one centroid — **(core)** CSES / USACO Guide / cp-algorithms entry drill; write `sz` DFS + walk-to-heavy-child template
- [ ] [Minimize Sum of Distances](https://atcoder.jp/contests/abc348/tasks/abc348_e) — `AtCoder` `ABC348 E (475)` — weighted centroid — **(core)** min ∑ C_i·dist(v,i) is at the weight-balanced centroid; motivates “why centroid”
- [ ] [Link Cut Centroids](https://codeforces.com/problemset/problem/1406/C) — `Codeforces` `1700` — 1–2 centroids / edge move — **(core)** modern Div2; find both centroids, cut/relink so exactly one remains
- [ ] [Distance in Tree](https://codeforces.com/problemset/problem/161/D) — `Codeforces` `1800` — count paths length = k — **(core)** VK Cup classic; tree DP or first full CD “paths through centroid” practice
- [ ] [Fixed-Length Paths I](https://cses.fi/problemset/task/2080) — `CSES` `Advanced Techniques` — CD path count = k — **(core)** *the* CD counting template (USACO Guide / cp-algorithms); bag of depths across children
- [ ] [Fixed-Length Paths II](https://cses.fi/problemset/task/2081) — `CSES` `Advanced Techniques` — CD path count in [k1,k2] — **(core)** same decompose + Fenwick/prefix on depths; CSES / USACO Guide
- [ ] [GCD Counting](https://codeforces.com/problemset/problem/1101/D) — `Codeforces` `2000` — longest path with GCD > 1 — Div2 D; path property on values (tree DP gateway before full CD GCD)
- [ ] [Village (Minimum)](https://codeforces.com/problemset/problem/1387/B1) — `Codeforces` `2100` — Baltic OI remap — pair nodes via a rooted tour; warm-up sibling before the CD maximum version
- [ ] [Ciel the Commander](https://codeforces.com/problemset/problem/321/C) — `Codeforces` `2100` — CD ranks A–Z — **(core)** USACO Guide / CF blog staple; centroid gets next letter, recurse — proves depth ≤ 26
- [ ] [Mahmoud and a xor trip](https://codeforces.com/problemset/problem/766/E) — `Codeforces` `2100` — sum of path XORs — **(core)** bit-wise path aggregates via CD or tree DP; transfer pattern from length-counts to XOR
- [ ] [Centroids](https://codeforces.com/problemset/problem/708/C) — `Codeforces` `2300` — move one edge → is v a centroid? — **(stretch)** for every v: reroot sizes + one edge relocation casework
- [ ] [Alternating Tree](https://codeforces.com/problemset/problem/960/E) — `Codeforces` `2300` — alternating path sums — **(stretch)** CD / DnC path contribution with signs
- [ ] [Balanced Tree](https://atcoder.jp/contests/abc291/tasks/abc291_h) — `AtCoder` `ABC291 Ex (600)` — build centroid tree — **(stretch)** output parents of the decomposition; forces explicit CD construction
- [ ] [Xenia and Tree](https://codeforces.com/problemset/problem/342/E) — `Codeforces` `2400` — paint red + nearest red — **(stretch)** *the* CD-tree query classic (USACO Guide focus); update/query via O(log n) centroid ancestors
- [ ] [Palindromes in a Tree](https://codeforces.com/problemset/problem/914/E) — `Codeforces` `2400` — palindromic paths per vertex — **(stretch)** CD + bitmask frequency of labels on paths
- [ ] [GCD Counting](https://codeforces.com/problemset/problem/990/G) — `Codeforces` `2400` — count pairs by path GCD — **(stretch)** full CD + number-theoretic convolution over gcd buckets
- [ ] [Village (Maximum)](https://codeforces.com/problemset/problem/1387/B2) — `Codeforces` `2500` — Baltic OI + centroid — **(stretch)** USACO Guide; maximize remap cost via centroid decomposition / small-to-large
- [ ] [Digit Tree](https://codeforces.com/problemset/problem/715/C) — `Codeforces` `2700` — path digits mod m — **(stretch)** USACO Guide / cp-algorithms; CD + modular inverse counting
- [ ] [Close Vertices](https://codeforces.com/problemset/problem/293/E) — `Codeforces` `2700` — count close pairs — **(stretch)** CF blog CD list classic; paths with length & weight constraints via CD + BIT
- [ ] [Double Tree](https://codeforces.com/problemset/problem/1140/G) — `Codeforces` `2700` — queries on two mirrored trees — **(stretch)** USACO Guide; CD / DnC across a product-like tree metric

## Must-internalize checklist (5-10 bullets)

- Find a centroid in O(n): compute `sz[]`, start anywhere, keep moving to a neighbor with `sz[child] > n/2` (or check parent-side `n - sz[v]`); stop when all sides ≤ n/2.
- Every tree has one or two centroids; if two, they are adjacent (even n split). `1406C` is the constructive drill.
- CD loop: `get_sz` → `get_centroid` → `process` paths through it → `removed[c]=true` → recurse on each adjacent live component. Never walk into `removed` nodes.
- Path coverage: every u–v path is processed exactly when the first centroid on that path (in the decomposition) is the current centroid — count by combining child bags, then add the child’s bag.
- Complexity: each node lies in O(log n) live components ⇒ O(n log n) · (work per visit). Keep process linear in component size (clear arrays only up to `max_depth`, not full `O(n)` memset each time).
- Explicit centroid tree: `par_cd[c] = previous centroid`; height O(log n). Store dist(node, centroid-ancestor) (precomputed) for O(log n) updates/queries (`342E`).
- Rank / construct pattern (`321C`, `ABC291H`): assign the current centroid the next layer / parent link, then recurse — layers ≤ log₂ n.
- When CD is overkill: pure tree DP / rerooting / DSU-on-tree may suffice (e.g. fixed small k, or subtree-only queries). Reach for CD when the constraint is **global paths** with n ≤ 1e5 and no root-given structure.

## Where it appears in OAs / interviews

- Almost never “implement centroid decomposition” in placement OAs; the diluted form is “pick a capital / warehouse so no branch is too large” or “minimize total distance to clients” → single centroid / weighted centroid (`ABC348E`), not full recurse.
- “Assign managers / ranks so peers communicate only through a superior” → same structure as `321C` (balanced hierarchy = CD layers).
- Harder online assessments / ICPC-style screens: count pairs of nodes whose path satisfies a property (length, XOR, GCD) under n = 1e5 → Fixed-Length Paths / `161D` / `766E` family.
- Rare take-home / onsite CM-ish round: dynamic “paint a node, query closest painted” on a tree → Xenia-style centroid tree + ancestor mins (`342E`).
