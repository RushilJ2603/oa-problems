# 37 — Sum over Subsets (SOS) DP & Submask Enumeration

**Placement value:** Medium — rarely the first OA template, but “count / aggregate over all bit-subsets of a mask” and “partition a small set via submasks” show up in harder bit-mask screens; essential CF ~1700–2200 toolkit Striver never covers
**Prereq topics:** Bit manipulation (set/unset/`__builtin_popcount`, AND/OR/XOR), basic bitmask DP (`dp[mask]`), intro DP / memoization; comfort with `n ≤ 20` / `values ≤ 2^20` constraints

**Pattern in one paragraph:** Two closely related tools. **Submask enumeration:** for a fixed mask `m`, walk every `s ⊆ m` via `for (int s=m; s; s=(s-1)&m)` (handle `0` separately); over *all* masks this is `O(3^n)`, not `O(4^n)`, and is the standard transition for “split set `mask` into group `sub` + rest” / clique-partition / reconstruct-from-parts DP. **SOS DP:** given `A[0…2^n)`, compute `F[mask] = Σ_{i ⊆ mask} A[i]` (or sum over *supersets*) in `O(n·2^n)` by sweeping one bit at a time — an `n`-dimensional prefix sum on the subset lattice. Spot it when you need, for every mask, a sum/count/max over all its submasks (or complements/supersets), and `n ≤ 20`–`23` makes `n·2^n` fit but `3^n`/`4^n` does not — or when the statement asks “compatible AND = 0”, “OR-subsets”, “count y with x|y=x / x&y=x”.

