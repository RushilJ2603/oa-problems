# 42 — CSES Problem Set digest (post-Striver)

**Placement value:** High — CSES is the standard bridge from Striver/LC templates to contest constraints; Sorting & Searching + Range Queries + Trees + contest Graphs/DP cover most OA and Div2 C–D patterns Striver never drills in CF form.
**Prereq topics:** Striver A2Z completed (arrays, BS incl. on-answer, trees/BST, graphs Dijkstra/topo/MST/DSU/SCC, classic DP catalog, KMP/Z/hash basics) — algorithms known, contest form not
**Pattern in one paragraph:** Treat CSES as a **section-priority curriculum**, not a “solve all 300” grind. Post-Striver: **skip/skim Introductory** (and easy Sorting warmups that are pure LC). **Do deeply:** Sorting & Searching (STL/multiset/sweep/BS-on-answer), **Range Queries** (Fenwick/segtree/sparse — mostly new), **Tree Algorithms** (diameter, rerooting, LCA/binary lifting, Euler+BIT), **Graph Algorithms** contest flavors (state Dijkstra, Bellman-Ford cycles, functional binary lifting, SCC/2-SAT), and **DP** contest gems (Array Description, Counting Towers, Projects, Elevator Rides, Counting Numbers). **Selective:** Mathematics (modular expo II, combos, Nim, matrix), Strings (borders/periods beyond KMP). **Defer:** Geometry, Additional Problems, Interactive, most Advanced Techniques until cores are solid (except Meet-in-the-Middle). Signal you’re using CSES right: same pattern as Striver, but `n≤2e5`, multi-query, and “write the template under constraints.”

## Ladder (easy -> hard, 26 problems)

