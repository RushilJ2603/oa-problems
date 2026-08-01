# 17 — Trees: LCA / Euler / Rerooting / DSU-on-tree (Depth Pass)

**Placement value:** Medium — second ladder after CSES Company Queries / Distances / Distinct Colors / 600E; these are the CF Div2 D–E and AtCoder ABC E–F drills that turn “I can write LCA” into “I can invent the path-diff / reroot transfer / centroid count.”
**Prereq topics:** Tree DFS, binary lifting LCA, Euler `tin/tout`, basic rerooting (CSES Distances II), Fenwick/segtree; finished the standard Trees ladder
**Pattern in one paragraph:** After Company Queries / Subtree Queries / Tree Painting, depth-pass tree problems hide the same four engines inside messier asks: path increments via LCA difference arrays, subtree+depth filters on an Euler tour, “answer for every root” with a non-trivial transfer (XOR, max-of-two-branches, marked-node distances), or count pairs through a centroid / heavy bag. Recognize them when the statement wants every-vertex answers, offline path/subtree updates, k-length paths, or “cut/rehang so the tree satisfies X.”

**Non-obvious tricks (internalize):**
1. Path \(u\!\to\!v\) mark: `+1` at \(u\), `+1` at \(v\), `-1` at \(\mathrm{lca}\), `-1` at \(\mathrm{parent}[\mathrm{lca}]\) (or `-2` at lca if counting vertices), then one upward DFS aggregates edge/vertex hits (Fools and Roads).
2. Sum-of-dist reroot: `ans[v] = ans[u] + n - 2\cdot sz[v]` when moving root \(u\to v\) (ABC220F); generalize by tracking a second aggregate (weight sum, XOR of `a[i]`).
3. White-subtree reroot (1324F): `down[v]=\max(0,\sum \mathrm{down}[\mathrm{child}])` then when moving \(u\to v\), peel \(v\)'s contribution from \(u\) and push the residual as \(v\)'s “up” value — never recompute from scratch.
4. Triple terminals: among \(\{\mathrm{lca}(a,b),\mathrm{lca}(b,c),\mathrm{lca}(a,c)\}\) the deepest is the unique meeting vertex of the three paths (832D); length of \(a\!-\!b\) via \(c\) is `dep[a]+dep[b]-2dep[lca(a,b)]` with the meeting substituted.
5. Depth-capped subtree add (1076E): Euler-range update on `[tin[v],tout[v]]` is not enough alone — couple with a depth BIT / process nodes by increasing depth so `+x` only hits nodes with `dep ≤ dep[v]+d`.
6. Binary lifting + weight prefix (1714G): store `sum[k][v]` = weight of the \(2^k\) jump; binary-search the deepest ancestor whose root-path sum stays \(\le S\).
7. Centroid count: each path has a unique highest centroid; remove centroid, add pairs with `d1+d2=k` from different components, recurse (CSES Fixed-Length Paths I) — the DSU-on-tree cousin when you only need length-\(k\) pairs.
8. Path-max for “MST for each edge”: binary-lift `mx[k][v]` = max edge on the \(2^k\) jump; replacement cost = MST + `w(e) - max_on_tree_path(u,v)`.

## Ladder (easy -> hard, 24 problems)

