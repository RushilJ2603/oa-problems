# 17 — Trees CF-style beyond Striver (LCA / binary lifting, Euler tour, rerooting, DSU-on-tree)

**Placement value:** Medium-High — OAs rarely need full LCA templates, but tree DFS/DP, subtree aggregates, and “answer for every root” show up constantly; the CF stretch (binary lifting, Euler+BIT, small-to-large) is the path from “knows trees” to Candidate Master tree problems.
**Prereq topics:** DFS/BFS on trees, basic tree DP (subtree sizes), Fenwick/segment tree (for Euler-tour problems), binary lifting intuition from sparse tables.

**Pattern in one paragraph:** Root the tree (or try every root via rerooting). Flatten with an Euler / DFS tour so a subtree becomes a contiguous `[tin, tout]` range — then Fenwick/segtree answers subtree and root→node path queries. Precompute `up[k][v] = 2^k`-th ancestor for k-th ancestor and LCA in \(O(\log n)\) (distance = `dep[u]+dep[v]-2·dep[lca]`). When every subtree needs a frequency bag, merge small→large (DSU-on-tree / sack) in \(O(n\log n)\). When the answer must be reported for every choice of root, do one downward DP then a second DFS that transfers the root across each edge (rerooting). Signal words: company hierarchy / boss queries, subtree sum after updates, path through an extra edge, “for each vertex as capital/root”, dominant color in subtree.

## Ladder (easy -> hard, 26 problems)

