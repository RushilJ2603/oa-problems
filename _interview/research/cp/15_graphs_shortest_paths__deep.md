# 15 — Graphs II: Shortest Paths (0-1 BFS, Implicit Graphs) (Depth Pass)

**Placement value:** High (second ladder after the standard 0-1 / coupon / multi-source / state-Dijkstra sheet — harder CF-style modeling: sparse/implicit grids, company-switch 0-1, SPT surgery, lex objectives, tiled mazes)
**Prereq topics:** Finished the standard Graphs II shortest-paths ladder (0-1 BFS deque, multi-source, state Dijkstra, two-Dijkstra coupon); deques + priority queues cold
**Pattern in one paragraph:** After Labyrinth / Flight Discount / Bicycles / Nearest Opposite Parity, contest problems stop naming the algorithm and hide a shortest-path graph: edges are “same company / same direction / good road = 0 else 1”, vertices are cells that exist only in a sparse set, or the ask is not one distance but “edit the SPT”, “shortest cycle”, “farthest ignition”, or “lex min (length, repairs)”. Recognize them when moves cost only two values, when you may turn/switch/repair a bounded resource, when the graph is too big to materialize naively, or when several BFS/Dijkstras must be combined on the same skeleton.

**Non-obvious tricks (internalize):**
1. 0-1 BFS invariant: `push_front` on weight 0, `push_back` on weight 1; deque stays sorted by distance — use for company switch, direction change, good/bad roads (not general Dijkstra).
2. Hub / virtual nodes beat cliques: portals, subway companies, letter teleports → attach real nodes to a hub with 0/1 edges instead of connecting all pairs.
3. Reverse multi-source: “nearest special to every node” ⇒ reverse all edges, seed every special at dist 0 (Fire Again / Fair / Nearest Excluded / Police Stations).
4. Two-end distances: keep `ds[·]` and `dt[·]`; try one added edge / meet vertex with `ds[u]+w+dt[v]`; Destroying Roads extends this to two paths with careful overlap accounting.
5. Lexicographic SP: optimize `(path_length, secondary)` in one Dijkstra (pair keys or packed cost) — Breaking Good: fewest bad roads among shortest paths, then edit the rest.
6. SPT surgery: while Dijkstra-relaxing, store parents; among equal-`dist` edges prefer smaller weight (Paths and Trees) or keep only `k` tree edges (Edge Deletion).
7. Implicit infinite grids: visit key `(r mod n, c mod m)` but accept a cell if you reach it from a *different* tile copy than first seen (Infinite Maze).
8. Long-move grids (Pond Skater / Olya-style): one “stroke” of up to `K` in a direction is often 0-1 BFS on `(cell)` with careful first-visit per ray, not `O(K)` naive edges per cell.

