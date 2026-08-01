# 39 — Bitset optimization tricks

**Placement value:** Medium — rarely named “bitset” in OAs, but the *packed boolean / subset-sum reachability* idea (Partition Equal Subset Sum, “can you make sum S?”) shows up constantly; dense AND/OR / DAG reachability is a Candidate Master rating-builder Striver never covers.
**Prereq topics:** Bit manipulation basics, 0/1 knapsack / subset-sum DP, basic graphs (DFS/BFS, DAG topo, SCC intuition), DSU (for component-size knapsacks)
**Pattern in one paragraph:** When DP/state is **boolean** (reachable / adjacent / “exists”) and the dimension is thousands, pack bits into machine words (`std::bitset` / `uint64_t[]`) so AND/OR/XOR/shift run ~64× faster. Classic tells: subset-sum with `n·W` too big but `n·W/64` OK → `dp |= dp << w`; pairwise row/column overlaps → AND then `.count()`; DAG/SCC reachability → OR bitsets along topo order; complement-graph BFS → `_Find_next` over an “unvisited” bitset. Recognize constraints like `n≤2e3`–`5e3` with an `n²` or `n·W` bool loop that needs a `/64` constant.

## Ladder (easy -> hard, 22 problems)
- [ ] [A+B+C](https://atcoder.jp/contests/abc344/tasks/abc344_c) — `AtCoder` `ABC344-C` — bitset as packed bool[] — **(core)** ground-up: mark all `a+b+c` in a bitset, answer queries by `possible[x]`
- [ ] [Money Sums](https://cses.fi/problemset/task/1745) — `CSES` `Dynamic Programming` — knapsack shift — **(core)** first `dp |= dp << w`; list all reachable sums
- [ ] [Baby Ehab Partitions Again](https://codeforces.com/problemset/problem/1516/C) — `Codeforces` `1700` — partition + bitset — **(core)** OA-flavored: equal split, then remove one element so it’s impossible
- [ ] [Transitivity](https://atcoder.jp/contests/abc292/tasks/abc292_e) — `AtCoder` `ABC292-E` — Floyd bitset closure — **(core)** count missing transitive edges; `if (reach[i][k]) reach[i] |= reach[k]`
- [ ] [Unmerge](https://codeforces.com/problemset/problem/1381/B) — `Codeforces` `1800` — segment-length bitset — **(core)** split into decreasing-prefix chunks; knapsack whether half-length is reachable
- [ ] [School Excursion](https://cses.fi/problemset/task/1706) — `CSES` `Additional Problems II` — DSU sizes + bitset — **(core)** USACO Guide Bitsets focus; which team sizes are possible
- [ ] [PermuTree (easy version)](https://codeforces.com/problemset/problem/1856/E1) — `Codeforces` `1800` — tree knapsack bitset — **(core)** at each node, bitset-combine child subtree sizes for min imbalance
- [ ] [Hamming Distance](https://cses.fi/problemset/task/2136) — `CSES` `Advanced Techniques` — XOR + popcount — **(core)** CPH / Errichto drill; min Hamming over `n≤2e4`, `k≤30` bitstrings
- [ ] [Corner Subgrid Check](https://cses.fi/problemset/task/3360) — `CSES` `Advanced Techniques` — row AND existence — warm-up for the count version; same letter on four corners
- [ ] [Corner Subgrid Count](https://cses.fi/problemset/task/2137) — `CSES` `Advanced Techniques` — pair-rows AND + C(k,2) — **(core)** *the* `O(n²·n/64)` bitset AND classic (`n≤3000`)
- [ ] [Modulo Sum](https://codeforces.com/problemset/problem/577/B) — `Codeforces` `1900` — pigeonhole + mod bitset — **(core)** if `n≥m` YES; else bitset knapsack of residues
- [ ] [0-1 MST](https://codeforces.com/problemset/problem/1242/B) — `Codeforces` `1900` — complement components — **(core)** BFS the complement via unvisited set / bitset `_Find_next`; weight-0 edges inside components
- [ ] [Oddly Similar](https://atcoder.jp/contests/abc348/tasks/abc348_f) — `AtCoder` `ABC348-F` — column-value XOR bitsets — **(core)** count pairs with odd #matches; editorial bitset `/64`
- [ ] [Reachable Nodes](https://cses.fi/problemset/task/2138) — `CSES` `Advanced Techniques` — DAG reachability bitsets — **(core)** topo OR of children’s bitsets; print popcounts
- [ ] [Reachability Queries](https://cses.fi/problemset/task/2143) — `CSES` `Advanced Techniques` — SCC + bitset — **(core)** condense to DAG, then same OR trick for `q` reach queries
- [ ] [Knights](https://codeforces.com/problemset/problem/33/D) — `Codeforces` `2000` — region bitsets — **(stretch)** electicode sheet; point-in-circle masks, shortest path on regions
- [ ] [Connected Components?](https://codeforces.com/problemset/problem/920/E) — `Codeforces` `2100` — complement CC sizes — **(stretch)** same complement-BFS family as 0-1 MST; output sorted sizes
- [ ] [Careful Maneuvering](https://codeforces.com/problemset/problem/993/C) — `Codeforces` `2100` — geometry + bitsets of hits — **(stretch)** electicode bitset sheet; ship lasers as bitsets of destroyed ships
- [ ] [Directed Graph and Query](https://atcoder.jp/contests/abc287/tasks/abc287_h) — `AtCoder` `ABC287-Ex` — online Floyd + bitset — **(stretch)** process vertices in order; bitset OR speeds `O(n³/64)`
- [ ] [Persistent Bookcase](https://codeforces.com/problemset/problem/707/D) — `Codeforces` `2200` — bitset shelves + undo DFS — **(stretch)** each shelf a bitset; tree of operations with rollback
- [ ] [Mediator](https://atcoder.jp/contests/abc350/tasks/abc350_g) — `AtCoder` `ABC350-G` — hybrid adj-list / bitset — **(stretch)** memory: only high-degree vertices get bitsets
- [ ] [Jumping sequence](https://atcoder.jp/contests/abc221/tasks/abc221_g) — `AtCoder` `ABC221-G` — hard subset-sum + reconstruct — **(stretch)** reduce to subset sum; bitset (or Pisinger) then recover signs

## Must-internalize checklist (5-10 bullets)
- `bitset<N>` ops (AND/OR/XOR/shift/`.count()`/`.test()`/`.set()`) cost `O(N/64)`; prefer compile-time `N` or your own `uint64_t` blocks when `N` is dynamic.
- Subset-sum reachability: `dp[0]=1; for w in a: dp |= dp << w` (0/1); for bounded counts, binary-split multiplicities then shift.
- Pairwise overlap: store each row/set as a bitset; answer = `(A & B).count()` (or XOR for parity-of-matches).
- DAG reachability: `reach[u][u]=1; for u in topo: for v in adj[u]: reach[u] |= reach[v]` (direction depends on edge meaning).
- SCC queries: Kosaraju/Tarjan → DAG on components → bitset reachability on the condensation.
- Complement-graph traversal: keep unvisited vertices in a bitset/set; iterate with `_Find_first` / `_Find_next`, skip real neighbors.
- Memory: `n` bitsets of length `n` ≈ `n²/8` bytes; if MLE, process in blocks of 64 sources, or only materialize bitsets for high-degree nodes.
- Don’t confuse with **bitmask DP** (`n≤20`, state = mask): bitset opt is the `/64` speedup on large boolean arrays, not `2^n` DP.

## Where it appears in OAs / interviews
- “Partition array into two equal-sum subsets” / “subset with sum = S” (Partition Equal Subset Sum family) — bool knapsack; bitset is the CP-speed version of the same idea.
- “Which team sizes are possible after merging friend groups?” — DSU component sizes + subset-sum (School Excursion shape).
- “n≤2000 bitstrings / rows — count pairs with property on columns” — packed AND/XOR + popcount (Corner Subgrid / Oddly Similar shape).
- “Can u reach v in a large digraph / many queries?” — SCC + bitset reachability (CSES Reachability Queries shape), not Floyd on `n=1e5`.
