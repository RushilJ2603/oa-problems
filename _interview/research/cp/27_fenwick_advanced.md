# 27 — Fenwick / BIT advanced: 2D, order-statistics, inversions, range-update

**Placement value:** High — inversion counting, “how many ≤ x”, and k-th in a dynamic multiset show up constantly in OAs; range-add / 2D rectangle sum are the CF Div2 C–D upgrade past plain prefix sums.
**Prereq topics:** Prefix sums & difference arrays (04), binary search, coordinate compression / sorting, basic Fenwick PURS (topic 20) or equivalent
**Pattern in one paragraph:** Fenwick stores frequencies or values so prefix sums answer “how many / how much before index i” in \(O(\log n)\). **Inversions / smaller-to-the-right:** compress values, scan L→R or R→L, query prefix then `add(rank,1)`. **Order statistics:** BIT as frequency table; find k-th by binary lifting on prefix sums (`find_kth`). **Range update:** store a difference array in the BIT — `add(l,+v)`, `add(r+1,−v)`, point value = prefix; for range-add + range-sum use **two BITs**. **2D:** nest the `i+=i&-i` loops; rectangle = inclusion–exclusion of four corners. Signal words: count pairs with order constraint, k-th remaining element, many range increments, trees in a subrectangle with toggles, nested segments.

