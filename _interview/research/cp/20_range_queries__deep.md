# 20 — Range queries: Fenwick, segtree, sparse table (Depth Pass)

**Placement value:** High (second ladder after CSES/EDU templates — CF Div2 C–E “rewrite the ask into a merge / walk / offline count,” GCD-sparse tricks, and custom node structs that still appear as hard OA twists)
**Prereq topics:** Finished the standard range-query ladder (prefix, sparse RMQ, Fenwick PURS, basic segtree, Hotel/List Removals-style walks); coordinate compression; light DP / sorting
**Pattern in one paragraph:** After Dynamic Range Sum / Hotel Queries / Sereja-and-Brackets-classics, contest range DS stops being “paste the template.” You invent what each node stores (max subarray, top-2, GCD+count), run Fenwick offline over sorted endpoints, or pair a sparse table with two pointers / binary lifting on idempotent ops. Recognize it when many `[l,r]` asks survive only if you pre-merge associative info, when updates are rare-but-heavy (digit-sum, \(D(n)\)), or when the answer is a count of pairs/subsequences that a frequency BIT can accumulate while sweeping.

**Non-obvious tricks (internalize):**
1. Coverage → rearrange: range “+1 usefulness” via difference array, then greedily assign largest values to most-queried indices (Little Girl and Maximum Sum).
2. GCD segtree prune: if `node_gcd % x == 0` skip; else recurse — with at most one “bad” child you get near-\(O(\log n)\) replace/check (Bash and a Tough Math Puzzle).
3. Offline last-occurrence: sort queries by `r`, walk `i=1..n`, `add(prev[a_i],-1)`, `add(i,+1)`, answer distinct on `[l,r]` as `sum(r)-sum(l-1)` (Distinct Values Queries).
4. Dual affine trees: pizza cost `|x-i|+a_i` = query `min(a_i-i)+x` left of `x` and `min(a_i+i)-x` right — two point-update range-min segtrees (Pizzeria Queries).
5. Layered BIT DP: `dp[k][i] = sum dp[k-1][j]` over `a_j < a_i` via Fenwick on value; \(k\) trees or one reused layer (Subsequences).
6. Sparse + monotonic pointers: for each `L`, grow `R` while `gcd(L..R)` (or `max-min`) still satisfies a predicate — each endpoint moves \(O(n)\) total (Array Stabilization / Friends and Subsequences).
7. “Replace until stable” segtree: store range max; if `max ≤ 2` (or digit-sum fixed point) skip; else point-update children — total updates \(O(n\log A)\) (SUM and REPLACE / Range Update Point Query).
8. Custom merge beyond sum/min: node = `(total, pref, suf, best)` for max subarray, or `(mx, mx_cnt, second, second_cnt)` for second-largest frequency — merge is pure casework on the two children.

