# 13 — DP IV: Bitmask & Digit DP — Depth Pass

**Placement value:** Medium — second wave after Matching / Elevator / Classy Numbers / TSP; these are the CF Div2 D–E and ABC E drills that hide mask packing, profile DP, and digit-bound construction rather than announcing the template.
**Prereq topics:** Bit ops + `__builtin_popcount`, basic memo/DP, the standard Bitmask & Digit ladder (assignment, elevator packing, `tight` digit DP, TSP `dp[mask][last]`, submask `O(3^n)`)
**Pattern in one paragraph:** After the famous set, contests stop saying “bitmask DP” and instead leave a tiny dimension (`n≤20`, `k≤10` specials, width ≤3–8, ≤10 factorials, ≤16 rows) or a huge numeric bound with a digit invariant. Depth-pass states still look like `dp[mask]`, `dp[mask][last]`, or `dfs(pos,tight,extra)`, but the *extra* work is non-obvious: BFS/APSP before TSP, topo-prereq checks inside transitions, AND-only shrinkage, bit-by-bit greedy with a DP oracle, column-profile compatibility, or compressing an unbounded digit-product into a small ID. Spot it when brute subsets/`2^n·n^2` fits, when `[L,R]` is up to `10^18`+ with a digit property, or when a thin grid forces “fill one column / one mask at a time”.

## Ladder (easy -> hard, 25 problems)