## Ladder (easy -> hard, ~18-28 problems)
- [ ] [Fenwick Tree](https://atcoder.jp/contests/practice2/tasks/practice2_b) — `AtCoder` `ACL Practice B` — PURS template — **(core)** ACL / Library Checker point-add range-sum; write the 1-indexed `add`/`sum` once
- [ ] [Dynamic Range Sum Queries](https://cses.fi/problemset/task/1648) — `CSES` `Range Queries` — PURS — **(core)** CSES / USACO Guide Gold; same template under contest constraints
- [ ] [Number of Inversions](https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_ef) — `AtCoder` `Tessoku B59` — inversion BIT — **(core)** compress + scan; first inversion muscle memory
- [ ] [Greg and Array](https://codeforces.com/problemset/problem/295/A) — `Codeforces` `1400` — nested difference — **(core)** range-add of range-adds; difference mindset before BIT-as-diff
- [ ] [Maximum Crossings (Hard Version)](https://codeforces.com/problemset/problem/1676/H2) — `Codeforces` `1500` — inversions — **(core)** modern Div2; crossings ≡ inversions on a sequence
- [ ] [Bubble Sort Graph](https://codeforces.com/problemset/problem/340/D) — `Codeforces` `1500` — LIS via BIT — **(core)** maintain best length for ranks ≤ value
- [ ] [Range Update Queries](https://cses.fi/problemset/task/1651) — `CSES` `Range Queries` — range add + point query — **(core)** BIT-as-difference; USACO Guide adjacent
- [ ] [Forest Queries](https://cses.fi/problemset/task/1652) — `CSES` `Range Queries` — static 2D sum — **(core)** four-corner identity before 2D BIT
- [ ] [Counting Points](https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_cg) — `AtCoder` `Tessoku B08` — 2D prefix counts — **(core)** compress grid then prefix / BIT habit
- [ ] [List Removals](https://cses.fi/problemset/task/1749) — `CSES` `Range Queries` — order-statistic BIT — **(core)** alive markers + find k-th then delete
- [ ] [Salary Queries](https://cses.fi/problemset/task/1144) — `CSES` `Range Queries` — compress + freq BIT — **(core)** dynamic “how many in [a,b]” after point changes
- [ ] [Nested Ranges Count](https://cses.fi/problemset/task/2169) — `CSES` `Sorting and Searching` — sort + Fenwick — **(core)** CSES / USACO Guide; containment counts
- [ ] [Flowers](https://atcoder.jp/contests/dp/tasks/dp_q) — `AtCoder` `DP contest Q` — BIT for LIS-style DP — **(core)** AtCoder DP contest; max beauty with increasing height
- [ ] [Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) — `LeetCode` `Hard` — Fenwick inversions — **(core)** NeetCode / OA classic; *the* interview “smaller to the right”
- [ ] [Increasing Subsequence II](https://cses.fi/problemset/task/1748) — `CSES` `Dynamic Programming` — count IS via BIT — **(core)** compress; `dp[v]=1+sum(<v)` then add
- [ ] [Forest Queries II](https://cses.fi/problemset/task/1739) — `CSES` `Range Queries` — 2D BIT — **(core)** cp-algorithms / CSES; point toggle + rectangle sum \(O(\log^2 n)\)
- [ ] [Gravel](https://www.codechef.com/problems/SPREAD) — `CodeChef` `SPREAD` — range-add + range-sum — **(core)** cp-algorithms classic; **two BITs** RURQ formula
- [ ] [Nested Segments](https://codeforces.com/problemset/problem/652/D) — `Codeforces` `1800` — Fenwick containment — **(stretch)** USACO Guide; sort endpoints, count insides
- [ ] [Pashmak and Parmida's problem](https://codeforces.com/problemset/problem/459/D) — `Codeforces` `1800` — Fenwick on frequencies — **(stretch)** classic `f(prefix)` vs `f(suffix)` count
- [ ] [Multiset](https://codeforces.com/problemset/problem/1354/D) — `Codeforces` `1900` — BIT find-k-th — **(stretch)** *the* CF order-statistic tutorial problem (\(n,q\le10^6\))
- [ ] [Enemy is weak](https://codeforces.com/problemset/problem/61/E) — `Codeforces` `1900` — 3-way inversions — **(stretch)** two Fenwicks / left-greater × right-smaller
- [ ] [Subsequences](https://codeforces.com/problemset/problem/597/C) — `Codeforces` `1900` — k BITs for length — **(stretch)** count increasing subsequences of length \(k+1\)
- [ ] [Tufurama](https://codeforces.com/problemset/problem/961/E) — `Codeforces` `1900` — offline BIT pairs — **(stretch)** count \((i,j)\) with value/index constraints
- [ ] [Pyramid Array](https://cses.fi/problemset/task/1747) — `CSES` `Additional` — inversions / placement cost — **(stretch)** USACO Guide Hard; adjacent swaps to unimodal
- [ ] [Intersection Points](https://cses.fi/problemset/task/1740) — `CSES` `Geometry` — sweep + BIT — **(stretch)** H/V segments; event sort + active y-coords in BIT
- [ ] [Little Artem and Time Machine](https://codeforces.com/problemset/problem/641/E) — `Codeforces` `2000` — offline BIT by time — **(stretch)** cp-algorithms list; group by value, BIT on time
- [ ] [Infinite Inversions](https://codeforces.com/problemset/problem/540/E) — `Codeforces` `2100` — compress + inversions — **(stretch)** Candidate Master milestone; sparse permutation after swaps

## Must-internalize checklist (5-10 bullets)
- 1-indexed BIT: `add(i,δ)` via `i += i&-i`; `sum(i)` via `i -= i&-i`; range = `sum(r)-sum(l-1)`; always `long long` on CF.
- Coordinate compression before any value-as-index BIT when \(a_i\le10^9\); offline-collect all values (array + query endpoints).
- Inversions / smaller-to-the-right: scan with a frequency BIT; query how many already seen are `<` (or `>`) current rank, then update.
- Order statistic: BIT stores counts; find k-th with binary lifting — walk bits of `pos` while `bit[pos+bit] < k` (List Removals / Multiset).
- Range update + point query: difference in BIT — `add(l,v)`, `add(r+1,-v)`; point = `sum(i)`.
- Range update + range query: two BITs \(B_1,B_2\); `prefix(i)=i·sum(B_1,i)-sum(B_2,i)` (SPREAD / cp-algorithms).
- 2D BIT: nest both loops; `rect(x1,y1,x2,y2)=S(x2,y2)-S(x1-1,y2)-S(x2,y1-1)+S(x1-1,y1-1)`.
- BIT-for-DP: when transition is `max/sum over ranks < v`, replace the loop with a Fenwick (Flowers, Increasing Subsequence II, Bubble Sort Graph).

## Where it appears in OAs / interviews
- “For each index, count how many smaller elements appear to its right” → LC 315 / Tessoku inversions (Amazon/Meta-style Hard).
- “Support add value, delete k-th, or count elements in [L,R] under updates” → Multiset / Salary Queries / List Removals (order-statistic DS API).
- “NumMatrix: update cell, query subrectangle sum” → 2D BIT (CSES Forest Queries II shape; interview API often mirrors LC 308).
- “Many range increments, then read the array / range sums” → Greg and Array / CSES Range Update / two-BIT RURQ (difference-array interviews that scale to \(n,q\sim10^5\)).
