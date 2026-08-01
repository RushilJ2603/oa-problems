# 14 — Graphs I: BFS/DFS, Connected Components, Flood Fill, Topological Sort

**Placement value:** High (grid/graph reachability, islands, bipartite checks, and course-order / dependency topo are OA staples)
**Prereq topics:** Arrays & grids, Recursion, Queues/Stacks, Basic trees

**Pattern in one paragraph:** Model the input as an explicit graph (adjacency list) or an implicit one (grid 4-neighbors). DFS explores deeply to mark a component, detect cycles, or color bipartitely; BFS explores by distance and is the default for unweighted shortest paths and multi-source spread. Connected components / flood fill answer “how many regions / can A reach B / min edges to connect.” Topological sort (Kahn indegree queue or DFS finish-order) linearizes a DAG and fails exactly when a directed cycle exists — signaled by prerequisites, ordering constraints, or “longest/number of paths in a DAG.”

## Ladder (easy -> hard, 26 problems)
- [ ] [Number of Islands](https://leetcode.com/problems/number-of-islands/) — `LeetCode` `Medium` — flood fill / CC — NeetCode / Striver OA classic; grid DFS/BFS template. (core)
- [ ] [Party](https://codeforces.com/problemset/problem/115/A) — `Codeforces` `900` — DFS / tree depth — Earliest CF DFS: longest chain in a forest of managers.
- [ ] [Counting Rooms](https://cses.fi/problemset/task/1192) — `CSES` `Graph Algorithms` — flood fill — CSES / USACO Guide focus; count `.` components in a grid. (core)
- [ ] [Building Roads](https://cses.fi/problemset/task/1666) — `CSES` `Graph Algorithms` — connected components — CSES / USACO Guide focus; need `C-1` edges to connect `C` components. (core)
- [ ] [Ice Skating](https://codeforces.com/problemset/problem/217/A) — `Codeforces` `1200` — connected components — A2OJ classic; points share a row/col ⇒ edge, answer `C-1`.
- [ ] [BFS](https://atcoder.jp/contests/abc007/tasks/abc007_3) — `AtCoder` `ABC007 C` — grid BFS — Canonical AtCoder BFS maze tutorial (queue + dist).
- [ ] [Rumor](https://codeforces.com/problemset/problem/893/C) — `Codeforces` `1300` — CC + greedy — Pay min gold per component; clean CC application.
- [ ] [Mahmoud and Ehab and the bipartiteness](https://codeforces.com/problemset/problem/862/B) — `Codeforces` `1300` — bipartite coloring — Tree is bipartite; maximize cross edges between color classes.
- [ ] [Course Schedule](https://leetcode.com/problems/course-schedule/) — `LeetCode` `Medium` — topo / cycle detect — NeetCode / Striver; directed-cycle ⇔ impossible. (core)
- [ ] [Rotting Oranges](https://leetcode.com/problems/rotting-oranges/) — `LeetCode` `Medium` — multi-source BFS — NeetCode OA staple; simultaneous infection from all rotten cells. (core)
- [ ] [Message Route](https://cses.fi/problemset/task/1667) — `CSES` `Graph Algorithms` — BFS + path reconstruct — Unweighted shortest path with parent pointers. (core)
- [ ] [Labyrinth](https://cses.fi/problemset/task/1193) — `CSES` `Graph Algorithms` — grid BFS + path string — Same idea on a grid; reconstruct `U/D/L/R`. (core)
- [ ] [Building Teams](https://cses.fi/problemset/task/1668) — `CSES` `Graph Algorithms` — bipartite check — CSES / USACO Guide focus; 2-color every component. (core)
- [ ] [Kefa and Park](https://codeforces.com/problemset/problem/580/C) — `Codeforces` `1500` — DFS on trees — Count leaves reachable without `m+1` consecutive cats.
- [ ] [Cyclic Components](https://codeforces.com/problemset/problem/977/E) — `Codeforces` `1500` — CC + cycle shape — Count components that are simple cycles (all deg 2).
- [ ] [Round Trip](https://cses.fi/problemset/task/1669) — `CSES` `Graph Algorithms` — undirected cycle — DFS with parent; reconstruct a cycle of length ≥ 3.
- [ ] [Maze](https://codeforces.com/problemset/problem/377/A) — `Codeforces` `1600` — flood fill / DFS — Visit `s` empties then wall off the rest; A2OJ-era DFS classic.
- [ ] [Fox And Names](https://codeforces.com/problemset/problem/510/C) — `Codeforces` `1600` — topological sort — USACO Guide; alphabet graph from consecutive strings. (core)
- [ ] [Course Schedule](https://cses.fi/problemset/task/1679) — `CSES` `Graph Algorithms` — topological sort — CSES / USACO Guide Kahn or DFS-topo template at `n ≤ 1e5`. (core)
- [ ] [Monsters](https://cses.fi/problemset/task/1194) — `CSES` `Graph Algorithms` — multi-source BFS — Escape to border beating monster arrival times; OA-transfer pattern. (core)
- [ ] [Longest Path](https://atcoder.jp/contests/dp/tasks/dp_g) — `AtCoder` `DP contest G` — DAG DP / topo — AtCoder DP contest milestone; longest path in a DAG. (stretch)
- [ ] [Igor In the Museum](https://codeforces.com/problemset/problem/598/D) — `Codeforces` `1700` — flood fill + memo — Precompute pictures per component; answer queries in O(1). (stretch)
- [ ] [Valid BFS?](https://codeforces.com/problemset/problem/1037/D) — `Codeforces` `1700` — BFS order check — Decide if a given sequence can be a BFS traversal. (stretch)
- [ ] [Substring](https://codeforces.com/problemset/problem/919/D) — `Codeforces` `1700` — topo + DP — USACO Guide; max letter-frequency along a path, or -1 on cycle. (stretch)
- [ ] [Directing Edges](https://codeforces.com/problemset/problem/1385/E) — `Codeforces` `2000` — topo constructive — USACO Guide; orient undirected edges using a topo order. (stretch)
- [ ] [Connected Components?](https://codeforces.com/problemset/problem/920/E) — `Codeforces` `2100` — CC in complement — USACO Guide hard; components of the complement graph efficiently. (stretch)

## Must-internalize checklist (5-10 bullets)
- Adjacency-list DFS/BFS with `visited[]`; iterative BFS via `queue` / `deque`.
- Grid flood fill: 4-dir deltas, bounds checks, mark visited before enqueue/recurse (avoid TLE/stack blowups).
- Connected-component loop: for each unvisited node, run DFS/BFS and count / collect representatives.
- Unweighted shortest path: BFS distances + `parent[]` (or move char) to reconstruct the path.
- Multi-source BFS: seed the queue with all sources at dist 0 (rotten oranges / monsters).
- Bipartite check: 2-color with BFS/DFS; conflict ⇒ impossible.
- Undirected cycle: DFS with parent; directed cycle: color states (WHITE/GRAY/BLACK) or failed Kahn.
- Topological sort: Kahn (`indegree` + queue) and DFS finish-order; output size `< n` ⇒ cycle.
- DAG DP after topo: longest path / path counts processed in topo order.

## Where it appears in OAs / interviews
- **Grid islands / regions:** “Count connected groups of 1s” or “flood-fill recolor from a click” (Number of Islands / Flood Fill clones).
- **Infection / minutes-to-spread:** Multi-source BFS on a grid until all fresh cells are reached (Rotting Oranges pattern at Amazon/Meta-style OAs).
- **Prerequisite / build order:** Courses or tasks with “A before B”; detect cycles and return a valid order (Course Schedule I/II).
- **Reachability / walls:** Maze escape, blocked cells, or “can you reach the border before X spreads” — plain or racing BFS.
