# 04 — Prefix sums, 2D prefix sums & difference arrays

**Placement value:** High — static range sums, subarray-sum counting, and range updates are among the most common OA / interview array patterns; CF Div2 B–C reuse the same templates constantly.
**Prereq topics:** Arrays, basic hashing / maps, modular arithmetic (for divisibility variants)
**Pattern in one paragraph:** Precompute cumulative aggregates so any contiguous range becomes a constant-time difference of two prefixes (`sum(l..r) = pref[r] − pref[l−1]`). The inverse idea is the difference array: mark `+v` at `l` and `−v` at `r+1`, then one prefix rebuild applies many range updates. Extend both to 2D with inclusion–exclusion on rectangles, and to “count subarrays with property X” by hashing prefix values (or prefix mod m).

## Ladder (easy -> hard, ~18-28 problems)
- [ ] [Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/) — `LeetCode` `Easy` — 1D prefix template — **(core)** NeetCode / Striver base API for O(1) range sums
- [ ] [Static Range Sum Queries](https://cses.fi/problemset/task/1646) — `CSES` `Range Queries` — 1D prefix template — **(core)** CSES / USACO Guide warmup; same idea as LC 303 at contest scale
- [ ] [Odd Queries](https://codeforces.com/problemset/problem/1807/D) — `Codeforces` `900` — parity via prefix — **(core)** modern Div2 B; forces `long long` + many queries
- [ ] [Fence](https://codeforces.com/problemset/problem/363/B) — `Codeforces` `1100` — min fixed-length range sum — **(core)** classic “shortest fence” / sliding prefix; A2OJ-ladder staple
- [ ] [GeT AC](https://atcoder.jp/contests/abc122/tasks/abc122_c) — `AtCoder` `ABC122 C (300)` — prefix counts of pattern — **(core)** ABC classic; count `"AC"` occurrences in ranges
- [ ] [Kuriyama Mirai's Stones](https://codeforces.com/problemset/problem/433/B) — `Codeforces` `1200` — two prefixes (raw + sorted) — **(core)** keep both orderings’ prefixes; very common OA trick
- [ ] [Lecture Sleep](https://codeforces.com/problemset/problem/961/B) — `Codeforces` `1200` — prefix + one window boost — **(core)** awaken one segment of length `k`; USACO-Guide-adjacent pattern
- [ ] [Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/) — `LeetCode` `Medium` — prefix × suffix products — **(core)** NeetCode / Striver; interview staple (no division)
- [ ] [GCD on Blackboard](https://atcoder.jp/contests/abc125/tasks/abc125_c) — `AtCoder` `ABC125 C (300)` — prefix/suffix GCD — USACO Guide; replace one element → combine left/right aggregates
- [ ] [Water Heater](https://atcoder.jp/contests/abc183/tasks/abc183_d) — `AtCoder` `ABC183 D (400)` — difference array (timeline) — **(core)** ABC difference-array classic; capacity over intervals
- [ ] [Corporate Flight Bookings](https://leetcode.com/problems/corporate-flight-bookings/) — `LeetCode` `Medium` — difference array — **(core)** NeetCode difference template; OA-classic range increments
- [ ] [Karen and Coffee](https://codeforces.com/problemset/problem/816/B) — `Codeforces` `1400` — diff → coverage → second prefix — **(core)** USACO Guide; admissible temperatures + range queries
- [ ] [Greg and Array](https://codeforces.com/problemset/problem/295/A) — `Codeforces` `1400` — nested difference arrays — **(core)** USACO Guide; ops-on-ops then apply to array
- [ ] [Nastya and Door](https://codeforces.com/problemset/problem/1341/B) — `Codeforces` `1300` — prefix of peaks — count peaks in every window of length `k`
- [ ] [Little Girl and Maximum Sum](https://codeforces.com/problemset/problem/276/C) — `Codeforces` `1500` — diff frequency + greedy assign — **(core)** USACO Guide; how often each index is queried
- [ ] [Forest Queries](https://cses.fi/problemset/task/1652) — `CSES` `Range Queries` — 2D prefix sums — **(core)** CSES / USACO Guide; rectangle tree counts
- [ ] [Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/) — `LeetCode` `Medium` — 2D prefix inclusion–exclusion — **(core)** NeetCode / Striver OA classic
- [ ] [AtCoder Express 2](https://atcoder.jp/contests/abc106/tasks/abc106_d) — `AtCoder` `ABC106 D (400)` — 2D prefix on (L,R) plane — count trains fully inside `[p,q]`; famous ABC 2D-prefix drill
- [ ] [Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) — `LeetCode` `Medium` — prefix + hashmap — **(core)** NeetCode / Striver; *the* OA subarray-sum pattern
- [ ] [Subarray Sums II](https://cses.fi/problemset/task/1661) — `CSES` `Sorting and Searching` — prefix + hashmap — **(core)** CSES / USACO Guide; same idea as LC 560 at CP constraints
- [ ] [Subarray Divisibility](https://cses.fi/problemset/task/1662) — `CSES` `Sorting and Searching` — prefix mod n — **(core)** CSES / USACO Guide; same remainder ⇒ divisible subarray
- [ ] [Balanced Substring](https://codeforces.com/problemset/problem/873/B) — `Codeforces` `1500` — 0/1 → ±1 prefix map — longest balanced; same transform as LC Contiguous Array
- [ ] [Good Subarrays](https://codeforces.com/problemset/problem/1398/C) — `Codeforces` `1600` — rewritten prefix + count — **(core)** USACO Guide; `sum = length` → hash `pref − i`
- [ ] [Multiple of 2019](https://atcoder.jp/contests/abc164/tasks/abc164_d) — `AtCoder` `ABC164 D (400)` — suffix mod + count — USACO Guide; digit-string multiples via modular prefixes
- [ ] [Number of Ways](https://codeforces.com/problemset/problem/466/C) — `Codeforces` `1700` — prefix thirds + suffix counts — **(stretch)** classic CF; partition into three equal sums
- [ ] [Constant Palindrome Sum](https://codeforces.com/problemset/problem/1343/D) — `Codeforces` `1700` — difference over pair-sum candidates — **(stretch)** CF Div2 D; optimize replacements with a diff sweep

## Must-internalize checklist (5-10 bullets)
- Build 1D `pref[0]=0`, `pref[i]=pref[i−1]+a[i]`; answer `sum(l..r)=pref[r]−pref[l−1]` (1-indexed or 0-indexed consistently).
- Difference array: `diff[l]+=v`, `diff[r+1]−=v`; final array = prefix of `diff` (always `long long` on CF).
- 2D build: `P[i][j]=a[i][j]+P[i−1][j]+P[i][j−1]−P[i−1][j−1]`; query rectangle with +/−/+ inclusion–exclusion.
- Subarray sum = K: map of prefix frequencies; init `{0:1}`; query `pref−K` before inserting `pref`.
- Subarray divisible by m: hash `pref % m` (normalize negatives); same remainder ⇒ divisible block.
- Prefix/suffix aggregates beyond sum: products, GCD, XOR, counts of a pattern (`"AC"`, awake minutes, peaks).
- When many range updates then one read → difference; when many range queries on static data → prefix; interleaved updates → Fenwick/segment tree (next topic).
- Off-by-one discipline: inclusive bounds, `r+1` clamp, empty-prefix sentinel, and overflow.

## Where it appears in OAs / interviews
- “Immutable array, many range-sum queries” → LC 303 / CSES Static Range Sum (NumArray design questions).
- “Add seats / bookings / passengers on `[l,r]` then report the array” → LC 1109 / Car Pooling-style difference arrays.
- “Count subarrays with sum K / sum divisible by K” → LC 560 / CSES Subarray Sums II & Divisibility (Amazon/Google-style mediums).
- “Sum of any submatrix / block of a grid” → LC 304 / CSES Forest Queries (matrix / image integral questions).
