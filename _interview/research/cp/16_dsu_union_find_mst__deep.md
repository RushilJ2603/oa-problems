# 16 — DSU / Union-Find & MST (Depth Pass)

**Placement value:** High (second ladder after template Kruskal/Prim/component-size — CF Div2 C–E “rewrite as merges,” weighted DSU, Kruskal contribution, and MST variants that still show up as hard OA twists)
**Prereq topics:** Finished the standard DSU & MST ladder (find/union, reverse-time unions, basic Kruskal/Prim); sorting; light combinatorics on component sizes
**Pattern in one paragraph:** After provinces / redundant edge / Road Construction / Decayed Bridges, contest DSU stops being “run the template.” Edges encode constraints (equality, relative distance, same color, allowed swaps), Kruskal is run offline to accumulate \(\mathrm{size}_A\cdot\mathrm{size}_B\) contributions, or you maintain two forests / a complement graph / range-unions. Recognize it when merges are the only mutable state, when a threshold edge weight defines connectivity, or when the answer is a function of component sizes as edges are added light→heavy (or reverse).

**Non-obvious tricks (internalize):**
1. Weighted / potential DSU: store `delta[v]` = value(v)−value(parent); on `find`, compress deltas; `union(a,b,w)` sets relation `val[b]-val[a]=w` (People on a Line / Third Letter).
2. Kruskal contribution: sorting edges ascending and merging A,B of weight `w` adds `w·|A|·|B|` to “sum of max-edge on path” (ABC214D; same skeleton as Child and Zoo / Path Queries).
3. Same-weight batching: before unioning weight-`w` edges, count how many could still link different components; extras that fail after the batch force +1 ops to uniquify MST (MST Unification).
4. 0-1 MST / complement connectivity: MST weight = (#components in the 0-edge graph)−1; build components by iterating a `set` of unused vertices (cannot enumerate \(K_n\)).
5. Harmonious / range closure: after ordinary unions, each component must swallow `[min_id, max_id]` — walk that interval and union everything (pointer / next-DSU).
6. Dual forests: an edge is legal only if both DSUs would accept it (Graph Composition / Mocha-style); count how many merges remain to equalize.
7. Virtual star for MST: connect every vertex to the global-min `a_i` with weight `a_i+a_u`, then Kruskal on given edges ∪ star (Make It Connected).
8. Fixed-degree spanning tree: force exactly `k` edges incident to vertex 1 — DSU-partition the rest, then carefully pick which 1-edges close components.

## Ladder (easy -> hard, 24 problems)
- [ ] [DZY Loves Chemistry](https://codeforces.com/problemset/problem/445/B) — `Codeforces` `1400` — component → \(2^{\mathrm{sz}-1}\) — **(core)** each merge doubles danger; pure size-on-root bookkeeping after basics.
- [ ] [Mr. Kitayuta's Colorful Graph](https://codeforces.com/problemset/problem/505/B) — `Codeforces` `1400` — DSU per color — **(core)** `100` parallel UFFs; query = count colors with `find_c(u)==find_c(v)`.
- [ ] [Connect](https://codeforces.com/problemset/problem/1130/C) — `Codeforces` `1400` — two components + land bridge — **(core)** flood/DSU the lakes; min cost \((x_1-x_2)^2+(y_1-y_2)^2\) over cells in start vs end comps.
- [ ] [E - 1 or 2](https://atcoder.jp/contests/abc126/tasks/abc126_e) — `AtCoder` `ABC126 E (~1500)` — constraint components — XOR/parity links collapse to ordinary DSU; answer = #components (magicians to assign).
- [ ] [Bear and Friendship Condition](https://codeforces.com/problemset/problem/771/A) — `Codeforces` `1500` — component must be clique — **(core)** for every root, edges inside = \(\binom{\mathrm{sz}}{2}\); high-consensus “friendship graph” check.
- [ ] [Edgy Trees](https://codeforces.com/problemset/problem/1139/C) — `Codeforces` `1500` — DSU on 0-weight edges — **(core)** \(n^k - \sum \mathrm{sz}^k\) paths that use ≥1 red edge; classic size-pow contribution.
- [ ] [K-Complete Word](https://codeforces.com/problemset/problem/1332/C) — `Codeforces` `1500` — DSU on string positions — **(core)** union `i` with `n-1-i` and with `i+k`; per component take majority char.
- [ ] [Graph Composition](https://codeforces.com/problemset/problem/2060/E) — `Codeforces` `1500` — dual DSU forests — **(core)** edges of F/G; ops = remove contradicting + add to match components (post–Mocha Diana).
- [ ] [New Year Permutation](https://codeforces.com/problemset/problem/500/B) — `Codeforces` `1600` — allowed-swap components — **(core)** DSU on matrix-1 pairs; sort values inside each component onto sorted indices.
- [ ] [Socks](https://codeforces.com/problemset/problem/731/C) — `Codeforces` `1600` — DSU + mode color — **(core)** days link socks; per component recolor all but the most frequent color.
- [ ] [D - People on a Line](https://atcoder.jp/contests/abc087/tasks/arc090_b) — `AtCoder` `ABC087 D / ARC090 B (~1600)` — weighted DSU — **(core)** canonical potential-UFF; reject inconsistent `x_b - x_a = d`.
- [ ] [Love Rescue](https://codeforces.com/problemset/problem/939/D) — `Codeforces` `1600` — alphabet DSU / letter MST — **(core)** mismatch pairs as edges; spanning forest on 26 letters = min changes.
- [ ] [Harmonious Graph](https://codeforces.com/problemset/problem/1253/D) — `Codeforces` `1700` — range-closure unions — **(core)** after merges, force `[min,max]` of each component connected; count extra edges.
- [ ] [Cow and Snacks](https://codeforces.com/problemset/problem/1209/D) — `Codeforces` `1700` — DSU redundant friendships — **(core)** each failed union = one unhappy cow; answer = that count.
- [ ] [Fix a Tree](https://codeforces.com/problemset/problem/698/B) — `Codeforces` `1700` — break cycles → single root — functional graph + DSU; pick one root, redirect cycle heads.
- [ ] [The Third Letter](https://codeforces.com/problemset/problem/1850/H) — `Codeforces` `1700` — weighted DSU on positions — **(stretch)** same potential template as People on a Line; multi-test CF form.
- [ ] [D - Sum of Maximum Weights](https://atcoder.jp/contests/abc214/tasks/abc214_d) — `AtCoder` `ABC214 D (~1800)` — Kruskal \(\sum\) max-on-path — **(core)** add `w·sz[a]·sz[b]` on each merge; AtCoder twin of CF Path Queries math.
- [ ] [Maximum Distance](https://codeforces.com/problemset/problem/1081/D) — `Codeforces` `1800` — Kruskal until specials connect — **(core)** only `k` special vertices matter; last merged edge weight among them is the answer.
- [ ] [Road Reform](https://codeforces.com/problemset/problem/1468/J) — `Codeforces` `1800` — MST vs target `d` — **(stretch)** build MST; if max MST edge `≤ d` pay to raise/lower toward `d`, else pay to bring the lightest `>d` bridge down.
- [ ] [The Child and Zoo](https://codeforces.com/problemset/problem/437/D) — `Codeforces` `1900` — reverse Kruskal on node values — **(stretch)** add vertices high→low; contribution `min(a_u,a_v)·sz·sz` style pair counts.
- [ ] [Restructuring Company](https://codeforces.com/problemset/problem/566/D) — `Codeforces` `1900` — range union + point union — **(stretch)** type-2 unions on `[l,r]` via “next unmerged” DSU pointer — must-know optimization.
- [ ] [Make It Connected](https://codeforces.com/problemset/problem/1095/F) — `Codeforces` `1900` — MST + virtual star — **(stretch)** star from `argmin a_i`; Kruskal on `m+n` edges — Shichikuji-adjacent without rebuilding stations.
- [ ] [0-1 MST](https://codeforces.com/problemset/problem/1242/B) — `Codeforces` `1900` — complement-graph components — **(stretch)** MST cost = comps−1 in the dense 0-graph; set-iteration BFS/DSU.
- [ ] [Spanning Tree with One Fixed Degree](https://codeforces.com/problemset/problem/1133/F2) — `Codeforces` `1900` — MST/ST with `deg(1)=k` — **(stretch)** DSU components after removing 1; choose exactly `k` bridges from 1, then complete a spanning tree.
- [ ] [MST Unification](https://codeforces.com/problemset/problem/1108/F) — `Codeforces` `2100` — unique MST by +1 ops — **(stretch)** CM ceiling; per equal-weight batch, count edges that could replace a tree edge.

## Must-internalize checklist (5-10 bullets)
- Potential/weighted DSU API: `find` returns root and compresses `delta`; `relate(a,b,w)` / `same` / inconsistency detect.
- On merge of sizes \(A,B\), know the three formulas cold: components−1, \(\binom{A+B}{2}-\binom{A}{2}-\binom{B}{2}=A\cdot B\), and weight contribution \(w\cdot A\cdot B\).
- Kruskal variants: stop at `k` specials connected; batch equal weights; add virtual node/star edges before sorting.
- Range unions: maintain `next[i]` = first index not yet united with `i` (or DSU on “next pointer”) so `[l,r]` is \(O((r-l)\alpha^{-1})\) amortized total.
- Complement / 0-1 MST: never build \(K_n\); iterate neighbors of the sparse “missing” edges and erase from a global `set`.
- Dual-DSU constructive: enumerate candidate pairs (or given edges) and add iff both `union` succeed.
- Letter/string DSU: map `char → node` or `position → node`; majority vote or spanning forest on 26 nodes.
- When the statement says “max edge on path ≤ x” / “sum of max edges,” sort edges and DSU offline — do not LCA every pair.

## Where it appears in OAs / interviews
- **Constraint satisfaction on equals / distances:** “assign values with given differences” or “are these equations consistent?” — weighted DSU (People on a Line / Third Letter), same family as equality-equation DSU.
- **Redeploy / recolor inside groups:** “friendship / swap / day-link components; minimize changes” — Socks / New Year Permutation / K-Complete Word.
- **Wire a network with a twist:** “connect all servers; one node has fixed degree / build one hub cheaply / only 0-1 cable costs” — Fixed Degree / Make It Connected / 0-1 MST.
- **Score = f(component sizes over time):** “sum of dangers / pair counts as chemicals mix or edges activate” — DZY / Edgy Trees / Kruskal contribution (ABC214D).
