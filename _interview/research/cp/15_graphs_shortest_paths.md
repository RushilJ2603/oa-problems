# 15 — Graphs II: Shortest Paths (0-1 BFS, State/Implicit Dijkstra, Multi-source, k-shortest)

**Placement value:** High — grid/maze races, “one coupon / one free edge”, multi-source infection, and state-augmented shortest paths dominate mid OA + Div2 C/D; stretch covers k-shortest and potentials mindset toward CM.
**Prereq topics:** Graphs I (BFS/DFS, multi-source BFS idea), priority queues, Dijkstra / Bellman-Ford / Floyd at Striver level (algorithms known — retrain in contest form), deques.

**Pattern in one paragraph:** Contest shortest-path problems rarely say “run Dijkstra.” Edges are often 0/1 (deque 0-1 BFS), the graph is implicit (grid, residues, portals), or the vertex is a *state* `(node, resource)` (coupon used, best bike, direction streak). Multi-source = seed every source at dist 0 (or reverse the graph and start from all sinks). k-shortest keeps the first `k` pops per node. Potentials / Johnson = Bellman-Ford distances as node potentials so reweighted edges are nonnegative, then Dijkstra APSP — recognize when you need many SSSP queries on a graph that may have negatives but no neg-cycle.

## Ladder (easy -> hard, 25 problems)
- [ ] [Getting Zero](https://codeforces.com/problemset/problem/1661/B) — `Codeforces` `1300` — BFS on implicit states — Ops `+1` / `×2` mod 32768; state graph BFS, not “array DP only.”
- [ ] [Air Conditioners](https://codeforces.com/problemset/problem/1547/E) — `Codeforces` `1500` — multi-source shortest — Seed all ACs; left/right sweeps ≡ multi-source dist. OA-transfer classic. **(core)**
- [ ] [The Two Routes](https://codeforces.com/problemset/problem/601/A) — `Codeforces` `1600` — BFS on G vs complement — Train vs bus; one mode uses the missing edges. Clean modeling.
- [ ] [By Elevator or Stairs?](https://codeforces.com/problemset/problem/1249/E) — `Codeforces` `1700` — layered / state SP — Floor + “last was elevator?”; Dijkstra or DP-on-DAG of states.
- [ ] [Drunken Maze](https://codeforces.com/problemset/problem/2041/D) — `Codeforces` `1700` — state grid BFS — State `(r,c,dir,streak)`; grid BFS with move constraints.
- [ ] [Escape The Maze (easy version)](https://codeforces.com/problemset/problem/1611/E1) — `Codeforces` `1700` — multi-source BFS on tree — Friends vs you racing to root; seed all friends first.
- [ ] [Navigation System](https://codeforces.com/problemset/problem/1320/B) — `Codeforces` `1700` — reverse BFS + SPT — Dist from `t`; count forced rebuilds vs optional on a shortest-path DAG.
- [ ] [Flight Discount](https://cses.fi/problemset/task/1195) — `CSES` `Graph Algorithms` — state Dijkstra / two Dijkstras — USACO Guide staple; coupon = layer or `fwd[u]+⌊w/2⌋+bwd[v]`. **(core)**
- [ ] [Investigation](https://cses.fi/problemset/task/1202) — `CSES` `Graph Algorithms` — Dijkstra + path DP — Min cost, count, min/max edges on shortest paths; CSES / USACO Guide. **(core)**
- [ ] [Labyrinth](https://codeforces.com/problemset/problem/1063/B) — `Codeforces` `1800` — 0-1 BFS on grid — Left cost 1 / other moves 0; canonical 0-1 BFS maze. **(core)**
- [ ] [Christmas Trees](https://codeforces.com/problemset/problem/1283/D) — `Codeforces` `1800` — multi-source BFS on line — Expand from all trees; place `m` people maximizing min dist. **(core)**
- [ ] [Bicycles](https://codeforces.com/problemset/problem/1915/G) — `Codeforces` `1800` — state Dijkstra — State `(city, best_bike)`; CF Div4 G that is pure state SP. **(core)**
- [ ] [Third Avenue](https://atcoder.jp/contests/abc184/tasks/abc184_e) — `AtCoder` `ABC184 E` — 0-1 BFS + portal hubs — Virtual letter nodes; 0/1 edges beat naïve teleport clique. **(core)**
- [ ] [Rendez-vous de Marian et Robin](https://codeforces.com/problemset/problem/2014/E) — `Codeforces` `1800` — multi Dijkstra + horse bit — Meet anywhere; state “has horse?” from both ends.
- [ ] [D/D/D](https://codeforces.com/problemset/problem/2109/D) — `Codeforces` `1900` — 0-1 BFS / parity trick — USACO Guide unweighted-SP list; edge weights 0/1 after modeling. **(core)**
- [ ] [Nearest Opposite Parity](https://codeforces.com/problemset/problem/1272/E) — `Codeforces` `1900` — reverse multi-source BFS — Edges `i → i±a[i]` reversed; BFS from all odd/even sinks. **(core)**
- [ ] [Cow and Fields](https://codeforces.com/problemset/problem/1307/D) — `Codeforces` `1900` — two BFS + best pair — Add one edge among specials; maximize `dist(1,n)` via `d1[u]+1+dn[v]`.
- [ ] [Flight Routes](https://cses.fi/problemset/task/1196) — `CSES` `Graph Algorithms` — k-shortest paths — USACO Guide; allow `k` pops per node, print `k` costs to `n`. **(core)**
- [ ] [Buy a Ticket](https://codeforces.com/problemset/problem/938/D) — `Codeforces` `2000` — reverse multi-source Dijkstra — Concert cost as edge to super-sink; reverse = multi-source from all cities. **(stretch)**
- [ ] [Jzzhu and Cities](https://codeforces.com/problemset/problem/449/B) — `Codeforces` `2000` — Dijkstra + redundant trains — Drop train edges useless vs road SPT. **(stretch)**
- [ ] [Shortest Path](https://codeforces.com/problemset/problem/59/E) — `Codeforces` `2000` — state BFS — Forbid consecutive pairs; state `(v, prev)` unweighted SP. **(stretch)**
- [ ] [Small Multiple](https://atcoder.jp/contests/abc077/tasks/arc084_b) — `AtCoder` `ABC077 D` — 0-1 BFS on residues — USACO Guide hard; `+1` cost 1, `×10` cost 0 mod `K`. **(stretch)**
- [ ] [High Score](https://cses.fi/problemset/task/1673) — `CSES` `Graph Algorithms` — Bellman-Ford / pos-cycle — CSES; longest path + cycle reachable to `n`. Potentials / Johnson foundation. **(stretch)**
- [ ] [Weights Distributing](https://codeforces.com/problemset/problem/1343/E) — `Codeforces` `2100` — 3×BFS + greedy assign — Paths `a-b-c`; sort weights onto a shortest-path skeleton. **(stretch)**
- [ ] [Reducing Delivery Cost](https://codeforces.com/problemset/problem/1433/G) — `Codeforces` `2100` — many Dijkstras / APSP usage — Precompute all SSSP; try zeroing one edge. Johnson-motivation stretch (sparse APSP via repeated Dijkstra). **(stretch)**

## Must-internalize checklist (5-10 bullets)
- 0-1 BFS: `deque`, `push_front` on weight 0, `push_back` on weight 1; `O(V+E)`.
- State Dijkstra: `dist[node][extra…]` (or hashed state); relax transitions, not only original edges.
- Multi-source: initialize queue/PQ with all sources at 0; reverse edges when “nearest source to each node.”
- Two-Dijkstra coupon trick: `fwd` from `s`, `bwd` from `t` on reversed graph; try the special op on every edge.
- k-shortest: keep ≤`k` distances per node; the `i`-th pop is the `i`-th best under nonnegative weights.
- Dijkstra hygiene: `if (d > dist[u]) continue;` before relaxing (USACO Guide TLE trap).
- Path aggregates on shortest DAG: while running Dijkstra, update count / min-edges / max-edges on `==` and `<` relaxations.
- Potentials / Johnson sketch: Bellman-Ford from a super-source → potentials `p[v]`; reweight `w'(u,v)=w(u,v)+p[u]-p[v] ≥ 0`; then `n` Dijkstras for APSP; restore `dist = dist' - p[u] + p[v]`.
- Grid tricks: portal hubs, direction/streak in the state, left/right budgets as 0-1 costs, race against multi-source monsters (Graphs I).

## Where it appears in OAs / interviews
- **One free upgrade / coupon:** Cheapest route if you may halve (or zero) exactly one edge — Flight Discount clones in delivery/ride-share OAs.
- **Infection / facility placement:** Multi-source BFS/Dijkstra from all hospitals, Wi-Fi routers, or ACs; answer min time or best spot (Air Conditioners / Christmas Trees pattern).
- **State-augmented travel:** “You may pick up one bike / key / discount along the way” → `dist[u][have]` Dijkstra (Bicycles / elevator-vs-stairs interviews).
- **Maze with asymmetric moves:** Limited left/right presses or teleporters — 0-1 BFS / hub nodes rather than plain BFS (Labyrinth / Third Avenue style).