- [ ] [Preparing Olympiad](https://codeforces.com/problemset/problem/550/B) — `Codeforces` `1400` — enumerate all `2^n` subsets — **(core)** constraints on count / sum / max−min; cleanest post-basics “mask = subset” drill (not a full DP yet)
- [ ] [Chain Contestant](https://atcoder.jp/contests/abc215/tasks/abc215_e) — `AtCoder` `ABC E (~1400 CF-eq)` — `dp[mask][last]` on letters — **(core)** longest subsequence with distinct used letters + adjacency rule; lightweight TSP-shaped mask DP
- [ ] [Factorials and Powers of Two](https://codeforces.com/problemset/problem/1646/C) — `Codeforces` `1500` — mask over ≤15 factorials — **(core)** subtract a factorial-subset sum, finish with popcount of remainder; “tiny universe → mask”
- [ ] [We Like AGC](https://atcoder.jp/contests/abc122/tasks/abc122_d) — `AtCoder` `ABC D (~1500 CF-eq)` — string DP, last-3 as state — **(core)** forbid AGC/adjacent-swap patterns; last characters packed as a small mask / base-4 state
- [ ] [Undoubtedly Lucky Numbers](https://codeforces.com/problemset/problem/244/B) — `Codeforces` `1600` — generate ≤2 distinct digits — **(core)** DFS/digit-build all numbers whose digit set size ≤2; digit DP without a full `tight` table
- [ ] [Boboniu and Bit Operations](https://codeforces.com/problemset/problem/1395/C) — `Codeforces` `1600` — feasibility over OR candidates — **(core)** binary-search / iterate possible OR values; each `a_i` must hit some `b_j` under the candidate mask
- [ ] [Magical Ornament](https://atcoder.jp/contests/abc190/tasks/abc190_e) — `AtCoder` `ABC E (~1650 CF-eq)` — BFS + TSP on `k` specials — **(core)** all-pairs shortest paths among ≤10 keys, then `dp[mask][i]` Hamiltonian; the “reduce graph then mask” template
- [ ] [Footrace](https://atcoder.jp/contests/abc041/tasks/abc041_d) — `AtCoder` `ABC D (~1670 CF-eq)` — count topo orders via mask — **(core)** `dp[mask]` = ways to place exactly the set `mask`; add `v∉mask` only if all prerequisites already in `mask`
- [ ] [Bicolorings](https://codeforces.com/problemset/problem/1051/D) — `Codeforces` `1700` — DP on last-column color pair — **(core)** `n` columns, 2-colorings; state = coloring of previous two cells / component-count contribution
- [ ] [Barcode](https://codeforces.com/problemset/problem/225/C) — `Codeforces` `1700` — column-run DP — **(core)** paint columns black/white with run-length limits; prefix costs + DP over last color / length (profile warm-up)
- [ ] [Permute Digits](https://codeforces.com/problemset/problem/915/C) — `Codeforces` `1700` — greedy under upper bound — **(core)** rearrange digits of `a` to get largest ≤ `b`; digit-by-digit with multiset — digit-DP instinct without memo
- [ ] [Don't Blame Me](https://codeforces.com/problemset/problem/1829/H) — `Codeforces` `1700` — subsequence AND = `k` — **(core)** `dp[i][mask]` / rolling AND transitions; AND only shrinks bits — classic CF mask+combinatorics
- [ ] [Forbidden Digits](https://atcoder.jp/contests/abc007/tasks/abc007_4) — `AtCoder` `ABC D (~1700 CF-eq)` — digit DP avoid digits — **(core)** count `[1..N]` (or range) with no forbidden digit; pure `(pos,tight,leading)` skeleton
- [ ] [Travelling Salesman and Special Numbers](https://codeforces.com/problemset/problem/914/C) — `Codeforces` `1800` — digit DP + popcount chain — **(core)** count `x≤n` with `f^{k}(x)=1` where `f=popcount`; digit-DP ways to each digit-sum, then DP on sum→popcount steps
- [ ] [Cunning Gena](https://codeforces.com/problemset/problem/417/D) — `Codeforces` `1900` — friends-sorted problem mask — **(core)** sort by friends needed; `dp[mask]` min cost to solve problem-set `mask` with current friend budget
- [ ] [Bookshelves](https://codeforces.com/problemset/problem/981/D) — `Codeforces` `1900` — bit-greedy + partition DP — decide answer bits MSB→LSB; check whether `a` can split into `k` segments each covering the fixed prefix of bits
- [ ] [Shuffling Songs](https://codeforces.com/problemset/problem/1950/G) — `Codeforces` `1900` — Hamiltonian path on songs — genre/writer adjacency; `dp[mask][last]` longest path visiting each song ≤1
- [ ] [Unlucky Numbers](https://codeforces.com/problemset/problem/1808/C) — `Codeforces` `1900` — min distinct digits in `[L,R]` — **(core)** digit DP / constructive: minimize `|digit set|` of some `x∈[L,R]`; tight + used-mask
- [ ] [Rudolf and CodeVid-23](https://codeforces.com/problemset/problem/1846/G) — `Codeforces` `1900` — shortest path on disease mask — **(stretch)** state `(medicine mask of cured bits)`; Dijkstra/0-1 BFS over `2^n·m` medicine edges
- [ ] [Digit Products](https://atcoder.jp/contests/abc208/tasks/abc208_e) — `AtCoder` `ABC E (~2000 CF-eq)` — digit DP + product compression — **(stretch)** count ≤`N` with digit-product ≤`K`; map products to ≤ a few thousand IDs
- [ ] [Minimax Problem](https://codeforces.com/problemset/problem/1288/D) — `Codeforces` `2000` — BS + coverage mask — **(stretch)** binary-search answer `x`; each array → bitmask of coords ≥`x`; need two masks whose OR is full
- [ ] [Elongated Matrix](https://codeforces.com/problemset/problem/1102/F) — `Codeforces` `2000` — TSP on ≤16 rows — **(stretch)** edge weight = min adjacent-pair diff between rows; Hamiltonian path / cycle mask DP + BS on threshold
- [ ] [505](https://codeforces.com/problemset/problem/1391/D) — `Codeforces` `2000` — column profile DP — **(stretch)** `n≤3` so column mask is `2^n`; transitions require every 2×2 has odd number of 1s
- [ ] [Playlist for Polycarp (easy version)](https://codeforces.com/problemset/problem/1185/G1) — `Codeforces` `2100` — playlist mask DP — **(stretch)** `dp[mask][last_genre][time]` / count sequences with genre constraints; assignment-flavored with extras
- [ ] [Random Task](https://codeforces.com/problemset/problem/431/D) — `Codeforces` `2100` — binary digit DP — **(stretch)** find min `n` with exactly `k` numbers in `0..n` having popcount = `m`; binary-length digit DP + BS

## Must-internalize checklist (technique notes)

- **Specials-then-TSP:** when only `k≤20` “keys” matter on a big graph, BFS/APSP among keys first, then `dp[mask][i]` on the complete digraph (Magical Ornament / Playlist shape).
- **Topo mask:** `dp[mask] += dp[mask^1<<v]` only if every prerequisite of `v` lies in `mask^1<<v` (Footrace); same idea as counting linear extensions.
- **AND / OR shrinkage:** iterating `new = old & a[i]` (Don't Blame Me) or checking `a[i] & ~cand` (Boboniu) — bits only disappear; state space stays `2^{bitwidth}`.
- **Bit-greedy + oracle:** fix answer bits from MSB; a segment/partition DP asks “can we still realize the frozen high bits?” (Bookshelves) — do not DP the full numeric answer.
- **BS + coordinate mask:** threshold `x` turns each vector into a bitset of “good coordinates”; feasibility = exists a set of vectors whose OR is `(1<<m)-1` (Minimax; often just two).
- **Digit product / sum compression:** raw product explodes — map every reachable product (or digit-sum) to a dense ID before memoizing (Digit Products / Travelling Salesman Special Numbers).
- **Thin-grid profile:** width `w≤8` (or `n≤3`) ⇒ process the long direction; state = occupancy/colors of the previous column, reject incompatible 2×2 / run patterns (505 / Barcode / Bicolorings).
- **Used-digit mask inside digit DP:** for “≤k distinct digits” / “minimize distinct digits in range”, keep `mask` of digits used so far plus `tight` (Unlucky Numbers; same family as Nearest Beautiful).

## Where it appears in OAs / interviews

- **“Visit k POIs on a map / playlist with genre rules”** — Magical Ornament / Playlist / Shuffling Songs: shortest paths or adjacency first, then Hamiltonian mask DP.
- **“Count valid strings / colorings with local forbidden patterns”** — We Like AGC / Bicolorings / 505: sliding window of last few symbols packed into a mask.
- **“Largest arrangement / next number under digit constraints”** — Permute Digits / Forbidden Digits / Unlucky Numbers: left-to-right under an upper bound (OA classic disguised as “format the serial number”).
- **“Assign a tiny set of skills/problems/medicines”** — Cunning Gena / Rudolf CodeVid / Factorials-and-powers: `2^n` over the skill mask, often after sorting an external cost dimension.
