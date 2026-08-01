# 14 — Graphs I: BFS/DFS, Components, Topo (Depth Pass)

**Placement value:** High (Second ladder: CF-style reachability tricks, bipartite orientation, functional graphs, complement BFS, and DAG/Kahn variants — the post-Striver skill of *finding the graph*, not recalling the template).
**Prereq topics:** Base Graphs I ladder (grid flood fill, CC, bipartite check, Kahn/DFS-topo, multi-source BFS), queues/deques, basic trees; light DAG DP for the stretch tail.
**Pattern in one paragraph:** Same DFS/BFS/CC/topo engines as the base sheet, but statements hide them behind **rewrites**: wall off bad neighbors then ask reachability; 2-color then orient; treat “almost complete” graphs via the complement; expand state (turns / layer mod 3 / parity); or reverse the edges and multi-source from *targets*. Recognize them when you must force a property before searching, when \(n\) is large but “missing edges” are few, when each node has out-degree 1, when ordering constraints split into two processor types, or when “nearest opposite / nearest special” is asked from every node.

**Technique notes (non-obvious):**
- Block-then-BFS: to forbid paths through “bad” cells, first wall every neighbor of a bad cell, *then* one reachability BFS from the start (Solve The Maze) — don’t try to dodge during search.
- Complement / near-complete graphs: never materialize \(n^2\) edges; keep an unused-node set and skip only the explicit forbidden neighbors (The Two Routes / 0-1 MST).
- Bipartite orientation: undirected → direct every edge from color \(0\to 1\); “no long directed path” / cover constraints often reduce to 2-colorability (Graph Without Long Directed Paths / Cover it!).
- Functional graphs (outdeg \(=1\)): each component is a cycle with trees feeding in; the answer is usually the min on the cycle, after compressing tree→cycle edges (Mouse Hunt).
- Reverse multi-source BFS: “for every \(v\), nearest \(u\) with property \(P\)” → BFS from all \(P\)-nodes on the *reversed* graph (Nearest Opposite Parity).
- Dual Kahn: maintain two ready-queues (needs scarce resource vs free); repeatedly drain the free side, then spend one scarce step (Coprocessor) — same indegree idea, different scheduler.
- State BFS / layered graph: node \(=(v,\text{state})\) for turns used, hop parity, or layer \(\bmod 3\) instead of rebuilding a huge explicit graph (Igor / Hopscotch Addict).
- Edge coloring of digraphs: if acyclic → 1 color; else 2 — color an edge by whether it is a DFS back-edge into the recursion stack (Coloring Edges).

