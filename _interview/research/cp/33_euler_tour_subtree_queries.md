# 33 — Euler tour + subtree/path queries (BIT/segtree)

**Placement value:** Medium — org-chart / file-tree “sum or update this department” maps directly to flatten+BIT; full path/LCA variants are rarer in OAs but dominate CF Div2 D–E tree DS. Striver never teaches tree linearization, so this is a pure CP unlock.
**Prereq topics:** DFS on trees / subtree sizes, Fenwick & basic segment tree (topic 20), difference arrays, LCA / binary lifting (topic 17)

**Pattern in one paragraph:** Root the tree and DFS-timestamp each node: enter → `tin[v]`, leave → `tout[v]`. Then the subtree of `v` is the contiguous index range `[tin[v], tout[v]]` (or `[tin[v], tin[v]+sz[v]-1]`). Put a Fenwick/segtree on that linear order so **subtree** ops become **range** ops, and **root→node path** ops become **prefix** ops (via the standard `+x` at `tin`, `−x` at `tout+1` difference trick). Ancestor tests are `tin[u] ≤ tin[v] ≤ tout[u]`. Combine with LCA for arbitrary `u–v` paths. Signal words: subtree sum/add/flip after updates, values on root→node path, “descendants at depth h”, color assign on a whole subtree, company hierarchy queries.

