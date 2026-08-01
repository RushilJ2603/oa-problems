# 12 — DP III: Knapsack Variants & Subsequence (depth)

**Placement value:** High — post-ladder CF/AtCoder twists on 0/1, multiple, group, and contribution knapsacks plus subsequence-counting / LCS-with-constraints; this is the Div2 C–D / CM band after CSES coins + AtCoder D/E/F.
**Prereq topics:** Base knapsack ladder (0/1 vs unbounded loop order, subset-sum / partition, value-as-state flip), LCS / edit / distinct-subsequences templates, bitset optional; meet-in-the-middle for one stretch item
**Pattern in one paragraph:** Same engines as the base topic — fill a capacity, flip to value-dimension, or align two sequences — but statements force a rewrite first: “every k-th free” → sort + prefix then 0/1 on leftovers; “W is 10^9 but few weight classes / n≤40” → group by weight or MITM; shelves/days/lessons → precompute per-group bests, then knapsack groups; subsequence asks → count ways with `?`, forced length, or an LCS that must avoid a virus string (automaton). Spot it when a classic knapsack/LCS sits under a contest packing (deadlines, nested groups, contribution over all subsets/segments).

## Technique notes (non-obvious)
- Free-every-k (K for the Price of One): sort ascending; paying for `i` items can unlock `⌊i/k⌋` free ones taken from the most expensive paid — hard version uses prefix sums + DP over how many “paid blocks” you buy.
- Huge `W`, small structure: few distinct weights → knapsack only on weight classes (Simple Knapsack); `n≤40` → split, enumerate 2^{n/2} subset sums, binary-search complements (Programming Contest).
- Nested / group knapsack (Porcelain, Timetable): for each group compute `best[t]` = value of taking exactly `t` items from that group, then 0/1-knapsack the groups into the global budget.
- Multiple knapsack (Book Shop II): binary-split counts `1,2,4,…,remain` into pseudo-items and run ordinary 0/1 — do not loop `cnt` naively.
- Contribution DP (Knapsack for All Subsets / Segments): answer is not one optimal pack — each subset/segment adds `f(sum)`; push updates that add the contribution of newly formed sums (often mod a prime).
- Offset / signed knapsack (Coding Company): map difference `d` to index `d+OFFSET`; employees change both sum and “imbalance”.
- Subsequence counting: `dp[i][j]` consume/skip; with `?` (Number of Subsequences) multiply three branches; with a forbidden pattern (Lucky Common Subsequence) fold a KMP failure link into the LCS state so the virus never completes.
- Bitset / forced coins (Coin Troubles, Unbearable Lightness): reachability `dp |= dp<<w`, then peel forced items or argue which total weights can be unique.

