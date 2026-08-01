# 16 — DSU / Union-Find & MST (Kruskal, Prim)

**Placement value:** High — connectivity, cycle detection, “min cost to connect”, and offline merge queries dominate OAs; Kruskal+DSU is the standard MST interview package.
**Prereq topics:** Graphs (adj / edge list), sorting, DFS/BFS components, basic greedy.

**Pattern in one paragraph:** Maintain disjoint sets under merges so you can answer “same component?” and merge in nearly \(O(1)\) amortized (path compression + union by size/rank). Use it whenever edges arrive over time, you need component sizes/counts, or you must detect a cycle while adding edges. Kruskal = sort edges by weight, add if endpoints differ (DSU); Prim = grow one tree with a priority queue (prefer dense / implicit complete graphs). Offline tricks: process edges light→heavy or reverse deletions as unions. Signal words: provinces/friends/network, redundant cable, connect all cities, max edge on path ≤ X, repair roads with min cost.

## Ladder (easy -> hard, 26 problems)

- [ ] [Count Connected Components](https://atcoder.jp/contests/abc284/tasks/abc284_c) — `AtCoder` `ABC C` — DSU component count — Warm-up: write `find`/`union`, count roots. ABC template.
- [ ] [Ice Skating](https://codeforces.com/problemset/problem/217/A) — `Codeforces` `1200` — DSU on shared row/col — Classic “union if same x or y”; A2OJ-era connectivity. **(core)**
- [ ] [Number of Provinces](https://leetcode.com/problems/number-of-provinces/) — `LeetCode` `Medium` — DSU / components — NeetCode / Striver staple; adjacency-matrix provinces. **(core)**
- [ ] [Redundant Connection](https://leetcode.com/problems/redundant-connection/) — `LeetCode` `Medium` — DSU cycle edge — NeetCode; first failed `union` is the answer. **(core)**
- [ ] [Rumor](https://codeforces.com/problemset/problem/893/C) — `Codeforces` `1300` — min cost per component — Pay once per component (min bribe); DSU or DFS. **(core)**
- [ ] [Road Construction](https://cses.fi/problemset/task/1676) — `CSES` `Graph Algorithms` — incremental DSU sizes — CSES / USACO Guide focus; components + max size after each edge. **(core)**
- [ ] [News Distribution](https://codeforces.com/problemset/problem/1167/C) — `Codeforces` `1400` — component size queries — CF classic; groups as cliques → answer `sz[find(i)]`. **(core)**
- [ ] [Learning Languages](https://codeforces.com/problemset/problem/277/A) — `Codeforces` `1400` — DSU via shared language — A2OJ; employees linked through languages (+ empty case).
- [ ] [Number of Operations to Make Network Connected](https://leetcode.com/problems/number-of-operations-to-make-network-connected/) — `LeetCode` `Medium` — spare edges → connect comps — OA classic: need `components-1` moves iff enough redundants. **(core)**
- [ ] [Satisfiability of Equality Equations](https://leetcode.com/problems/satisfiability-of-equality-equations/) — `LeetCode` `Medium` — DSU on `==` then check `!=` — NeetCode / Striver; equalities first. **(core)**
- [ ] [Friend Suggestions](https://atcoder.jp/contests/abc157/tasks/abc157_d) — `AtCoder` `ABC D` — DSU + block list — Component size minus self/friends/blocks; AtCoder UF classic.
- [ ] [Mocha and Diana (Easy Version)](https://codeforces.com/problemset/problem/1559/D1) — `Codeforces` `1400` — dual DSU forests — Add edge iff both forests stay acyclic; constructive DSU. **(core)**
- [ ] [Secret Passwords](https://codeforces.com/problemset/problem/1263/D) — `Codeforces` `1500` — DSU on shared letters — Strings connected by common chars → component count.
- [ ] [Decayed Bridges](https://atcoder.jp/contests/abc120/tasks/abc120_d) — `AtCoder` `ABC D` — reverse-time DSU — Famous reverse-union: inconvenient pairs = \(n(n-1)/2\) minus size products. **(core)**
- [ ] [Destroying Array](https://codeforces.com/problemset/problem/722/C) — `Codeforces` `1600` — reverse DSU + max segment sum — CF EDU-adjacent classic; delete→add reverse, track max component sum. **(core)**
- [ ] [Road Reparation](https://cses.fi/problemset/task/1675) — `CSES` `Graph Algorithms` — Kruskal MST — CSES / USACO Guide MST focus; sort + DSU, else `IMPOSSIBLE`. **(core)**
- [ ] [Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/) — `LeetCode` `Medium` — Kruskal / Prim MST — NeetCode; Manhattan complete graph (Prim often cleaner). **(core)**
- [ ] [MST (Minimum Spanning Tree)](https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_bo) — `AtCoder` `Tessoku A67` — textbook Kruskal — Kyopro textbook drill; pure MST weight.
- [ ] [Destruction](https://atcoder.jp/contests/abc218/tasks/abc218_e) — `AtCoder` `ABC E` — max removable = non-MST positive — Keep a spanning tree (Kruskal), sum rewards on discarded nonnegative edges.
- [ ] [Social Network](https://codeforces.com/problemset/problem/1609/D) — `Codeforces` `1600` — DSU + unused merges — Extra same-component edges banked to enlarge top components later.
- [ ] [Accounts Merge](https://leetcode.com/problems/accounts-merge/) — `LeetCode` `Medium` — DSU on emails — NeetCode / Striver OA favorite; map email→id, union, group. **(core)**
- [ ] [Path Queries](https://codeforces.com/problemset/problem/1213/G) — `Codeforces` `1800` — offline DSU by edge weight — Sort edges+queries; pairs in component = \(\binom{sz}{2}\). **(stretch)**
- [ ] [Shichikuji and Power Grid](https://codeforces.com/problemset/problem/1245/D) — `Codeforces` `1900` — MST + virtual node — Station cost = edge to node 0; reconstruct edges. **(stretch)**
- [ ] [Roads not only in Berland](https://codeforces.com/problemset/problem/25/D) — `Codeforces` `1900` — replace cycles with bridges — DSU finds redundant edges; rewire components into a tree. **(stretch)**
- [ ] [MinOr Tree](https://codeforces.com/problemset/problem/1624/G) — `Codeforces` `1900` — bit-greedy spanning tree — Drop high OR-bits if graph stays connected (DSU checks). **(stretch)**
- [ ] [Minimum spanning tree for each edge](https://codeforces.com/problemset/problem/609/E) — `Codeforces` `2100` — MST + max-on-path — Build MST, then for each edge answer via tree max (LCA/binlift). **(stretch)**

## Must-internalize checklist

- DSU template from memory: `parent`, `size`/`rank`, recursive `find` with path compression, `union` by size/rank returning bool.
- Component bookkeeping: count of components, size of each root, optional sum/xor/min on the root.
- Kruskal: sort edges ascending, add iff `union` succeeds; stop at \(n-1\) edges; detect disconnected.
- Prim: binary-heap grow from a source; prefer when \(E \approx V^2\) or distances are implicit (points).
- Cycle / redundant edge: failed `union` means the edge closes a cycle.
- Reverse technique: deletions or “bridges collapse” → process reverse as unions (Decayed Bridges / Destroying Array).
- Offline by weight: sort edges and queries together (Path Queries); maintain \(\binom{sz}{2}\) as you merge.
- MST variants: virtual node for “build facility or connect” (Shichikuji); bit-greedy connectivity (MinOr).

## Where it appears in OAs / interviews

- **Provinces / friend circles / accounts:** merge entities sharing a key (city link, email, language) and count groups or report sizes (LC 547 / 721, CF News Distribution).
- **Cables & redundancy:** “min operations to connect all computers” / “which edge creates a cycle” (LC 1319 / 684) — Amazon/Meta-style graph OAs.
- **Min cost to wire sites:** Manhattan points or city roads → MST (LC 1584, CSES Road Reparation); sometimes “power station OR wire” → virtual node.
- **Equality constraints:** process `a==b` unions then validate `a!=b` (LC 990); same pattern as “same gang / opposite gang” 2-SAT-lite with DSU.