- [ ] [Queen](https://codeforces.com/problemset/problem/1143/C) — `Codeforces` `1400` — tree DFS / respect — Delete nodes whose every child is respectful; CF-style observation on rooted trees.
- [ ] [Cut 'em all!](https://codeforces.com/problemset/problem/982/C) — `Codeforces` `1500` — even subtree cuts — Max edges to cut so every component has even size; classic subtree-parity greedy. **(core)**
- [ ] [Journey](https://codeforces.com/problemset/problem/839/C) — `Codeforces` `1500` — tree expected length — Probability DFS to leaves; teaches “branching factor − parent” tree DP.
- [ ] [Alyona and the Tree](https://codeforces.com/problemset/problem/682/C) — `Codeforces` `1600` — path-max DFS prune — Drop subtree when path condition breaks; CF Div2 tree DFS staple.
- [ ] [Ki](https://atcoder.jp/contests/abc138/tasks/abc138_d) — `AtCoder` `ABC D (400)` — subtree add / push-down — Add on subtree root, DFS-push prefixes; Euler/imos-on-tree warm-up (USACO Guide–adjacent). **(core)**
- [ ] [Tree Distances II](https://cses.fi/problemset/task/1133) — `CSES` `Tree Algorithms` — rerooting sum-of-dist — USACO Guide “all roots” focus; `ans[child] = ans[parent] + n − 2·sz[child]`. **(core)**
- [ ] [Tree Distances I](https://cses.fi/problemset/task/1132) — `CSES` `Tree Algorithms` — rerooting / two farthest — Per-node eccentricity via down+up maxima (or diameter endpoints).
- [ ] [Company Queries I](https://cses.fi/problemset/task/1687) — `CSES` `Tree Algorithms` — k-th ancestor binary lifting — USACO Guide binary-jump focus problem; write `up[LOG][n]` first. **(core)**
- [ ] [Company Queries II](https://cses.fi/problemset/task/1688) — `CSES` `Tree Algorithms` — LCA via binary lifting — Equalize depth, jump together; the LCA template. **(core)**
- [ ] [Distance Queries](https://cses.fi/problemset/task/1135) — `CSES` `Tree Algorithms` — LCA distances — `dep[u]+dep[v]-2·dep[lca]`; mandatory after Company Queries. **(core)**
- [ ] [Choosing Capital for Treeland](https://codeforces.com/problemset/problem/219/D) — `Codeforces` `1700` — rerooting reverse-edge count — Canonical CF rerooting: min edges to reorient toward each capital. **(core)**
- [ ] [Subtree Queries](https://cses.fi/problemset/task/1137) — `CSES` `Tree Algorithms` — Euler tour + Fenwick — USACO Guide Euler module; subtree = `[tin, tout]` point-update range-sum. **(core)**
- [ ] [Path Queries](https://cses.fi/problemset/task/1138) — `CSES` `Tree Algorithms` — Euler + path-to-root BIT — Range-update on subtree ⇒ point query root→node sum (and LCA for u–v). **(core)**
- [ ] [Counting Paths](https://cses.fi/problemset/task/1136) — `CSES` `Tree Algorithms` — tree difference + LCA — Mark path endpoints, push diffs up; CSES / USACO Guide classic. **(core)**
- [ ] [Distinct Colors](https://cses.fi/problemset/task/1139) — `CSES` `Tree Algorithms` — small-to-large merge — USACO Guide; merge `set`s by size for distinct colors per subtree — gateway to DSU-on-tree. **(core)**
- [ ] [Distance in Tree](https://codeforces.com/problemset/problem/161/D) — `Codeforces` `1800` — tree DP k-paths — Count pairs at distance `k`; VK Cup classic, also rerooting-flavored.
- [ ] [Tree with Maximum Cost](https://codeforces.com/problemset/problem/1092/F) — `Codeforces` `1900` — rerooting weighted — Transfer `sum`/`cost` across edges; CF rerooting drill after CSES.
- [ ] [Tree Queries](https://codeforces.com/problemset/problem/1328/E) — `Codeforces` `1900` — LCA / ancestor check — Path covers vertices iff all lie under one child of LCA (Euler `tin/tout` or lift). **(core)**
- [ ] [Propagating tree](https://codeforces.com/problemset/problem/383/C) — `Codeforces` `2000` — Euler + parity Fenwick — Odd/even depth sign flips; tree→array DS pattern. **(stretch)**
- [ ] [Danil and a Part-time Job](https://codeforces.com/problemset/problem/877/E) — `Codeforces` `2000` — Euler + lazy segtree — Subtree flip / count-of-1s; lazy on tour ranges. **(stretch)**
- [ ] [1-Trees and Queries](https://codeforces.com/problemset/problem/1304/E) — `Codeforces` `2000` — LCA + extra edge — Distances with one added edge: check three path combinations. **(stretch)**
- [ ] [Passable Paths (hard version)](https://codeforces.com/problemset/problem/1702/G2) — `Codeforces` `2000` — multi-path LCA — Compress marked nodes via LCA depths; CF 1700s–2000s tree-query staple. **(stretch)**
- [ ] [Blood Cousins](https://codeforces.com/problemset/problem/208/E) — `Codeforces` `2100` — k-th ancestor + depth bags — Lift to p-th ancestor, count same-depth in subtree (binlift + Euler/DSU-on-tree). **(stretch)**
- [ ] [A and B and Lecture Rooms](https://codeforces.com/problemset/problem/519/E) — `Codeforces` `2100` — LCA midpoint counting — Nodes equidistant from two rooms; heavy binary-lifting casework. **(stretch)**
- [ ] [Tree Painting](https://codeforces.com/problemset/problem/1187/E) — `Codeforces` `2100` — rerooting score — Maximize paint score over start vertex; CF rerooting milestone. **(stretch)**
- [ ] [Lomsat gelral](https://codeforces.com/problemset/problem/600/E) — `Codeforces` `2300` — DSU-on-tree (sack) — *The* Arpa tutorial problem: sum of dominating colors per subtree; keep heavy child’s map. **(stretch)**

## Must-internalize checklist

- Binary lifting table: `up[0][v]=parent`, `up[k][v]=up[k-1][up[k-1][v]]`; k-th ancestor by bits; sentinel when jump leaves the tree.
- LCA: lift deeper node to same depth → joint lift while `up[k]` differ → parent is LCA; distance via depths.
- Euler tour: `tin/tout` (or in/out) so subtree of `v` is contiguous; ancestor test `tin[u]≤tin[v]≤tout[u]`.
- Subtree PURS: Fenwick/segtree on tour indices; point update at `tin[v]`, range query `[tin[v], tout[v]]`.
- Path-to-root via BIT: add `+x` at `tin[v]`, `-x` at `tout[v]+1` (range update); prefix to `tin[u]` = root→u; combine with LCA for u–v.
- Rerooting: DFS1 subtree DP → DFS2 transfer across edge using `sz` / contribution deltas (CSES Distances II formula as template).
- Small-to-large: always merge smaller `map`/`set` into larger; each element moves \(O(\log n)\) times → \(O(n\log^2 n)\) or \(O(n\log n)\) with sack.
- DSU-on-tree (sack): process light children and clear; keep heavy child’s bag; add lights; answer; clear if not kept.

## Where it appears in OAs / interviews

- **Org-chart / manager queries:** “k-th boss of employee” or “lowest common manager” → Company Queries I/II (binary lifting), rarely full CF LCA casework.
- **Subtree metrics after updates:** “sum/count in the department rooted at X” → Euler flatten + Fenwick (Subtree Queries / Ki), same shape as org HR dashboards in OAs.
- **Answer for every capital / warehouse:** “best root to minimize total distance / rewires” → rerooting DP (Tree Distances II, Choosing Capital); interview variant of “sum of distances in tree.”
- **Path feasibility on a tree:** “do these nodes lie on one path?” / “distance with one extra cable” → ancestor checks + LCA (Tree Queries, 1-Trees and Queries).