## Ladder (easy -> hard, 24 problems)
- [ ] [K for the Price of One (Easy Version)](https://codeforces.com/problemset/problem/1282/B1) — `Codeforces` `1400` — sort + free every k-th — **(core)** pay for a prefix, take freebies from the expensive end; OA-adjacent budget packing
- [ ] [Programming Contest](https://atcoder.jp/contests/abc184/tasks/abc184_f) — `AtCoder` `ABC184 F (~1400)` — meet-in-the-middle knapsack — **(core)** `n≤40`, `T` huge; split halves, sort subset sums, upper_bound complements
- [ ] [Simple Knapsack](https://atcoder.jp/contests/abc060/tasks/arc073_b) — `AtCoder` `ABC060 D (~1500)` — few weight classes — **(core)** `w_i ∈ [w1, w1+3]`; DP by (count, extra-weight) instead of full `W`
- [ ] [K for the Price of One (Hard Version)](https://codeforces.com/problemset/problem/1282/B2) — `Codeforces` `1600` — prefix + block DP — **(core)** same shop rule with larger `n`; optimize freebie accounting via prefixes
- [ ] [Substring and Subsequence](https://codeforces.com/problemset/problem/163/A) — `Codeforces` `1700` — count string alignments — **(core)** ways to pick a nonempty subsequence of `t` matching a substring of `s`; classic 2-string consume/skip
- [ ] [Shaass and Bookshelf](https://codeforces.com/problemset/problem/294/B) — `Codeforces` `1700` — thickness/width knapsack — **(core)** books upright vs flat; pack thickness into shelf width after choosing the flat set
- [ ] [Road Optimization](https://codeforces.com/problemset/problem/1625/C) — `Codeforces` `1700` — remove ≤k signs — **(core)** `dp[i][used]` min time to reach sign `i`; jump over deleted signs (segment knapsack)
- [ ] [Knapsack for All Subsets](https://atcoder.jp/contests/abc169/tasks/abc169_f) — `AtCoder` `ABC169 F (~1700)` — contribution over subsets — **(core)** for every subset, add `f(sum)` mod `998244353`; update DP by contribution, not one optimum
- [ ] [Writing Code](https://codeforces.com/problemset/problem/543/A) — `Codeforces` `1800` — 0/1 knapsack count — **(core)** `n` programmers, ≤`m` lines, ≤`b` bugs; number of ways — nested capacity DP
- [ ] [Timetable](https://codeforces.com/problemset/problem/946/D) — `Codeforces` `1800` — per-day precompute + knapsack — **(core)** for each day, best hours saved by skipping `t` lessons; then knapsack days into `k` skips
- [ ] [Unmerge](https://codeforces.com/problemset/problem/1381/B) — `Codeforces` `1800` — consecutive chunks → subset-sum — **(core)** split permutation into maximal left-to-right maxima blocks; ask if block sizes can make sum `n`
- [ ] [Colored Balls](https://codeforces.com/problemset/problem/1954/D) — `Codeforces` `1800` — knapsack counting with colors — ways/score when combining equal counts; 0/1 style on multiplicities
- [ ] [Book Shop II](https://cses.fi/problemset/task/1159) — `CSES` `Dynamic Programming` — multiple knapsack — **(core)** CSES sequel to Book Shop; binary grouping of copy counts into 0/1 items
- [ ] [Knapsack for All Segments](https://atcoder.jp/contests/abc159/tasks/abc159_f) — `AtCoder` `ABC159 F (~1900)` — contribution on subarrays — segment analogue of All Subsets; push sums formed by extending right endpoint
- [ ] [Checkout Assistant](https://codeforces.com/problemset/problem/19/B) — `Codeforces` `1900` — time-as-capacity knapsack — **(stretch)** item `i` costs `t_i` time and takes `c_i+1` “slots”; classic CF 0/1 with path to min money
- [ ] [Porcelain](https://codeforces.com/problemset/problem/148/E) — `Codeforces` `1900` — nested / group knapsack — **(stretch)** each shelf: prefix/suffix best for taking `t` cups; then knapsack shelves into `k` takes
- [ ] [Subsequences (hard version)](https://codeforces.com/problemset/problem/1183/H) — `Codeforces` `1900` — distinct subsequences by length — **(stretch)** count distinct subsequences of each length; last-occurrence trick to avoid double-count
- [ ] [Bookshelves](https://codeforces.com/problemset/problem/981/D) — `Codeforces` `1900` — bitwise OR knapsack — **(stretch)** greedily fix answer bits high→low; feasibility = can split into `k` segments each covering needed bits
- [ ] [Number of Subsequences](https://codeforces.com/problemset/problem/1426/F) — `Codeforces` `2000` — `abc` subsequences with `?` — **(stretch)** three rolling counts; `?` triples transitions — contest Distinct Subsequences
- [ ] [Lucky Common Subsequence](https://codeforces.com/problemset/problem/346/B) — `Codeforces` `2000` — LCS + KMP virus — **(stretch)** LCS DP state includes automaton position; never complete the forbidden string
- [ ] [Coding Company](https://cses.fi/problemset/task/1665) — `CSES` `Dynamic Programming` — offset knapsack on imbalance — **(stretch)** USACO Guide hard; sort employees, DP on (processed, open slots / difference)
- [ ] [The Unbearable Lightness of Weights](https://codeforces.com/problemset/problem/1032/E) — `Codeforces` `2100` — unique subset sums — **(stretch)** bitset reachability + count how many weights are forced unique; CM ceiling subset-sum reasoning
- [ ] [Coin Troubles](https://codeforces.com/problemset/problem/283/C) — `Codeforces` `2100` — unbounded + forced coins — **(stretch)** must use given coins at least once; shift target then unbounded knapsack / bitset
- [ ] [Subsequences of Length Two](https://codeforces.com/problemset/problem/1409/F) — `Codeforces` `2100` — change ≤n chars, max pattern count — **(stretch)** DP on (pos, changes left, first-char progress) for a length-2 pattern

## Must-internalize checklist (5-10 bullets)
- Rewrite the shop/deadline/group story into either (a) one 0/1 pass, (b) per-group `best[t]` then group-knapsack, or (c) contribution over all subsets/segments.
- Binary-group multiple copies; never `for _ in cnt` inside the capacity loop unless `cnt` is tiny.
- MITM when `n≤40` and capacity/`T` is huge; keep sorted vectors of achievable sums per half.
- Subsequence counters: track last index per character (distinctness) or an automaton index (forbidden pattern); with `?`, multiply/add the three letter branches carefully under mod.
- Offset arrays for signed imbalance; bitset `dp |= dp << w` when only reachability (or uniqueness of a sum) matters.
- Recover construction when needed (Checkout / Bookshelf): parent pointers or redo DP knowing the optimum budget.

## Where it appears in OAs / interviews
- **Promo pricing:** “Pay for k items, get floor(k/m) free” → K for the Price of One family (ecommerce OA flavor).
- **Team / bug budget:** “Assign lines of code to n people with a global bug cap” → Writing Code (0/1 with two capacities).
- **Nested inventory:** “Each shelf contributes a local pack; choose across shelves under a global k” → Porcelain / Timetable.
- **String analytics:** “Count `abc` patterns with wildcards” or “LCS that must not contain a banned token” → Number of Subsequences / Lucky Common Subsequence.
