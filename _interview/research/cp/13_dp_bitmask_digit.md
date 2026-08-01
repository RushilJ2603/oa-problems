# 13 — DP IV: Bitmask DP (Subset / TSP / Assignment) & Digit DP

**Placement value:** Medium (harder OAs reuse assignment-under-mask and “count numbers in `[L,R]` with a digit property”; essential for CF ~1600–2100, not as common as knapsack/LCS in easy screens)
**Prereq topics:** Intro DP / memoization, bit manipulation (set/unset/`__builtin_popcount`), recursion; 0/1 knapsack intuition helps for elevator-style subset packing

**Pattern in one paragraph:** Bitmask DP encodes a small set of ≤20 items/cities/roles as bits of an integer. Typical states: `dp[mask]` = best over subset `mask`, `dp[mask][i]` = best path visiting `mask` ending at `i` (TSP / Hamiltonian), or `dp[mask]` = ways to assign the next free person to an unused bit (assignment / Matching). Transitions flip one bit, or enumerate submasks in `O(3^n)`. Digit DP builds numbers left-to-right against an upper bound: state `(pos, tight, started, extra)` where `extra` is digit-sum / remainder / nonzero-count / last digit / used-digit mask; answer `[L,R]` as `f(R)-f(L-1)`. Spot bitmask when `n≤20` or “assign / visit / choose a subset of roles”; spot digit DP when the range is up to `10^18` (or a huge digit string) and the constraint is on digits.

