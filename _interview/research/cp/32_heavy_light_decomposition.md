# 32 — Heavy-light decomposition (HLD)

**Placement value:** Medium — OAs almost never ask for a full HLD template, but “path / subtree update+query on a tree” is the CF skill that separates “knows Euler tour” from Candidate Master tree DS; Striver never covers it.
**Prereq topics:** Trees DFS (subtree sizes, parents, depths), LCA / binary lifting, Euler tour + Fenwick/segtree, lazy segment tree (for path/subtree range updates)

**Pattern in one paragraph:** Root the tree; mark the child with largest subtree as **heavy**, others **light**. Heavy edges form disjoint **chains**; assign contiguous segment-tree indices along each chain (heavy-first DFS — so each subtree is still a contiguous `[tin, tout]`). Any u–v path crosses \(O(\log n)\) light edges ⇒ \(O(\log n)\) chain segments ⇒ each path query/update is \(O(\log^2 n)\) with a segtree. Use HLD when you need **arbitrary path aggregates with updates** (max/min/sum/composite) that Euler+BIT alone cannot do (e.g. path max with point updates). Prefer Euler/tree-diff/binary-lifting when queries are only subtree, only root→node, or path sum without awkward ops. Signal words: path max/min under updates, paint path then query, path + subtree mixed updates, function composition along a path.

## Ladder (easy -> hard, 23 problems)

