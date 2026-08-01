# 04 — Prefix sums & difference arrays (depth)

**Placement value:** High — once the template ladder is done, OA/Div2 C–D still hide prefix rewrites (median gather, ratio counts, BS+diff, 2D imos); this list is the post-famous band through CM.
**Prereq topics:** 1D/2D prefix + difference arrays (base ladder), hashing/maps, binary search on answer, basic greedy/heaps
**Pattern in one paragraph:** Same engines as the base topic — range aggregates via prefixes, range updates via difference/imos — but statements force a rewrite first: gather cost → median + prefix counts; “good cuts” → prefix of runs; coverage histograms → compressed sweep; median/subarray tricks → map values to ±1 and track prefix minima; 2D paint/paths → inclusion–exclusion or cascade diffs. Recognize it when many static range questions, many offline range adds, or “count subarrays with property expressible from `pref[r]−pref[l−1]`” appear under contest packing.

## Technique notes (non-obvious)
- Compressed sweep (e.g. Covered Points): emit `+1` at `l` and `−1` at `r+1` on a sorted coordinate list; between consecutive events the coverage is constant — multiply length by coverage, never loop the axis.
- Contribution / constructive diff (Sum on Subarrays): to force subarray-sum scores, mark the *derivative* of the desired contribution array, then prefix once — you build the array that induces the scores, not the scores themselves.
- BS + difference (Tracking Segments): binary-search the first moment a segment becomes “full”; for a mid, apply the first `mid` point updates on a diff array and prefix-check each segment’s coverage.
- ±1 prefix for order statistics (Median on Segments / Max Median): replace “≥x” by `+1` else `−1`; a subarray median ≥x iff some prefix difference is positive (or a prefix minimum stays controlled). Init map/min carefully at index 0.
- Pref/suf of `b[i]+i` and `b[i]−i` (Running Miles): a length-3 score `b[i]+b[j]+b[k]-(k−i)` splits into independent left/right maxima — classic “prefix of transformed values”.
- 2D cascade diff (Matrix Cascade): a diagonal/triangle update is still O(1) marks on a 2D difference (or two 1D diffs on diagonals), then one prefix rebuild — same imos idea as ABC timeline compression.
- Zero-Sum Prefixes: between editable zeros the running prefix is fixed; greedily set the next zero so the most frequent prefix in the segment becomes 0 (freq map of prefixes).
- Nested prefixes (Sums of Segments): answers are prefixes of the prefix-sum array (sum of all subarray sums ending in a range) — precompute `pref`, `prefpref`, and sometimes `i·pref[i]` closed forms.