- [ ] [Restaurant Customers](https://cses.fi/problemset/task/1619) — `CSES` `Sorting and Searching` — sweep +/−1 — *the* arrival/departure line-sweep; max concurrent = running sum
- [ ] [Concert Tickets](https://cses.fi/problemset/task/1091) — `CSES` `Sorting and Searching` — multiset `upper_bound` — **(core)** CSES/USACO Guide; assign largest ticket ≤ price (`--it` after upper_bound)
- [ ] [Towers](https://cses.fi/problemset/task/1073) — `CSES` `Sorting and Searching` — multiset / patience — min piles = LIS-of-non-increasing flavor; CF “cubes/towers” shape
- [ ] [Factory Machines](https://cses.fi/problemset/task/1620) — `CSES` `Sorting and Searching` — BS-on-answer — **(core)** “can we make `t` products by time `mid`?”; *the* timed-OA BS drill
- [ ] [Sagheer and Nubian Market](https://codeforces.com/problemset/problem/812/C) — `Codeforces` `1500` — BS on count `k` — transfer: cost of buying first `k` after reweight; CSES Factory Machines → CF
- [ ] [Room Allocation](https://cses.fi/problemset/task/1164) — `CSES` `Sorting and Searching` — sweep + free-room PQ — **(core)** assign room IDs online; OA hotel/server allocation
- [ ] [Subarray Sums II](https://cses.fi/problemset/task/1661) — `CSES` `Sorting and Searching` — prefix + hashmap — count subarrays with sum `x`; OA classic (watch `long long` + empty prefix)
- [ ] [Array Description](https://cses.fi/problemset/task/1746) — `CSES` `Dynamic Programming` — fill with `|a_i−a_{i+1}|≤1` — **(core)** first “contest DP” after Striver knapsack; `dp[i][v]` ways
- [ ] [Counting Towers](https://cses.fi/problemset/task/2413) — `CSES` `Dynamic Programming` — tiling recurrence — 2-wide tower states; forces clean recurrence design (not LC memo copy)
- [ ] [Projects](https://cses.fi/problemset/task/1140) — `CSES` `Dynamic Programming` — weighted intervals + BS — **(core)** sort by end, `dp[i]=max(skip, reward+dp[prev])`; OA scheduling upgrade
- [ ] [Flowers](https://atcoder.jp/contests/dp/tasks/dp_q) — `AtCoder` `DP contest Q` — BIT for increasing-height DP — AtCoder Educational DP; max beauty with LIS-style constraint
- [ ] [Dynamic Range Sum Queries](https://cses.fi/problemset/task/1648) — `CSES` `Range Queries` — Fenwick / segtree PURS — **(core)** *start Range Queries here*; Striver never forced this DS under CF constraints
- [ ] [Nested Ranges Count](https://cses.fi/problemset/task/2169) — `CSES` `Sorting and Searching` — compress + Fenwick — sort endpoints, count contained/containing; CF Nested Segments twin
- [ ] [Flight Discount](https://cses.fi/problemset/task/1195) — `CSES` `Graph Algorithms` — Dijkstra with state — **(core)** `dist[u][usedCoupon]`; *the* “expand node state” CF graph pattern
- [ ] [Hotel Queries](https://cses.fi/problemset/task/1143) — `CSES` `Range Queries` — segtree walk first `≥ x` — **(core)** descent on max-tree; OA “first free seat/server”
- [ ] [Tree Distances I](https://cses.fi/problemset/task/1132) — `CSES` `Tree Algorithms` — rerooting / 2-pass — **(core)** max distance from every node; do Tree Diameter first if rusty
- [ ] [Choosing Capital for Treeland](https://codeforces.com/problemset/problem/219/D) — `Codeforces` `1700` — rerooting on directed edges — transfer: CSES Tree Distances → CF “min reverse edges to root”
- [ ] [High Score](https://cses.fi/problemset/task/1673) — `CSES` `Graph Algorithms` — Bellman-Ford + positive cycle — max path with “∞ if positive cycle reaches”; CF “score” trap classic
- [ ] [Company Queries II](https://cses.fi/problemset/task/1688) — `CSES` `Tree Algorithms` — LCA binary lifting — **(core)** jump table `up[k][v]`; Distance Queries / Counting Paths reuse it
- [ ] [Planets Queries I](https://cses.fi/problemset/task/1750) — `CSES` `Graph Algorithms` — functional binary lifting — `k`-th successor in functional graph; same jumps as LCA, no tree
- [ ] [Elevator Rides](https://cses.fi/problemset/task/1653) — `CSES` `Dynamic Programming` — bitmask DP — contest bitmask beyond assignment; `dp[mask]=(rides, last_load)`
- [ ] [Counting Numbers](https://cses.fi/problemset/task/2220) — `CSES` `Dynamic Programming` — digit DP — count `[a,b]` with no adjacent equal digits; digit-DP template Striver under-covers
- [ ] [Meet in the Middle](https://cses.fi/problemset/task/1628) — `CSES` `Advanced Techniques` — subset-sum MITM — **(core)** `n≤40` → two halves `2^{n/2}`; first Advanced Techniques must-do
- [ ] [Distinct Colors](https://cses.fi/problemset/task/1139) — `CSES` `Tree Algorithms` — small-to-large / Euler+BIT — **(stretch)** subtree distinct count; Candidate Master tree DS
- [ ] [Counting Tilings](https://cses.fi/problemset/task/2181) — `CSES` `Dynamic Programming` — profile / broken-profile DP — **(stretch)** grid tiling by column masks; hard DP milestone
- [ ] [Distance in Tree](https://codeforces.com/problemset/problem/161/D) — `Codeforces` `1800` — tree DP paths of length `k` — **(stretch)** CSES Fixed-Length Paths warm-up twin; CM rating-builder

## Must-internalize checklist (5-10 bullets)

- **Section order post-Striver:** Sorting & Searching (STL/sweep/BS) → DP contest gems → Graphs (state Dijkstra / BF / lifting) → Range Queries (whole section) → Trees (diameter → rerooting → LCA → Euler+BIT) → selective Math/Strings → MITM → then stretch Advanced/Additional.
- **Skip list:** Introductory (except maybe Gray Code / Digit Queries if weak on construction); Geometry for placement; Additional Problems until cores done.
- **STL contest kits:** `multiset` + `--upper_bound` (Concert Tickets), ordered set / PBDS optional, sweep events `(time, ±1)`, priority queue for free resources (Room Allocation).
- **BS-on-answer reflex:** monotone `can(mid)` under `n≤2e5` and answer on `[0, 1e18]` (Factory Machines); always `long long`.
- **Range-query ladder:** prefix → sparse RMQ → Fenwick PURS → segtree walk → lazy `(stretch)`; Dynamic Range Sum is the entry ticket.
- **Tree kit:** diameter (2-BFS) → rerooting (Tree Distances I/II) → binary lifting LCA → Euler tour + Fenwick for subtree/path.
- **Graph contest kit:** Dijkstra with extra state (Flight Discount); Bellman-Ford + cycle reachability (High Score); functional binary lifting (Planets Queries); SCC/2-SAT later in the same section.
- **DP contest kit:** constrained fill (Array Description), tiling recurrences (Counting Towers), weighted intervals (Projects), bitmask (Elevator Rides), digit DP (Counting Numbers); AtCoder Educational DP contest is the parallel track.
- **`n≤40` / `2^n` too big → MITM** (CSES Meet in the Middle); don’t force knapsack DP.

## Where it appears in OAs / interviews

- “Max concurrent users / rooms / servers given intervals” → Restaurant Customers / Room Allocation sweep (Amazon/Uber-style scheduling screens).
- “Point update + range sum / first hotel with capacity ≥ x” → CSES Dynamic Range Sum / Hotel Queries (API-style OA DS questions past plain prefix sums).
- “Shortest path with one coupon / discount edge” → Flight Discount state Dijkstra (common Div2 C/D and harder OA graph twist).
- “Count numbers in `[L,R]` with digit constraints” / “n≤40 subset sum” → Counting Numbers digit DP / Meet-in-the-Middle (when LC knapsack or `2^n` is the wrong reflex).
