# 34 — Max flow, min cut, bipartite matching

**Placement value:** Medium — “assign people↔jobs / seats↔students” bipartite matching is the interview slice; raw Dinic / min-cut / MCMF is mostly Candidate-Master rating stretch Striver never covers.
**Prereq topics:** BFS/DFS, residual-graph intuition, bipartite 2-coloring, binary search on answer, basic shortest paths (for BS+matching / MCMF potentials)
**Pattern in one paragraph:** Build a directed network with capacities; **max flow** = maximum “stuff” from `s` to `t` under capacity + conservation (Edmonds–Karp / Dinic). By the **max-flow min-cut** theorem that value equals the cheapest set of edges whose deletion disconnects `s` from `t` (recover cut: nodes reachable from `s` in the residual graph). **Bipartite matching** is the unit-capacity special case: `s → L (cap 1) → R (cap 1) → t`; flow = matching size (Dinic on this = Hopcroft–Karp complexity). Spot it when the statement is assignment, pairwise compatibility, edge/vertex-disjoint paths, “minimum blockers,” or “binary-search a threshold then check a matching/flow.”

## Ladder (easy -> hard, 24 problems)
- [ ] [Maximum Flow](https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_bp) — `AtCoder` `Tessoku A68` — Edmonds–Karp / Dinic template — first “just compute max flow” drill
- [ ] [Bipartite Matching](https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_bq) — `AtCoder` `Tessoku A69` — matching via unit flow — **(core)** seat↔student = `s→L→R→t`
- [ ] [Download Speed](https://cses.fi/problemset/task/1694) — `CSES` `Graph Algorithms` — plain max flow — **(core)** CSES / USACO Guide Max Flow; ship your Dinic here
- [ ] [School Dance](https://cses.fi/problemset/task/1696) — `CSES` `Graph Algorithms` — bipartite matching + pairs — **(core)** CSES / USACO Guide; reconstruct matching edges with flow 1
- [ ] [2D Plane 2N Points](https://atcoder.jp/contests/abc091/tasks/arc092_a) — `AtCoder` `ABC091 C` — greedy bipartite matching — sort red/blue points; matching without needing Dinic
- [ ] [Police Chase](https://cses.fi/problemset/task/1695) — `CSES` `Graph Algorithms` — min cut edges — **(core)** USACO Guide Min-Cut; residual BFS → list cut edges
- [ ] [Maxflow](https://atcoder.jp/contests/practice2/tasks/practice2_d) — `AtCoder` `ACL Practice D` — grid tiling ↔ matching — **(core)** checkerboard bipartition + 1×2 tiles
- [ ] [Coin Grid](https://cses.fi/problemset/task/1709) — `CSES` `Additional Problems` — König min vertex cover — **(core)** USACO Guide; rows↔cols, cut = rows/cols to clear
- [ ] [Distinct Routes](https://cses.fi/problemset/task/1711) — `CSES` `Graph Algorithms` — edge-disjoint paths — **(core)** unit-cap flow + path decomposition
- [ ] [Armchairs](https://codeforces.com/problemset/problem/1525/D) — `Codeforces` `1800` — assignment DP — people↔empty seats as matching-shaped DP (no flow needed)
- [ ] [Chef Monocarp](https://codeforces.com/problemset/problem/1437/C) — `Codeforces` `1800` — assignment to times — **(core)** OA-flavoured “assign items to slots” cost DP
- [ ] [Treasure Island](https://codeforces.com/problemset/problem/1214/D) — `Codeforces` `1900` — min cut on grid — **(core)** block all paths with ≤2 cells; unit min-cut
- [ ] [Valuable Paper](https://codeforces.com/problemset/problem/1423/B) — `Codeforces` `1900` — binary search + matching — **(core)** threshold on edge weight, then perfect matching check
- [ ] [Build String](https://codeforces.com/problemset/problem/237/E) — `Codeforces` `2000` — flow modeling — letters / substrings as capacitated supplies → flow
- [ ] [Task Assignment](https://cses.fi/problemset/task/2129) — `CSES` `Advanced Techniques` — min-cost assignment — **(core)** OA classic; Hungarian or MCMF on complete bipartite
- [ ] [Grid and Tokens](https://atcoder.jp/contests/abc205/tasks/abc205_f) — `AtCoder` `ABC205 F` — node split + flow — **(stretch)** row/col/token capacities; split vertices for “use ≤1”
- [ ] [Array and Operations](https://codeforces.com/problemset/problem/498/C) — `Codeforces` `2100` — prime-factor matching — **(core)** edges = shared primes between `a[i]+a[j]`; matching count
- [ ] [Soldier and Traveling](https://codeforces.com/problemset/problem/546/E) — `Codeforces` `2100` — multi-source flow — **(core)** day-0 / day-1 copies; move along edges under caps
- [ ] [Exploration plan](https://codeforces.com/problemset/problem/852/D) — `Codeforces` `2100` — BS + shortest + matching — **(stretch)** mid = max travel time; bipartite teams↔silks
- [ ] [Parcel Delivery](https://cses.fi/problemset/task/2121) — `CSES` `Advanced Techniques` — min-cost max-flow — **(stretch)** send exactly `k` units of flow at min cost
- [ ] [Delivery Bears](https://codeforces.com/problemset/problem/653/D) — `Codeforces` `2200` — BS + max flow — **(stretch)** mid = per-bear load; floor capacities, need flow ≥ `x`
- [ ] [Little C Loves 3 II](https://codeforces.com/problemset/problem/1034/B) — `Codeforces` `2200` — grid matching — **(stretch)** maximum matching on grid graph (formula / flow)
- [ ] [Distinct Routes II](https://cses.fi/problemset/task/2130) — `CSES` `Advanced Techniques` — MCMF path pack — **(stretch)** exactly `k` edge-disjoint routes, minimize total length
- [ ] [MinCostFlow](https://atcoder.jp/contests/practice2/tasks/practice2_e) — `AtCoder` `ACL Practice E` — MCMF on grid — **(stretch)** row/col pick limits + costs; ACL `mcf_graph` drill

## Must-internalize checklist (5-10 bullets)
- Dinic (or Edmonds–Karp) template from memory: level graph + blocking flow; use `long long` for capacities/flow.
- Residual edges: every forward edge has a reverse with capacity 0; augmenting path updates both.
- Bipartite matching model: `s→L→R→t` all caps 1; matching edges = `L→R` with flow 1; Dinic is `O(E√V)` here.
- Max-flow = min-cut: after max flow, BFS/DFS from `s` in residual; cut = edges `u→v` with `u` reachable, `v` not.
- König (bipartite): max matching = min vertex cover; recover cover from the min-cut of the matching network (CSES Coin Grid).
- Edge-disjoint paths = unit-capacity max flow; decompose by walking saturated edges and subtracting.
- Node capacity `c(v)`: split `v_in → v_out` with cap `c(v)`; all in-edges to `v_in`, out-edges from `v_out`.
- Binary search + matching/flow: monotone “can we achieve threshold `x`?” → rebuild caps / keep edges ≥ `x` → check flow/matching.
- Assignment with costs → min-cost max-flow (or Hungarian for dense `n≤200`); CSES Task Assignment is the template.
- Don’t force flow: many “matching-shaped” OA tasks are assignment DP (`Armchairs` / `Chef Monocarp`) when `n` is small.

## Where it appears in OAs / interviews
- “Maximum number of boy–girl / worker–job pairs under compatibility” → bipartite matching (School Dance / Tessoku A69).
- “Assign each employee exactly one task minimizing total cost” → assignment / Hungarian / MCMF (CSES Task Assignment).
- “Seat students so no two can cheat / cover coins by deleting rows or columns” → independent set / vertex cover via bipartite matching + König (Coin Grid; LC-style classroom seating).
- “Minimum walls/cells to block all paths from A to B” → min cut (Police Chase / Treasure Island), often disguised as “cut the network / remove fewest roads.”