## Ladder (easy -> hard, 24 problems)
- [ ] [Fire Again](https://codeforces.com/problemset/problem/35/C) — `Codeforces` `1500` — multi-source BFS on grid — **(core)** seed all initial fires; answer farthest cell (any). Classic “infection radius” OA clone.
- [ ] [Biridian Forest](https://codeforces.com/problemset/problem/329/B) — `Codeforces` `1500` — BFS from exit + race — **(core)** enemies that can reach the exit no later than you count; reverse thinking from the sink.
- [ ] [Mike and Shortcuts](https://codeforces.com/problemset/problem/689/B) — `Codeforces` `1600` — BFS on implicit line — **(core)** edges `i→i±1` cost 1 and one shortcut per index; pure modeling, not “array DP only.”
- [ ] [Fair](https://codeforces.com/problemset/problem/986/A) — `Codeforces` `1600` — multi-source BFS × types — **(core)** for each of `k` goods, BFS from all towns selling it; take `s` nearest per town. Transfer staple.
- [ ] [Fight Against Traffic](https://codeforces.com/problemset/problem/954/D) — `Codeforces` `1600` — two BFS + edge filter — **(core)** `d1`, `dn`; count non-edges whose addition does **not** shorten `1…n`. Sibling of Cow-and-Fields thinking without the main-ladder problem.
- [ ] [Igor and his way to work](https://codeforces.com/problemset/problem/793/B) — `Codeforces` `1600` — state BFS ≤2 turns — **(core)** state `(r,c,dir,turns)`; grid BFS with turn budget — lighter cousin of streak mazes.
- [ ] [Planets](https://codeforces.com/problemset/problem/229/B) — `Codeforces` `1700` — Dijkstra + wait sets — **(core)** if you arrive at a forbidden second, wait to the next free time before leaving; binary-search/set on busy times.
- [ ] [Mad City](https://codeforces.com/problemset/problem/1873/H) — `Codeforces` `1700` — cycle find + BFS race — police vs thief on a unicyclic graph; enter-cycle distance vs chase distance.
- [ ] [Graph Girth](https://cses.fi/problemset/task/1707) — `CSES` `Graph Algorithms` — BFS shortest cycle — **(core)** USACO Guide; BFS from each node, detect back-edge carefully (`dist[u]+dist[v]+1` with parent skip).
- [ ] [Chamber of Secrets](https://codeforces.com/problemset/problem/173/B) — `Codeforces` `1800` — 0-1 BFS on rows/cols — **(core)** mirrors shoot along row/col; moving to a mirror line costs 0/1 — canonical non-grid 0-1 model.
- [ ] [King's Path](https://codeforces.com/problemset/problem/242/C) — `Codeforces` `1800` — BFS on sparse allowed cells — **(core)** hash-set of permitted squares (not full matrix); 8-direction king moves. Implicit-graph staple.
- [ ] [Edge Deletion](https://codeforces.com/problemset/problem/1076/D) — `Codeforces` `1800` — Dijkstra SPT keep ≤k — **(core)** build a shortest-path tree, output any `min(n−1,k)` tree edges. SPT extraction drill.
- [ ] [E - Bishop 2](https://atcoder.jp/contests/abc246/tasks/abc246_e) — `AtCoder` `ABC246 E (~1800)` — 0-1 BFS `(cell, dir)` — **(core)** continuing on the same diagonal ray costs 0; changing direction costs 1. Editorial-standard 01-BFS.
- [ ] [Nearest Excluded Points](https://codeforces.com/problemset/problem/1651/D) — `Codeforces` `1900` — multi-source BFS from blocked — **(stretch)** seed all non-given lattice points’ “boundary”; answer nearest point outside the set for each query point.
- [ ] [Frog Traveler](https://codeforces.com/problemset/problem/1601/B) — `Codeforces` `1900` — BFS with jump-down edges — **(stretch)** from `i` jump up to `a_i` then slip `b`; optimize with “highest unvisited” pointers / segtree BFS.
- [ ] [Rudolf and CodeVid-23](https://codeforces.com/problemset/problem/1846/G) — `Codeforces` `1900` — bitmask state Dijkstra — **(stretch)** illness mask as vertex; medicines are edges that clear/set bits with a time cost.
- [ ] [Paths and Trees](https://codeforces.com/problemset/problem/545/E) — `Codeforces` `2000` — min-weight SPT — **(stretch)** among all shortest-path trees from `u`, minimize Σ edge weights; on `== dist` ties prefer smaller `w`.
- [ ] [Theseus and labyrinth](https://codeforces.com/problemset/problem/676/D) — `Codeforces` `2000` — state BFS + rotations — **(stretch)** state `(r,c,rot)`; rotating the whole maze is an edge of cost 1.
- [ ] [Infinite Maze](https://codeforces.com/problemset/problem/196/B) — `Codeforces` `2000` — BFS on infinite tiling — **(stretch)** periodic copy of the pattern; reachable forever iff some cell is hit from two different tile offsets.
- [ ] [E - Snuke's Subway Trip](https://atcoder.jp/contests/arc061/tasks/arc061_c) — `AtCoder` `ARC061 E (~2000)` — 0-1 BFS company switch — **(stretch)** ride within a company cost 0 after paying 1 to enter; virtual (station,company) nodes. *The* AtCoder 0-1 classic.
- [ ] [F - Pond Skater](https://atcoder.jp/contests/abc170/tasks/abc170_f) — `AtCoder` `ABC170 F (~2100)` — 0-1 BFS long strokes — **(stretch)** one stroke moves 1…K in a cardinal direction; deque 0-1 / careful ray visitation under `H·W≤1e6`.
- [ ] [Breaking Good](https://codeforces.com/problemset/problem/507/E) — `Codeforces` `2100` — lex Dijkstra on roads — **(stretch)** minimize path length, then minimize broken roads used; repair/destroy edges off that path. CM-band 0-1+length.
- [ ] [Police Stations](https://codeforces.com/problemset/problem/796/D) — `Codeforces` `2100` — multi-source BFS spanning — **(stretch)** seed all stations; keep a BFS forest with depth ≤`d`, delete the other edges. Multi-source construction.
- [ ] [Destroying Roads](https://codeforces.com/problemset/problem/543/B) — `Codeforces` `2100` — multi-BFS path combo — **(stretch)** distances from `s1,t1,s2,t2`; maximize leftover edges by routing two paths that may share a middle segment.

## Must-internalize checklist (5-10 bullets)
- Write 0-1 BFS from memory: deque + front/back pushes; prove why distances stay nondecreasing.
- Build virtual hubs for “all pairs in a group share a mode” instead of materializing dense cliques.
- Multi-source initialization: push all sources with `dist=0` before the loop — never run `k` separate full graphs if one joint BFS suffices (unless `k` labels need separate layers like Fair).
- Always store parents / predecessor edges during Dijkstra when the ask is a tree, a path, or “which edges are useful.”
- Lex / multi-criteria: either `pair<dist,secondary>` in the PQ or a 2D `dist[v][state]`.
- Sparse / implicit graphs: hash permitted cells or generate neighbors on the fly; never allocate `N×M` if only `P` cells exist.
- Shortest-cycle BFS: ignore the parent edge; update answer with non-tree back-edges using recorded distances.
- Tiled / infinite mazes: modular index for visit, absolute tile id (or first-offset) for the “second reach” test.

## Where it appears in OAs / interviews
- **Multi-source infection / Wi-Fi:** “fires / routers / warehouses start at once; farthest / nearest client” — Fire Again / Fair pattern in delivery and infra OAs.
- **Mode-switch travel:** “same line free, changing line/company costs 1” — Snuke subway / Chamber mirrors; ride-share interview favorite.
- **Grid with turn or stroke limits:** bishop/rook rays, ≤2 turns, pond-skater strokes — Map navigation rounds after plain BFS mazes.
- **Repair / keep-k roads:** “delete all but k shortest-path edges” or “fix broken roads on a shortest route” — Edge Deletion / Breaking Good style system-design flavored graph questions.