## Ladder (easy -> hard, 25 problems)
- [ ] [Dreamoon and WiFi](https://codeforces.com/problemset/problem/476/B) — `Codeforces` `1300` — bitmask / ways over ± choices — Lightest CF entry: treat `+`/`-`/`?` as a mask of outcomes; bridges bit ops → counting DP. **(core)**
- [ ] [Given Length and Sum of Digits...](https://codeforces.com/problemset/problem/489/C) — `Codeforces` `1400` — digit construction — Build min/max n-digit numbers with digit-sum `s`; warms digit thinking before full digit DP.
- [ ] [Qualification Rounds](https://codeforces.com/problemset/problem/868/C) — `Codeforces` `1500` — subset masks of topics — Encode each problem’s topic set as a mask; check if two (or one) problems cover all — CF-style mask observation.
- [ ] [Get Everything](https://atcoder.jp/contests/abc142/tasks/abc142_e) — `AtCoder` `ABC E` — collect-all bitmask DP — Classic “buy chests / keys until mask is full”; `dp[mask]=min cost`. Strong AtCoder ABC drill.
- [ ] [Matching](https://atcoder.jp/contests/dp/tasks/dp_o) — `AtCoder` `Educational DP` — assignment / bipartite matching count — AtCoder DP Contest O / USACO Guide focus; `dp[S]` = ways to match `|S|` men to women in `S`. **(core)**
- [ ] [Elevator Rides](https://cses.fi/problemset/task/1653) — `CSES` `Dynamic Programming` — subset packing / min rides — CSES / CPH / USACO Guide; `dp[mask]=(rides, last_load)` — the subset-sum-over-masks template. **(core)**
- [ ] [Add One](https://codeforces.com/problemset/problem/1513/C) — `Codeforces` `1600` — digit evolution DP — Track how each digit 0–9 grows under “+1” ops for `m` steps; OA-flavored digit DP without a tight bound.
- [ ] [Carrying Conundrum](https://codeforces.com/problemset/problem/1567/C) — `Codeforces` `1600` — independent digit DP — Count `a+b=n` with no carry between odd/even positions; digit DP on interleaved places.
- [ ] [Counting Numbers](https://cses.fi/problemset/task/2220) — `CSES` `Dynamic Programming` — digit DP (adj ≠) — CSES / USACO-adjacent intro: count `[a,b]` with no equal adjacent digits; forces `tight` + `prev` + leading-zero. **(core)**
- [ ] [Digit Sum](https://atcoder.jp/contests/dp/tasks/dp_s) — `AtCoder` `Educational DP` — digit DP + mod sum — AtCoder DP Contest S; count `1..K` with digit-sum ≡ 0 (mod `D`), `K` up to 10^10000 digits. **(core)**
- [ ] [Almost Everywhere Zero](https://atcoder.jp/contests/abc154/tasks/abc154_e) — `AtCoder` `ABC E` — digit DP nonzero count — Count numbers ≤ `N` with exactly `K` non-zero digits; standard `(pos,tight,cnt)` state.
- [ ] [Nastya and Scoreboard](https://codeforces.com/problemset/problem/1340/B) — `Codeforces` `1700` — digit display + leftover sticks — Greedy+DP: for each position try largest digit affordable with remaining sticks; reconstruct lexicographically.
- [ ] [Kefa and Dishes](https://codeforces.com/problemset/problem/580/D) — `Codeforces` `1800` — TSP-style path on dishes — `dp[mask][last]` max satisfaction with pairwise bonuses; the CF gateway to Hamiltonian DP. **(core)**
- [ ] [Hamiltonian Flights](https://cses.fi/problemset/task/1690) — `CSES` `Graph Algorithms` — count Hamiltonian paths — CSES / USACO Guide bitmask focus; `dp[mask][v]` ways visiting `mask` ending at `v`. **(core)**
- [ ] [Fish](https://codeforces.com/problemset/problem/16/E) — `Codeforces` `1900` — probability over remaining set — `dp[mask]` = Prob subset `mask` still alive; transitions fight pairs inside the mask.
- [ ] [Classy Numbers](https://codeforces.com/problemset/problem/1036/C) — `Codeforces` `1900` — digit DP ≤3 nonzeros — CF classic / digit-DP blog staple; `f(R)-f(L-1)` with nonzero counter in state. **(core)**
- [ ] [Grouping](https://atcoder.jp/contests/dp/tasks/dp_u) — `AtCoder` `Educational DP` — submask enumeration `O(3^n)` — AtCoder DP Contest U / USACO Guide; max score partitioning into groups via submask DP. **(core)**
- [ ] [Looking for Order](https://codeforces.com/problemset/problem/8/C) — `Codeforces` `2000` — TSP pickup-return — Famous CF TSP: start at origin, collect items (1 or 2 per trip), `dp[mask]` min time. **(core)**
- [ ] [Roman and Numbers](https://codeforces.com/problemset/problem/401/D) — `Codeforces` `2000` — digit permutation + used-mask — Permute digits of `n`, count values ≡ 0 (mod `m`); mask of used positions + mod. Bridges bitmask ↔ digit DP. **(core)**
- [ ] [Little Pony and Harmony Chest](https://codeforces.com/problemset/problem/453/B) — `Codeforces` `2000` — primes-as-mask assignment — Map small primes to bits; assign each `a_i` a square-free partner with disjoint prime masks. **(stretch)**
- [ ] [Square Subsets](https://codeforces.com/problemset/problem/895/C) — `Codeforces` `2000` — subset product square via prime mask — Count subsets whose product is a square; XOR/add exponent-parity masks (mod 2). **(stretch)**
- [ ] [Counting Tilings](https://cses.fi/problemset/task/2181) — `CSES` `Dynamic Programming` — profile / broken-profile DP — CSES; fill a grid column-by-column with a vertical bitmask — advanced mask DP. **(stretch)**
- [ ] [Nearest Beautiful Number (hard version)](https://codeforces.com/problemset/problem/1560/F2) — `Codeforces` `2100` — construct next number with ≤k distinct digits — Digit-greedy / digit-DP construction under a distinct-digit budget. **(stretch)**
- [ ] [Magic Numbers](https://codeforces.com/problemset/problem/628/D) — `Codeforces` `2200` — digit DP with pattern + mod — USACO Guide digit-DP list; d-magic positions and divisible by `m`. **(stretch)**
- [ ] [Team Building](https://codeforces.com/problemset/problem/1316/E) — `Codeforces` `2300` — assign positions via mask — USACO Guide bitmask list; sort by audience value, `dp[i][mask]` fill `p≤7` roles. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- Iterate bits: `for (int i=0;i<n;i++) if (mask>>i&1)`; build `mask|(1<<i)`, `mask^(1<<i)`, popcount.
- Assignment template: `dp[0]=1`; for each `mask`, let `i=__builtin_popcount(mask)`, try unmatched `j` compatible with person `i`.
- TSP / Hamiltonian: `dp[1<<s][s]=1` (or 0 cost); transition `dp[mask][v] → dp[mask|(1<<u)][u]` over edges `v→u`.
- Elevator / subset packing: store `(min_rides, load_in_last_ride)` per mask; try adding each unused person into the last ride or a new ride.
- Submask enumeration in `O(3^n)`: `for (int sub=mask; sub; sub=(sub-1)&mask)`.
- Digit DP skeleton: `dfs(pos, tight, started, extra)` with memo; `limit = tight ? digits[pos] : 9`; answer `[L,R]` as `solve(R)-solve(L-1)`.
- Always handle leading zeros (`started` flag) so “previous digit” / “nonzero count” does not treat padding zeros as real digits.
- Know when `n≤20` ⇒ bitmask DP, when `R≤10^18` + digit property ⇒ digit DP — and when both combine (used-digit mask inside digit DP).

## Where it appears in OAs / interviews
- **Role / skill assignment:** “Assign `n` workers to `n` jobs with compatibility matrix; count ways / max score” → Matching / assignment bitmask (AtCoder O).
- **Capacity packing:** “Minimum trips / days / buses so every person’s weight fits under capacity `W`” → Elevator Rides subset DP.
- **Count in a numeric range:** “How many integers in `[L,R]` have digit-sum divisible by `k` / at most 3 non-zero digits / no two equal adjacent digits” → Digit DP (Classy Numbers / Counting Numbers / Digit Sum).
- **Visit-all path with bonuses:** “Order `n≤20` tasks; pairwise adjacency bonus if `i` immediately follows `j`” → Kefa-and-Dishes / TSP-style `dp[mask][last]`.