## Ladder (easy -> hard, 22 problems)
- [ ] [Ki](https://atcoder.jp/contests/abc138/tasks/abc138_d) — `AtCoder` `ABC138 D` — subtree add / DFS push — **(core)** add on subtree root then push; mental model before BIT-on-tour
- [ ] [Subordinates](https://cses.fi/problemset/task/1674) — `CSES` `Tree Algorithms` — subtree sizes — **(core)** `sz[v] = tout[v]−tin[v]` (or count on exit); tour length intuition
- [ ] [Subtree Queries](https://cses.fi/problemset/task/1137) — `CSES` `Tree Algorithms` — Euler + Fenwick PURS — **(core)** *the* USACO Guide / CPH template: point-set at `tin[v]`, range-sum `[tin[v], tout[v]]`
- [ ] [Path Queries](https://cses.fi/problemset/task/1138) — `CSES` `Tree Algorithms` — path-to-root via BIT — **(core)** range-update on subtree ⇒ prefix to `tin[s]` = root→s sum
- [ ] [Counting Paths](https://cses.fi/problemset/task/1136) — `CSES` `Tree Algorithms` — tree difference + LCA — **(core)** mark path endpoints, push diffs up; no DS yet, same tour mindset
- [ ] [Count Descendants](https://atcoder.jp/contests/abc202/tasks/abc202_e) — `AtCoder` `ABC202 E` — Euler + depth lists — **(core)** per-depth `tin` vectors + binary search inside `[tin[u], tout[u]]`
- [ ] [Distinct Colors](https://cses.fi/problemset/task/1139) — `CSES` `Tree Algorithms` — Euler + last-occurrence BIT — **(core)** USACO Guide; offline “distinct in `[tin,tout]`” (alt: small-to-large)
- [ ] [Fools and Roads](https://codeforces.com/problemset/problem/191/C) — `Codeforces` `1900` — path mark on edges — **(core)** +1/−1 on path via LCA, DFS accumulate; edge-path classic
- [ ] [Tree Queries](https://codeforces.com/problemset/problem/1328/E) — `Codeforces` `1900` — ancestor via `tin/tout` — **(core)** path-cover check with Euler timestamps (often + one lift)
- [ ] [Unusual Entertainment](https://codeforces.com/problemset/problem/1899/G) — `Codeforces` `1900` — descendant in array range — **(core)** modern Div2 G; `tin` of `p[l..r]` hits `[tin[x], tout[x]]` (BIT / merge-sort tree)
- [ ] [Vasya and a Tree](https://codeforces.com/problemset/problem/1076/E) — `Codeforces` `1900` — depth-capped subtree add — **(core)** DFS + Fenwick on depth (or Euler + depth filter); CF staple
- [ ] [Alyona and a tree](https://codeforces.com/problemset/problem/739/B) — `Codeforces` `1900` — path condition + BIT — **(core)** walk ancestors with tour Fenwick / offline add-on-path
- [ ] [Distance Queries on a Tree](https://atcoder.jp/contests/abc294/tasks/abc294_g) — `AtCoder` `ABC294 G` — Euler + BIT + LCA — **(core)** edge-weight update + `dist(u,v)` via root prefixes; interview-shaped combo
- [ ] [Propagating tree](https://codeforces.com/problemset/problem/383/C) — `Codeforces` `2000` — Euler + parity Fenwick — **(stretch)** odd/even depth sign flip on subtree range-update
- [ ] [Danil and a Part-time Job](https://codeforces.com/problemset/problem/877/E) — `Codeforces` `2000` — Euler + lazy flip — **(stretch)** subtree XOR-flip / count-1s; first lazy-on-tour drill
- [ ] [A Growing Tree](https://codeforces.com/problemset/problem/1891/F) — `Codeforces` `2000` — offline Euler + BIT — **(stretch)** build final tree, reverse ops; dynamic add-node → static tour
- [ ] [Passable Paths (hard version)](https://codeforces.com/problemset/problem/1702/G2) — `Codeforces` `2000` — multi-node path cover — **(stretch)** compress via LCA depths / `tin`; tour fluency under casework
- [ ] [Water Tree](https://codeforces.com/problemset/problem/343/D) — `Codeforces` `2100` — Euler + lazy fill/empty — **(stretch)** subtree assign + path-to-root clear; famous CF DS milestone
- [ ] [New Year Tree](https://codeforces.com/problemset/problem/620/E) — `Codeforces` `2100` — Euler + lazy bitmask — **(stretch)** ≤60 colors → `uint64` OR on tour ranges
- [ ] [Blood Cousins](https://codeforces.com/problemset/problem/208/E) — `Codeforces` `2100` — k-th ancestor + depth bags — **(stretch)** lift then count same-depth in subtree (Euler / DSU-on-tree)
- [ ] [Path Queries II](https://cses.fi/problemset/task/2134) — `CSES` `Tree Algorithms` — HLD path max — **(stretch)** when Euler alone can’t do arbitrary path aggregates with updates
- [ ] [Tree Requests](https://codeforces.com/problemset/problem/570/D) — `Codeforces` `2200` — depth + Euler + XOR parity — **(stretch)** palindrome-from-letters at depth `h` in subtree; CF classic (slightly above CM band)

## Must-internalize checklist (5-10 bullets)
- Write `tin/tout` (or `in/out`) in one DFS; subtree of `v` = contiguous `[tin[v], tout[v]]`; `sz[v] = tout[v] − tin[v]` (convention-dependent — pick one and stick to it).
- Ancestor test in \(O(1)\): `tin[u] ≤ tin[v] && tout[v] ≤ tout[u]` (equivalently `tin[u] ≤ tin[v] ≤ tout[u]` with matching `tout` convention).
- Subtree PURS: store value at `tin[v]`; point update `tin[v]`; query sum/min/OR on `[tin[v], tout[v]]` with Fenwick or segtree.
- Path root→`u`: on value change of `v` by `δ`, do range-add `[tin[v], tout[v]]` by `δ` (BIT-as-diff: `+δ` at `tin[v]`, `−δ` at `tout[v]+1`); answer = prefix sum to `tin[u]`.
- Path `u–v`: `path(u)+path(v)−2·path(lca)` (edge weights) or adjust by `±value[lca]` for node weights; need LCA template.
- Subtree assign / flip → lazy segtree on the tour array (Danil / New Year Tree / Water Tree).
- Offline distinct-in-subtree: scan Euler order, keep only last index of each color in a BIT (Distinct Colors).
- Know the limit: Euler shines for **subtrees** and **root-paths**; arbitrary path aggregates with updates usually need **HLD** (Path Queries II).

## Where it appears in OAs / interviews
- **Org / manager trees:** “sum salaries under manager X” or “add bonus to department X” → Subtree Queries / Ki (flatten + Fenwick).
- **File-system / nested folders:** toggle or recolor a folder and all descendants → Euler range update (Danil / New Year Tree shape, often simplified).
- **Path cost after edge edits:** “update road length, query distance between cities” → ABC294 G / CSES Path Queries + LCA (Juspay-style tree distance interviews).
- **Hierarchy reachability:** “is A an ancestor of B?” / “any of these IDs under boss X?” → `tin/tout` checks (Tree Queries / Unusual Entertainment).