## Ladder (easy -> hard, ~18-28 problems)
- [ ] [Arranging The Sheep](https://codeforces.com/problemset/problem/1520/E) — `Codeforces` `1400` — prefix counts + median — **(core)** gather `*` to a median; cost = Σ|pos−med| via left/right prefix counts
- [ ] [Robert Hood and Mrs Hood](https://codeforces.com/problemset/problem/2014/D) — `Codeforces` `1400` — prefix of points + window — **(core)** place a fixed-length segment to maximize covered houses
- [ ] [Range XOR Queries](https://cses.fi/problemset/task/1650) — `CSES` `Range Queries` — prefix XOR — **(core)** same API as range sum; `xor(l..r)=pref[r]⊕pref[l−1]`
- [ ] [Online games](https://atcoder.jp/contests/abc221/tasks/abc221_d) — `AtCoder` `ABC221 D (400)` — imos / difference on days — **(core)** login intervals → how many players online for exactly `k` days
- [ ] [Polycarp Restores Permutation](https://codeforces.com/problemset/problem/1141/C) — `Codeforces` `1500` — prefix of adjacent diffs — reconstruct permutation from `p_{i+1}−p_i`; shift to `[1..n]`
- [ ] [Alternating String](https://codeforces.com/problemset/problem/2008/E) — `Codeforces` `1500` — parity prefix letter counts — **(core)** USACO Guide; min changes so odd/even positions are uniform
- [ ] [Diluc and Kaeya](https://codeforces.com/problemset/problem/1536/C) — `Codeforces` `1500` — prefix ratio map — **(core)** count prefixes with same `D:K` reduced ratio (hash pair / gcd)
- [ ] [Sum on Subarrays](https://codeforces.com/problemset/problem/1809/C) — `Codeforces` `1500` — constructive difference — build an array realizing a target “number of positive subarray sums”
- [ ] [Masha and two friends](https://codeforces.com/problemset/problem/1080/C) — `Codeforces` `1500` — 2D rectangle paint — inclusion–exclusion on black/white counts after two rectangle recolors
- [ ] [Alyona and Spreadsheet](https://codeforces.com/problemset/problem/777/C) — `Codeforces` `1600` — prefix of sorted runs — **(core)** precompute farthest row each column stays non-decreasing; answer rectangle queries
- [ ] [Counting Rectangles](https://codeforces.com/problemset/problem/1722/E) — `Codeforces` `1600` — 2D prefix on values — **(core)** freq grid of `(h,w)` + rectangle sum queries for area counts
- [ ] [Zero-Sum Prefixes](https://codeforces.com/problemset/problem/1748/C) — `Codeforces` `1600` — prefix freq between zeros — **(core)** maximize zero prefixes by rewriting `0` entries
- [ ] [Least Prefix Sum](https://codeforces.com/problemset/problem/1779/C) — `Codeforces` `1600` — greedy on prefixes — **(core)** min flips so prefix `m` is a global minimum prefix
- [ ] [Tracking Segments](https://codeforces.com/problemset/problem/1843/E) — `Codeforces` `1600` — binary search + difference — **(core)** first time some segment is majority-ones after point updates
- [ ] [Snuke Prime](https://atcoder.jp/contests/abc188/tasks/abc188_d) — `AtCoder` `ABC188 D (400)` — compressed imos — timeline difference with coordinate compression + cost × length
- [ ] [Covered Points Count](https://codeforces.com/problemset/problem/1000/C) — `Codeforces` `1700` — sweep difference + compression — **(core)** for each coverage `k`, count integer points covered exactly `k` times
- [ ] [Painting the Fence](https://codeforces.com/problemset/problem/1132/C) — `Codeforces` `1700` — prefix of painter coverage — **(core)** omit two painters; maximize still-painted planks via coverage prefixes
- [ ] [Program](https://codeforces.com/problemset/problem/1473/D) — `Codeforces` `1700` — prefix/suffix min·max — delete a substring of `+/−` program; track reachable balance extrema
- [ ] [Running Miles](https://codeforces.com/problemset/problem/1826/D) — `Codeforces` `1700` — pref/suf of `b[i]±i` — **(core)** USACO Guide; maximize `b[i]+b[j]+b[k]-(k−i)` over `i<j<k`
- [ ] [Matrix Cascade](https://codeforces.com/problemset/problem/1864/D) — `Codeforces` `1700` — 2D difference cascade — **(stretch)** clear `1`s with diagonal updates via imos marks
- [ ] [Nuske vs Phantom Thnook](https://atcoder.jp/contests/agc015/tasks/agc015_c) — `AtCoder` `AGC015 C` — 2D prefix on grid trees — **(stretch)** rectangle path-connectivity counts from prefix of black cells / components
- [ ] [Queries for Number of Palindromes](https://codeforces.com/problemset/problem/245/H) — `Codeforces` `1800` — 2D prefix on palindrome DP — **(stretch)** `isPal[l][r]` then prefix-count substrings that are palindromes
- [ ] [Median on Segments (Permutations Edition)](https://codeforces.com/problemset/problem/1005/E1) — `Codeforces` `1800` — ±1 prefix around median — **(stretch)** count subarrays whose median is `m`
- [ ] [Sums of Segments](https://codeforces.com/problemset/problem/2026/D) — `Codeforces` `1900` — prefix of prefix sums — **(stretch)** USACO Guide hard; answer sums of all subarray sums over index ranges
- [ ] [Max Median](https://codeforces.com/problemset/problem/1486/D) — `Codeforces` `2100` — BS + ±1 prefix minima — **(stretch)** maximize median of a subarray of length ≥`k`

## Must-internalize checklist (5-10 bullets)
- Rewrite to a prefix invariant before coding: median gather, ratio `a:b`, coverage counts, “median ≥ x”, or sum-of-subarray-sums.
- Compressed difference/imos: sort events `(pos,+v)/(pos+1,−v)`; multiply gap length by current coverage.
- Binary search on “time / length / threshold” + one difference rebuild to validate — standard CF C/D combo.
- Maintain both prefix and suffix aggregates (`min/max`, `b[i]+i`, `b[i]−i`) when the optimum splits into left + pivot + right.
- 2D: rectangle paint counts, value-grid rectangle sums, and cascade/diagonal updates are still inclusion–exclusion or 2D imos — not a segment tree.
- ±1 / XOR / mod transforms: map the property into an additive group so `pref[r]−pref[l−1]` (or ⊕) becomes the check; hash frequencies carefully with a `0` sentinel.
- Always `long long` on CF; clamp `r+1`; for compression include `r+1` as a coordinate so open/close events stay correct.

## Where it appears in OAs / interviews
- “Minimum cost to make all special indices meet” → Arranging The Sheep / median + prefix (Amazon/Google OA flavor).
- “After many timestamped login/logout events, report histograms” → ABC221 D / Covered Points (imos + compression).
- “First query index when every watched segment is satisfied” → Tracking Segments (BS + diff) — classic CF packaging of difference arrays.
- “Maximize median of a long enough window” → Max Median (BS-on-answer + ±1 prefixes) — interview-adjacent binary-search-on-answer with a prefix check.