## Ladder (easy -> hard, 25 problems)
- [ ] [Rooks Defenders](https://codeforces.com/problemset/problem/1679/C) — `Codeforces` `1400` — BIT on row/col occupancy — **(core)** two Fenwicks: empty row/col counts; “rectangle free?” = no occupied rows and cols in ranges.
- [ ] [Little Girl and Maximum Sum](https://codeforces.com/problemset/problem/276/C) — `Codeforces` `1500` — diff coverage + sort — **(core)** build how often each index is queried, assign largest \(a_i\) to hottest indices.
- [ ] [Bubble Sort Graph](https://codeforces.com/problemset/problem/340/D) — `Codeforces` `1500` — LIS via Fenwick — **(core)** permutation LIS length with BIT max-on-prefix; bridge from “inversions” to “optimize DP with RQ.”
- [ ] [Range Update Point Query](https://codeforces.com/problemset/problem/1791/F) — `Codeforces` `1500` — digit-sum range ops — **(core)** values stabilize ≤9; maintain “still large” indices in a set / segtree and skip fixed points.
- [ ] [Subarray Sum Queries](https://cses.fi/problemset/task/1190) — `CSES` `Range Queries` — max-subarray merge node — **(core)** GSS1-style `(sum, pref, suf, best)`; empty subarray allowed ⇒ `best≥0`.
- [ ] [Distinct Values Queries](https://cses.fi/problemset/task/1734) — `CSES` `Range Queries` — offline last-occurrence Fenwick — **(core)** the standard Mo-alternative; high transfer to “count unique on `[l,r]`.”
- [ ] [F - Jealous Two](https://atcoder.jp/contests/abc231/tasks/abc231_f) — `AtCoder` `ABC231 F (~1600)` — compress + Fenwick pairs — **(core)** count pairs with \(A_i\le A_j\) and \(B_i\ge B_j\); classic 2D dominance via sort + BIT.
- [ ] [Program](https://codeforces.com/problemset/problem/1473/D) — `Codeforces` `1700` — sparse min/max on prefixes — **(core)** ±1 program; delete a segment ⇒ stitch prefix before + shifted suffix using range min/max of balances.
- [ ] [Pizzeria Queries](https://cses.fi/problemset/task/2206) — `CSES` `Range Queries` — two segtrees \(a_i\pm i\) — **(core)** distance-in-cost rewritten as independent left/right range mins.
- [ ] [Petya and Array](https://codeforces.com/problemset/problem/1042/D) — `Codeforces` `1800` — Fenwick on prefix sums — **(core)** count pairs with \(pref_r-pref_{l-1}<t\); compress prefixes, BIT while sweeping.
- [ ] [Max GEQ Sum](https://codeforces.com/problemset/problem/1691/D) — `Codeforces` `1800` — sparse max + next-greater — **(core)** for each peak, maximal segment where it stays maximum; check sum ≤ value via prefix.
- [ ] [F - Box in Box](https://atcoder.jp/contests/abc309/tasks/abc309_f) — `AtCoder` `ABC309 F (~1800)` — sort + Fenwick min — **(core)** nest boxes after normalizing sides; 2D partial order “exists smaller pair” via BIT.
- [ ] [Subsequences](https://codeforces.com/problemset/problem/597/C) — `Codeforces` `1900` — \(k\)-layer Fenwick DP — **(core)** count length-\((k+1)\) increasing subsequences; *the* BIT-accelerated DP drill.
- [ ] [Tufurama](https://codeforces.com/problemset/problem/961/E) — `Codeforces` `1900` — offline Fenwick on capped values — **(core)** count pairs \(i<j\le a_i,\ i\le a_j\); sort by one constraint, BIT the other.
- [ ] [Bash and a Tough Math Puzzle](https://codeforces.com/problemset/problem/914/D) — `Codeforces` `1900` — GCD segtree with prune — **(core)** replace/check divisibility without touching whole range; must-know early-exit pattern.
- [ ] [Restore Permutation](https://codeforces.com/problemset/problem/1208/D) — `Codeforces` `1900` — Fenwick find-by-prefix-sum — **(core)** from right, locate value = \(1+\)(# remaining smaller); binary-lift on BIT.
- [ ] [Array Stabilization (GCD version)](https://codeforces.com/problemset/problem/1547/F) — `Codeforces` `1900` — sparse GCD + two pointers — circular GCD-stable; minimal \(k\) so every window GCD equals global.
- [ ] [Copying Data](https://codeforces.com/problemset/problem/292/E) — `Codeforces` `1900` — lazy assign of copy-maps — **(stretch)** range overwrite “from \(a[x..]\) into \(b[y..]\)”; store source offset tag, push on read.
- [ ] [Forest Queries II](https://cses.fi/problemset/task/1739) — `CSES` `Range Queries` — 2D Fenwick point flip — **(stretch)** toggle forest cells + rectangle sum; the 2D PURS template past 1D.
- [ ] [SUM and REPLACE](https://codeforces.com/problemset/problem/920/F) — `Codeforces` `2000` — \(D(n)\) until small + segtree — **(stretch)** range replace by divisor-count; skip segments with `max≤2`.
- [ ] [New Year Concert](https://codeforces.com/problemset/problem/1632/D) — `Codeforces` `2000` — sparse GCD + greedy cuts — **(stretch)** maintain rightmost start of current GCD chain; cut when GCD hits segment length.
- [ ] [Pillars](https://codeforces.com/problemset/problem/474/E) — `Codeforces` `2000` — segtree max DP on compressed heights — **(stretch)** longest path with height gap \(>d\); query max over allowed height ranges.
- [ ] [F - Second Largest Query](https://atcoder.jp/contests/abc343/tasks/abc343_f) — `AtCoder` `ABC343 F (~2000)` — top-2 merge node — **(stretch)** store largest & second-largest with freqs; modern custom-merge drill past brackets.
- [ ] [Mishka and Interesting sum](https://codeforces.com/problemset/problem/703/D) — `Codeforces` `2100` — Fenwick XOR of distinct — **(stretch)** offline by `r`; XOR of values with odd count on `[l,r]` via last-occurrence XOR updates.
- [ ] [Friends and Subsequences](https://codeforces.com/problemset/problem/689/D) — `Codeforces` `2100` — dual sparse max/min — **(stretch)** CM ceiling; for each `L`, binary-search largest/smallest `R` with `max=min` using \(O(1)\) RMQ.

## Must-internalize checklist (5-10 bullets)
- Offline > online when queries commute: sort by `r` (or by value), Fenwick the sweeping side, answer in input order via ids.
- Idempotent static ops (min/max/GCD) → sparse table; then two-pointer / BS on endpoints is \(O(n\log)\) or \(O(n)\), not \(O(n^2)\).
- Walk/binary-lift on Fenwick prefix sums restores permutations and finds k-th remaining (Restore Permutation / Multiset family).
- Node design checklist: which fields are enough to merge? (sum+pref+suf+best; gcd; top-2; OR of bits; min with index).
- Early-exit / “stable range” updates: if the aggregate already implies no change, do not push into children — complexity comes from potential, not from \(q\log n\) worst-case alone.
- 2D / dominance: sort one axis, Fenwick the other (Jealous Two, Box in Box, Tufurama).
- Affine distance tricks: fold \(\pm i\) into the stored value so a plain range-min answers “best index near \(x\).”
- Always compress before BIT when values/\(pref\) hit \(10^9\); keep `long long` for sums and XOR-of-sums mixes.

## Where it appears in OAs / interviews
- **Coverage scheduling:** “each query marks a range; assign priorities/values to maximize sum” — Little Girl / difference-array frequency family.
- **Unique / distinct in window:** “how many distinct SKUs in `[l,r]` after stream of updates” — Distinct Values / last-occurrence Fenwick (log-store analytics).
- **Custom aggregate API:** “maintain max subarray sum after point edits” or “count of second-max in a segment” — Subarray Sum Queries / Second Largest Query (NumArray upgrades).
- **Pair/subsequence counting under order constraints:** “count increasing length-k / dominance pairs” — Subsequences / Jealous Two (classic hard OA DS+DP).