- [ ] [Military Problem](https://codeforces.com/problemset/problem/1006/E) — `Codeforces` `1600` — Euler `tin/tout` / k-th in subtree — **(core)** answer “who is the k-th vertex in the DFS list of v’s subtree”; gateway past CSES Subtree Queries.
- [ ] [Valera and Elections](https://codeforces.com/problemset/problem/369/C) — `Codeforces` `1600` — mark edges toward root — count minimal repair-nodes so every “bad” edge lies under one; tree-diff warm-up before Fools and Roads.
- [ ] [Kuro and Walking Route](https://codeforces.com/problemset/problem/979/C) — `Codeforces` `1600` — complement via two subtree sizes — total paths minus paths forced through forbidden edge \(x\!-\!y\); forces `sz` thinking.
- [ ] [D - Closed Paths](https://atcoder.jp/contests/abc014/tasks/abc014_4) — `AtCoder` `ABC014 D (~1600 CF-eq)` — LCA + cycle length — **(core)** AtCoder’s classic “path + back-edge” LCA drill; `dist(a,b)=dep[a]+dep[b]-2dep[lca]`.
- [ ] [D - Transit Tree Path](https://atcoder.jp/contests/abc070/tasks/abc070_d) — `AtCoder` `ABC070 D (~1600 CF-eq)` — LCA distances from fixed K — **(core)** precompute dist-from-K, answer `dist(K,x)+dist(K,y)` style queries without rebuilding.
- [ ] [Path Prefixes](https://codeforces.com/problemset/problem/1714/G) — `Codeforces` `1700` — binary lifting on weighted prefixes — **(core)** deepest ancestor with path-sum \(\le a_v\); lifts store sums, not just parents.
- [ ] [Gardening Friends](https://codeforces.com/problemset/problem/1822/F) — `Codeforces` `1700` — rerooting / eccentricity + edge bonus — max `dist·k - depth·c` over roots; reroot after one diameter-style DFS.
- [ ] [Link Cut Centroids](https://codeforces.com/problemset/problem/1406/C) — `Codeforces` `1700` — find/move centroid — **(core)** locate centroid(s), one edge swap to unique-ify; forces `sz` + “max component ≤ n/2” check.
- [ ] [E - Count Descendants](https://atcoder.jp/contests/abc202/tasks/abc202_e) — `AtCoder` `ABC202 E (~1800 CF-eq)` — Euler + depth buckets — **(core)** count nodes in subtree of \(u\) with exact depth \(d\); `tin/tout` + per-depth vectors / BIT.
- [ ] [F - Distance Sums 2](https://atcoder.jp/contests/abc220/tasks/abc220_f) — `AtCoder` `ABC220 F (~1800 CF-eq)` — rerooting ∑dist — **(core)** AtCoder twin of CSES Distances II; write the `+n-2sz` transfer cold.
- [ ] [Maximum White Subtree](https://codeforces.com/problemset/problem/1324/F) — `Codeforces` `1800` — rerooting max white — **(core)** the CF reroot tutorial problem; `down` then transfer residual “up”.
- [ ] [Connecting Universities](https://codeforces.com/problemset/problem/700/B) — `Codeforces` `1800` — contribution through each edge — **(core)** each edge pays `w · min(2·univ_in_subtree, 2k - …)`; template for “pairs whose path uses e”.
- [ ] [Vlad and Unfinished Business](https://codeforces.com/problemset/problem/1675/F) — `Codeforces` `1800` — Steiner tour on a tree — walk all marked nodes + destination; `2·(edges in minimal subtree) - path(start,dest)`.
- [ ] [Fools and Roads](https://codeforces.com/problemset/problem/191/C) — `Codeforces` `1900` — LCA path difference array — **(core)** offline +1 on paths, push to edges; the path-update template CSES Counting Paths prepares you for.
- [ ] [Vasya and a Tree](https://codeforces.com/problemset/problem/1076/E) — `Codeforces` `1900` — Euler + depth-limited subtree adds — **(core)** updates hit subtree ∩ depth window; BIT on Euler order keyed by depth.
- [ ] [Misha, Grisha and Underground](https://codeforces.com/problemset/problem/832/D) — `Codeforces` `1900` — triple-path LCA meeting point — **(core)** max overlap of two paths among three terminals; deepest of three LCAs.
- [ ] [Alyona and a tree](https://codeforces.com/problemset/problem/739/B) — `Codeforces` `1900` — binary lifting + fenwick on tree — **(stretch)** for each v count ancestors with dist condition; lift to cut-point, ±1 on Euler/stack.
- [ ] [Tree XOR](https://codeforces.com/problemset/problem/1882/D) — `Codeforces` `1900` — rerooting XOR costs — **(stretch)** cost flips by `sz`/`n-sz` when root crosses an edge; CM-band reroot algebra.
- [ ] [Book of Evil](https://codeforces.com/problemset/problem/337/D) — `Codeforces` `2000` — rerooting distances to marked — **(stretch)** every node’s max dist to an “evil” house ≤d; keep top-2 down distances, then up.
- [ ] [F - Expensive Expense](https://atcoder.jp/contests/abc222/tasks/abc222_f) — `AtCoder` `ABC222 F (~2000–2100 CF-eq)` — rerooting max path — **(stretch)** per-root max `dist+vertex_cost`; need excl-child prefix/suffix maxima.
- [ ] [New Year Tree](https://codeforces.com/problemset/problem/620/E) — `Codeforces` `2100` — Euler + bitset / lazy colors — **(stretch)** subtree color-assign + distinct-color count; tour range assign, OR-bitset combine.
- [ ] [Minimum spanning tree for each edge](https://codeforces.com/problemset/problem/609/E) — `Codeforces` `2100` — MST + LCA path-max — **(stretch)** for every edge, best spanning-tree weight if that edge is forced; lift stores max edge.
- [ ] [Ciel the Commander](https://codeforces.com/problemset/problem/321/C) — `Codeforces` `2100` — centroid decomposition constructive — **(stretch)** assign letters by centroid layers so adjacent ranks differ; CD entry ticket.
- [ ] [Fixed-Length Paths I](https://cses.fi/problemset/task/2080) — `CSES` `Tree Algorithms` — centroid / sack path counts — **(stretch)** count paths of length exactly k; CD or DSU-on-tree depth frequencies — the post-Distinct-Colors milestone.

## Must-internalize checklist (5-10 bullets)
- Euler `tin/tout`: subtree = contiguous range; ancestor test `tin[u] ≤ tin[v] ≤ tout[u]`; k-th in subtree = order-stat on the tour (Military Problem).
- Path aggregate offline: endpoint ±1 + LCA correction, then one DFS to push values onto edges/vertices (Fools and Roads / Counting Paths family).
- Binary lifting extras: besides `up[k][v]`, store `sum`/`mx`/`mn` on the jump; combine while equalizing depth and joint-lifting.
- Rerooting checklist: (1) down-DP from arbitrary root (2) formula to transfer across one edge using `sz` / residual (3) DFS2 visits each edge once.
- Top-2 down values: when the up-path must avoid the child you came from (Book of Evil / Expensive Expense), keep best and second-best child contributions.
- Centroid: component sizes after removal ≤ n/2; recurse independently; paths counted at the highest centroid they touch.
- DSU-on-tree / sack flashback: keep heavy child’s frequency map, add light children, answer, then clear if current node is light — same bag idea as Fixed-Length Paths depth counts.
- MST-for-edge: compute one MST, then for non-tree edges (or all edges) answer via path-max between endpoints on the tree.

## Where it appears in OAs / interviews
- **Org-chart range asks:** “k-th employee under manager v in DFS HR order” / “count reports at level d” — Military Problem / Count Descendants shape.
- **Cable / road usage:** “how many journeys use this road” after listing endpoint pairs — Connecting Universities / Fools and Roads contribution pattern.
- **Best warehouse / capital:** “pick a root minimizing total distance or max latency” — Distance Sums 2 / Gardening Friends / Expensive Expense rerooting.
- **Network with one forced link:** “MST if this edge must be included” — 609E; also the interview form of “path bottleneck between two nodes.”