## Ladder (easy -> hard, 25 problems)
- [ ] [Learning Languages](https://codeforces.com/problemset/problem/277/A) — `Codeforces` `1400` — CC via shared attrs — **(core)** employees share an edge if they share a language; min teaches \(=\) components (with the empty-language corner).
- [ ] [Connect](https://codeforces.com/problemset/problem/1130/C) — `Codeforces` `1400` — flood fill + bridge — **(core)** two land components; answer min squared distance between a cell of start-CC and finish-CC (or 0 if same).
- [ ] [Not Assigning](https://codeforces.com/problemset/problem/1627/C) — `Codeforces` `1400` — tree edge 2-color — **(core)** assign edge weights \(\{2,3\}\) so every path of length \(\ge 2\) is composite; bipartite edges of a tree.
- [ ] [Set Construction](https://codeforces.com/problemset/problem/1761/C) — `Codeforces` `1400` — reachability constructive — **(core)** build sets from a tournament-ish reachability matrix; each \(i\) gets \(\{i\}\) plus nodes that reach it — DAG/closure thinking.
- [ ] [D - Grid and Magnet](https://atcoder.jp/contests/abc351/tasks/abc351_d) — `AtCoder` `ABC351 D` — safe-cell flood fill — **(core)** magnets poison neighbors; count reachable *safe* cells with a careful “touch-unsafe-but-don’t-cross” rule.
- [ ] [Fox And Two Dots](https://codeforces.com/problemset/problem/510/B) — `Codeforces` `1500` — grid cycle ≥4 — **(core)** same-color DFS with parent; classic CF grid-cycle detection (not the CSES undirected-cycle template alone).
- [ ] [Bear and Friendship Condition](https://codeforces.com/problemset/problem/771/A) — `Codeforces` `1500` — CC must be clique — **(core)** friendship is transitive iff every component with \(s\) vertices has \(\binom{s}{2}\) edges.
- [ ] [Biridian Forest](https://codeforces.com/problemset/problem/329/B) — `Codeforces` `1500` — BFS race count — **(core)** BFS from the exit; count breeders strictly closer than you — multi-agent timing without multi-source setup.
- [ ] [The Labyrinth](https://codeforces.com/problemset/problem/616/C) — `Codeforces` `1600` — CC sizes + id — **(core)** precompute `.` component sizes; for each `*` sum distinct neighboring component sizes (+1). Sibling of Igor-in-Museum, different ask.
- [ ] [New Reform](https://codeforces.com/problemset/problem/659/E) — `Codeforces` `1600` — CC tree vs cyclic — **(core)** each tree-component needs one “unoriented” fix; components with a cycle are already fine — count by \(e=v-1\) vs not.
- [ ] [The Two Routes](https://codeforces.com/problemset/problem/601/A) — `Codeforces` `1600` — BFS on \(G\) and \(\overline{G}\) — Train vs bus: one uses given edges, one uses the complement; answer max of the two \(1\to n\) distances (or \(-1\)).
- [ ] [Igor and his way to work](https://codeforces.com/problemset/problem/793/B) — `Codeforces` `1600` — state BFS (≤2 turns) — Grid path allowing at most two direction changes; state `(cell, dir, turns)`.
- [ ] [Solve The Maze](https://codeforces.com/problemset/problem/1365/D) — `Codeforces` `1700` — block-then-reach — **(core)** wall neighbors of every bad guy, then check all goods still reach the corner; constructive + BFS hybrid.
- [ ] [Graph Without Long Directed Paths](https://codeforces.com/problemset/problem/1144/F) — `Codeforces` `1700` — bipartite orientation — **(core)** 2-color, orient every edge low→high color; impossible iff odd cycle.
- [ ] [Mouse Hunt](https://codeforces.com/problemset/problem/1027/D) — `Codeforces` `1700` — functional-graph cycles — Follow outdeg-1 edges; place the cheapest trap on each cycle (trees feeding in need nothing extra).
- [ ] [Game Routes](https://cses.fi/problemset/task/1681) — `CSES` `Graph Algorithms` — topo DP path counts — **(core)** number of routes \(1\to n\) mod \(10^9+7\) on a DAG; the canonical Kahn/DP follow-up to Course Schedule.
- [ ] [E - Hopscotch Addict](https://atcoder.jp/contests/abc132/tasks/abc132_e) — `AtCoder` `ABC132 E` — layered BFS — **(stretch)** shortest path whose length \(\equiv 0\pmod{3}\); BFS on states `(v, dist mod 3)`.
- [ ] [Christmas Trees](https://codeforces.com/problemset/problem/1283/D) — `Codeforces` `1800` — multi-source expand — **(stretch)** plant \(m\) people maximizing Σ dist to nearest tree; BFS ring-expansion from all trees with occupancy control.
- [ ] [Nearest Opposite Parity](https://codeforces.com/problemset/problem/1272/E) — `Codeforces` `1900` — reverse multi-source BFS — **(stretch)** from each index, min jumps to opposite parity; build reverse graph of jump targets, BFS from all odd and all even sinks.
- [ ] [Gargari and Permutations](https://codeforces.com/problemset/problem/463/D) — `Codeforces` `1900` — DAG longest path — **(stretch)** \(k\) permutations → pairwise order constraints → longest path in the induced DAG (common LCS-of-perms framing).
- [ ] [Coprocessor](https://codeforces.com/problemset/problem/909/E) — `Codeforces` `1900` — dual-queue Kahn — **(stretch)** tasks need main CPU or coprocessor; min main-CPU “sessions” via two ready-sets and indegrees.
- [ ] [0-1 MST](https://codeforces.com/problemset/problem/1242/B) — `Codeforces` `1900` — complement CC — **(stretch)** MST of \(K_n\) with a few weight-1 edges: count components under weight-0 (complement of given edges) — sibling technique to Connected Components? without repeating that problem.
- [ ] [Ice Cave](https://codeforces.com/problemset/problem/540/C) — `Codeforces` `2000` — revisit-cell BFS — **(stretch)** destination may be re-entered iff it has ≥2 open neighbors; non-standard `visited` rule on grids.
- [ ] [Course Schedule II](https://cses.fi/problemset/task/1757) — `CSES` `Graph Algorithms` — lex-min reverse Kahn — **(stretch)** among valid orders, minimize the sequence lexicographically via heap on the *reversed* constraint graph (USACO Guide hard topo).
- [ ] [Coloring Edges](https://codeforces.com/problemset/problem/1217/D) — `Codeforces` `2100` — DFS back-edge colors — **(stretch)** color digraph edges so no mono cycle; 1 color if DAG else 2, marking back-edges to the recursion stack.

## Must-internalize checklist (5-10 bullets)
- Rewrite before DFS/BFS: block neighbors, 2-color then orient, reverse edges, or switch to the complement.
- Component aggregates: store `comp_id[]` + `comp_size[]` / edge count; answer per-cell or per-query in \(O(1)\) / \(O(\deg)\).
- Clique-CC check: component with \(s\) nodes is a clique iff it has exactly \(\binom{s}{2}\) edges.
- Functional-graph pipeline: iterate unvisited → follow unique outs → detect cycle → process cycle then inbound trees.
- State BFS skeleton: queue of `(node, state)` + `dist[node][state]`; keep state domain tiny (≤3–5).
- Dual ready-queues Kahn: same indegree updates, two pops policies; count how often you must open the scarce queue.
- Complement traversal: `set`/`list` of unused vertices; on visit, erase and only skip adj-of-current — \(O((n+m)\log n)\).
- DAG DP after topo: longest path / path counts; fail cleanly if Kahn yields \(<n\) nodes (cycle).

## Where it appears in OAs / interviews
- **“Block hazards, then ask if all goods can escape”** → Solve The Maze / Monsters-style reachability with a preprocessing pass (Amazon/Meta grid variants).
- **“Friendship / shared skill ⇒ same group; min invites / teaches”** → Learning Languages / News Distribution CC counting.
- **“Order tasks with two machine types / cool-down”** → Coprocessor-style Kahn with two ready sets (build-system / scheduler interviews).
- **“Nearest opposite category from every index”** → reverse multi-source BFS (Nearest Opposite Parity); same pattern as multi-source infection, flipped.