- [ ] [Company Queries II](https://cses.fi/problemset/task/1688) — `CSES` `Tree Algorithms` — LCA binary lifting — HLD queries climb chains; write solid LCA first. **(core)**
- [ ] [Distance Queries](https://cses.fi/problemset/task/1135) — `CSES` `Tree Algorithms` — path length via LCA — `dep[u]+dep[v]-2·dep[lca]`; baseline before weighted path DS.
- [ ] [Subtree Queries](https://cses.fi/problemset/task/1137) — `CSES` `Tree Algorithms` — Euler + Fenwick — **(core)** when you only need subtree PURS, skip HLD; tin/tout is the mental model HLD reuses.
- [ ] [Path Queries](https://cses.fi/problemset/task/1138) — `CSES` `Tree Algorithms` — Euler path-to-root — **(core)** root→node sum with updates via tour difference; shows HLD is overkill for this shape.
- [ ] [Counting Paths](https://cses.fi/problemset/task/1136) — `CSES` `Tree Algorithms` — tree difference + LCA — offline path += 1 without a segtree; know this escape hatch.
- [ ] [Fools and Roads](https://codeforces.com/problemset/problem/191/C) — `Codeforces` `1900` — path mark via LCA diff — **(core)** count edge loads; classic “don’t reach for HLD” CF path drill.
- [ ] [Tree Queries](https://codeforces.com/problemset/problem/1328/E) — `Codeforces` `1900` — ancestor / path cover — vertices on one path iff under one child of LCA; tin/tout or lift.
- [ ] [Vasya and a Tree](https://codeforces.com/problemset/problem/1076/E) — `Codeforces` `1900` — depth-capped subtree add — DFS + Fenwick on depth; tree DS without chains.
- [ ] [Propagating tree](https://codeforces.com/problemset/problem/383/C) — `Codeforces` `2000` — Euler + parity Fenwick — odd/even depth sign flips; tour technique before chain jumping.
- [ ] [Danil and a Part-time Job](https://codeforces.com/problemset/problem/877/E) — `Codeforces` `2000` — Euler + lazy flip — subtree flip / count-1s; lazy on tour ranges (HLD’s subtree half).
- [ ] [Path Queries II](https://cses.fi/problemset/task/2134) — `CSES` `Tree Algorithms` — HLD + path max — **(core)** *the* USACO Guide / cp-algorithms focus problem; point set + path maximum.
- [ ] [Vertex Add Path Sum](https://judge.yosupo.jp/problem/vertex_add_path_sum) — `Library Checker` `HLD verify` — path sum template — **(core)** canonical library check; lock the climb-`head[]` loop.
- [ ] [Distance Queries on a Tree](https://atcoder.jp/contests/abc294/tasks/abc294_g) — `AtCoder` `ABC294 G (600)` — edge update + path distance — **(core)** official editorial lists HLD; store edge weight on child vertex.
- [ ] [Vertex Add Subtree Sum](https://judge.yosupo.jp/problem/vertex_add_subtree_sum) — `Library Checker` `HLD verify` — subtree via HLD order — **(core)** heavy-first DFS ⇒ subtree = `[pos[v], pos[v]+sz[v])`; same array as path HLD.
- [ ] [On Changing Tree](https://codeforces.com/problemset/problem/396/C) — `Codeforces` `Div. 1 C (~2000)` — path/subtree weighted updates — **(core)** mix of root-path and subtree ops; HLD or Euler-with-depth trick.
- [ ] [Little Girl and Problem on Trees](https://codeforces.com/problemset/problem/276/E) — `Codeforces` `2100` — path add + path query — **(core)** old CF HLD classic; chains + BIT/segtree.
- [ ] [Water Tree](https://codeforces.com/problemset/problem/343/D) — `Codeforces` `2100` — subtree fill + path empty — **(core)** fill subtree, empty to root, query vertex; HLD or clever Euler+lazy.
- [ ] [Vertex Set Path Composite](https://judge.yosupo.jp/problem/vertex_set_path_composite) — `Library Checker` `HLD verify` — non-commutative path fold — **(stretch)** USACO Guide; compose \(ax+b\) u→v with two directions / two segtrees.
- [ ] [Tree Path Composite Sum](https://judge.yosupo.jp/problem/tree_path_composite_sum) — `Library Checker` `HLD verify` — weighted path composite — **(stretch)** harder monoid-on-path check after Vertex Set Path Composite.
- [ ] [Duff in the Army](https://codeforces.com/problemset/problem/587/C) — `Codeforces` `2200` — k smallest IDs on path — **(stretch)** HLD+segtree merge or binary lifting of sorted vectors.
- [ ] [Colorful Tree](https://atcoder.jp/contests/abc133/tasks/abc133_f) — `AtCoder` `ABC133 F (600)` — path distance w/ color override — **(stretch)** offline per-color fixups + LCA; HLD optional, path-query maturity check.
- [ ] [Subtree Minimum Query](https://codeforces.com/problemset/problem/893/F) — `Codeforces` `2300` — subtree min with depth cap — **(stretch)** persistent segtree on DFS order (or HLD-flavored); hard tree-DS milestone.
- [ ] [Jamie and Tree](https://codeforces.com/problemset/problem/916/E) — `Codeforces` `2400` — HLD + dynamic root — **(stretch)** famous “reroot queries” HLD; treat new root via LCA casework on paths.

## Must-internalize checklist

- Heavy child = largest `sz[child]`; `head[v]` = top of v’s chain; `pos[v]` = index in the single segtree; decompose heavy child first so chains (and subtrees) are contiguous.
- Light-edge lemma: each light step halves subtree size ⇒ any root→v path has \(O(\log n)\) light edges ⇒ \(O(\log n)\) chains on any u–v path.
- Path query loop: while `head[u] != head[v]`, lift the deeper head, segtree-query `[pos[head], pos[node]]`, jump to `parent[head]`; then query the final same-chain segment (exclude LCA carefully when edges live on child vertices).
- Edge values: store edge `(p,v)`’s weight at `v`; on path u–v exclude the LCA vertex when summing edge weights.
- Subtree ops for free: with heavy-first ordering, subtree(v) = `[pos[v], pos[v]+sz[v])` — same HLD array handles path *and* subtree.
- Prefer simpler tools when possible: subtree only → Euler; root→node sum → Euler difference; path += offline → tree diff + LCA; static path min/max → binary lifting; HLD when updates + non-trivial path aggregates mix.
- Complexity target: \(O((n+q)\log^2 n)\) with one segtree (or \(O((n+q)\log n)\) with specialized tricks); always `long long` on CF/AtCoder distances.
- Non-commutative monoids (composites): split path at LCA into up-going and down-going folds; maintain reverse merge or two trees.

## Where it appears in OAs / interviews

- Almost never as “implement HLD,” but as **org-chart path metrics**: “sum/max along manager chain with salary updates” → interviewers expect Euler or binary lifting first; HLD is the contest-complete answer when constraints force it.
- **Network / cable queries:** update edge latency, query path delay between two nodes → ABC294 G / Path Queries II shape (edge on child + path sum).
- **Subtree broadcast + path reset:** fill a department, clear ancestors, ask a node’s state → Water Tree–style mixed updates (often solvable with Euler+lazy in interviews).
- Recognition question: “why is path-max-with-updates harder than subtree-sum?” → contiguous tour ranges vs \(O(\log n)\) chain pieces — the conceptual OA/CF gate before writing HLD.