## Ladder (easy -> hard, 24 problems)
- [ ] [Submask](https://atcoder.jp/contests/abc269/tasks/abc269_c) — `AtCoder` `ABC C` — literal submask enum — Print every submask of `N` (`popcount ≤ 15`); forces the `(s-1)&m` loop into muscle memory. **(core)**
- [ ] [Preparing Olympiad](https://codeforces.com/problemset/problem/550/B) — `Codeforces` `1400` — enumerate all `2^n` subsets — `n ≤ 15`, filter by count/sum/diff; warmup before caring *which* subsets are submasks of a given mask. **(core)**
- [ ] [Johnny and Another Rating Drop](https://codeforces.com/problemset/problem/1362/C) — `Codeforces` `1400` — bit contribution — Count bit flips along `1…n`; trains “answer = Σ over bits” before SOS aggregations.
- [ ] [Qualification Rounds](https://codeforces.com/problemset/problem/868/C) — `Codeforces` `1500` — topic masks / pairwise cover — Encode each problem’s topics as a mask; check two (or one) masks whose OR is full — CF-style mask observation. **(core)**
- [ ] [Orray](https://codeforces.com/problemset/problem/1742/G) — `Codeforces` `1500` — greedy OR construction — Build permutation maximizing prefix OR; bit-greedy that pairs well with later SOS “best under mask” thinking.
- [ ] [Get Everything](https://atcoder.jp/contests/abc142/tasks/abc142_e) — `AtCoder` `ABC E` — collect-keys bitmask DP — `dp[mask]` min cost to own key-set `mask`; solid bridge from Striver-style assignment masks → contest masks.
- [ ] [Cobb](https://codeforces.com/problemset/problem/1554/B) — `Codeforces` `1700` — submask enum for max score — Maximize `i·j − k·(a_i|a_j)`; for each index, try useful OR-submasks — *the* mid-rated “why enumerate submasks?” drill. **(core)**
- [ ] [Sum of XOR Functions](https://codeforces.com/problemset/problem/1879/D) — `Codeforces` `1700` — XOR contribution / bits — Sum `f(l,r)·(r−l+1)` with `f = XOR` of subarray; bit-by-bit closed form before full SOS.
- [ ] [Apollo versus Pan](https://codeforces.com/problemset/problem/1466/E) — `Codeforces` `1800` — AND/OR bit contribution — Expand `Σ (a_i & a_j) · (a_i | a_k)` over bits; OA-flavored bit math adjacent to SOS aggregates.
- [ ] [Grouping](https://atcoder.jp/contests/dp/tasks/dp_u) — `AtCoder` `Educational DP` — `O(3^n)` partition DP — Max score partitioning `n ≤ 16` people into groups; `dp[mask] = max over sub ⊆ mask of score(sub)+dp[mask\sub]`. **(core)**
- [ ] [Close Group](https://atcoder.jp/contests/abc187/tasks/abc187_f) — `AtCoder` `ABC F` — clique components via submasks — Min connected components after deletions so every component is a clique; mark valid clique masks, then `O(3^n)` cover DP. **(core)**
- [ ] [SOS Bit Problem](https://cses.fi/problemset/task/1654) — `CSES` `Bitwise Operations` — subset + superset SOS — For each `x`: counts with `x|y=x`, `x&y=x`, `x&y≠0`; USACO Guide / CSES *the* SOS starter. **(core)**
- [ ] [Or Plus Max](https://atcoder.jp/contests/arc100/tasks/arc100_c) — `AtCoder` `ARC E` — SOS keeping top-2 — For every `K`, max `A_i+A_j` with `(i∨j)≤K`; SOS propagates the two largest values under each mask. **(core)**
- [ ] [Minimax Problem](https://codeforces.com/problemset/problem/1288/D) — `Codeforces` `2000` — binary search + mask of “≥ mid” bits — BS answer; each array → mask of coordinates ≥ mid; check two masks covering all bits. **(core)**
- [ ] [Square Subsets](https://codeforces.com/problemset/problem/895/C) — `Codeforces` `2000` — prime-exponent parity mask — Count subsets with square product; compress small primes to a mask, then subset DP / linear algebra over GF(2).
- [ ] [Compatible Numbers](https://codeforces.com/problemset/problem/165/E) — `Codeforces` `2200` — SOS “exists submask of complement” — For each `a_i`, find any `a_j` with `a_i & a_j = 0`; push values onto supersets of themselves, query complement. **(core)**
- [ ] [Nuclear Fusion](https://codeforces.com/problemset/problem/71/E) — `Codeforces` `2200` — `O(3^n)` reconstruct formula — Fuse atoms into a target sequence; cp-algorithms submask classic — DP over mask by trying last fused group = a submask. **(core)**
- [ ] [Marbles](https://codeforces.com/problemset/problem/1215/E) — `Codeforces` `2200` — cost to gather colors by mask — `dp[mask]` min cost to place colors in `mask` as a contiguous block; transitions add one color against those already placed.
- [ ] [Felicity's Big Secret Revealed](https://codeforces.com/problemset/problem/757/D) — `Codeforces` `2200` — submask DP on bit string — Split a binary string into numbers `1…n` without reuse; submask-of-used-values DP. **(core)**
- [ ] [And Subset Count](https://cses.fi/problemset/task/3141) — `CSES` `Bitwise Operations` — SOS then invert — Count subsets whose AND equals each `k`; SOS for “AND ⊇ k”, then Möbius/differencing on the subset lattice. **(core)**
- [ ] [High Cry](https://codeforces.com/problemset/problem/875/D) — `Codeforces` `2200` — AND-submasks of range maxima — Count pairs where max on `[l,r]` equals `a_i` and AND of range equals `a_j`; stack + bit structure. **(stretch)**
- [ ] [Jzzhu and Numbers](https://codeforces.com/problemset/problem/449/D) — `Codeforces` `2400` — SOS + inclusion on AND=0 — Count subsequences with AND `0`; SOS counts with AND covering a mask, then inclusion-exclusion. **(stretch)**
- [ ] [Love-Hate](https://codeforces.com/problemset/problem/1523/D) — `Codeforces` `2400` — random sample + SOS on ≤15 bits — Pick random people’s like-masks as “universe”; SOS / subset DP on the ≤15 set bits. **(stretch)**
- [ ] [Bits And Pieces](https://codeforces.com/problemset/problem/1208/F) — `Codeforces` `2600` — SOS reachability for `a_i | (a_j & a_k)` — Famous hard SOS: propagate “two later values covering bits of complement”. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- Submask loop: `for (int s=m; s; s=(s-1)&m)` (+ handle `s=0`); never write `s--` alone — that visits non-submasks.
- Complexity: all `(mask, submask)` pairs = `3^n` (each bit: off / in-mask-only / in-both); use when `n ≤ 18`ish for partition DP, switch to SOS when you only need *aggregates* over all submasks.
- SOS (sum over subsets): `F = A; for i in 0..n-1: for mask: if mask>>i&1: F[mask] += F[mask^(1<<i)]` — `O(n·2^n)`.
- Sum over *supersets*: same loop but add into the bit-off side (`F[mask^(1<<i)] += F[mask]` when bit `i` is on), or SOS on bit-flipped indices.
- Inverse SOS / Möbius on subset lattice: given `F[mask]=Σ_{i⊆mask} A[i]`, recover `A` by subtracting along each bit (same loops, `-=`).
- Compatible / disjoint pair template: store presence (or the value) at each mask; SOS-max/OR into supersets; answer for `x` is SOS[`((1<<B)-1)^x`].
- Partition template: `dp[0]=0` (or `1` for ways); `for mask: for sub=mask; sub; sub=(sub-1)&mask: dp[mask] = best(dp[mask], combine(score(sub), dp[mask^sub]))`.
- Recognize “need something for every mask from all its submasks, and `n≈20`” → SOS; “need to *try splits* of a set” → `O(3^n)` submask enum.

## Where it appears in OAs / interviews
- **Puzzle / word masks:** “For each 7-letter puzzle, count dictionary words formable from its letters” → encode letters as bits, enumerate all `2^7` submasks of the puzzle (LC-style Valid Words for Each Puzzle pattern).
- **Compatibility under AND/OR:** “For each number, find another with no shared 1-bits / covering required flags” → Compatible Numbers / Qualification Rounds style SOS or pairwise mask check.
- **Team / group partition:** “Split `n ≤ 16` people into unordered groups maximizing pairwise score / requiring cliques” → Grouping / Close Group `O(3^n)` DP.
- **Aggregate over bit-subsets at scale:** “For every mask / every array value, count how many other values are submasks, supersets, or share a bit” → CSES SOS Bit Problem template (`n·2^{20}` over frequencies).
