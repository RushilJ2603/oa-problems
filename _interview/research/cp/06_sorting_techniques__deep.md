# 06 — Sorting-based Techniques, Comparators & Coordinate Compression (Depth)

**Placement value:** High (sort-then-greedy, event order, and rank-compression + Fenwick still dominate harder OA / Div2 C–D array problems)
**Prereq topics:** Custom sort keys, event sweep basics, Fenwick/segment tree (for the compression tail)
**Pattern in one paragraph:** After the famous ladder, the next skill is *which key to sort on* under constraints (ties, open/close events, free-item thresholds) and *compressing every index the DS will touch* (including `r+1` removals / prefix values). Spot it when values are `≤1e9` but `n≤2e5`, when greediness needs a multiset over a sorted stream, or when a rewrite like `a_i−b_i` turns a pairwise condition into a 1D sorted scan.

## Ladder (easy -> hard, 25 problems)
- [ ] [USB vs. PS/2](https://codeforces.com/problemset/problem/762/B) — `Codeforces` `1400` — sort + typed greedy — USACO Guide: sort cheap→expensive within port types. **(core)**
- [ ] [New Year Ratings Change](https://codeforces.com/problemset/problem/379/C) — `Codeforces` `1400` — sort + force distinct — Sort by preferred rating, assign the next free integer ≥ preference. **(core)**
- [ ] [Knights of a Polygonal Table](https://codeforces.com/problemset/problem/994/B) — `Codeforces` `1400` — sort + multiset top-k — Process by power ↑; keep a size-`k` loot multiset of defeated knights. **(core)**
- [ ] [Array Splitting](https://codeforces.com/problemset/problem/1197/C) — `Codeforces` `1400` — sort adjacent gaps — Cost = total span − sum of largest `k−1` jumps; pure “sort the diffs” trick.
- [ ] [Pair of Topics](https://codeforces.com/problemset/problem/1324/D) — `Codeforces` `1400` — rewrite then sort — Map to `a_i−b_i`, sort, two-pointers / lower_bound for pairs. **(core)**
- [ ] [Woodcutters](https://codeforces.com/problemset/problem/545/C) — `Codeforces` `1500` — positional greedy — Trees already sorted by `x`; decide fall L/R with last occupied bound.
- [ ] [Air Conditioners](https://codeforces.com/problemset/problem/1547/E) — `Codeforces` `1500` — sort coords + dual scan — Sort AC positions; prefix/suffix `t+|x−pos|` mins. **(core)**
- [ ] [Tasks and Deadlines](https://cses.fi/problemset/task/1630) — `CSES` `Sorting and Searching` — exchange argument — Sort by duration ↑ (not deadline); reward is independent of order except durations. **(core)**
- [ ] [Room Allocation](https://cses.fi/problemset/task/1164) — `CSES` `Sorting and Searching` — event sort + pool — Sort arrivals/departures; reuse room IDs from a free stack. **(core)**
- [ ] [Movie Festival II](https://cses.fi/problemset/task/1632) — `CSES` `Sorting and Searching` — sort by end + multiset — `k` attendees: assign each film to the latest free end `≤ start`. **(core)**
- [ ] [Online games](https://atcoder.jp/contests/abc221/tasks/abc221_d) — `AtCoder` `ABC-D` — day events — Emit `+1` at `A`, `−1` at `A+B`; sort and histogram by active count.
- [ ] [Rectangles](https://atcoder.jp/contests/abc218/tasks/abc218_d) — `AtCoder` `ABC-D` — point set / coords — After sorting unique `x`/`y`, count opposite corners that close an axis-aligned rectangle. **(core)**
- [ ] [PriceFixed](https://codeforces.com/problemset/problem/1539/D) — `Codeforces` `1600` — sort + two-pointer buy — Sort by `b_i`; buy expensive-first until thresholds unlock free/cheap suffixes.
- [ ] [Seating Arrangements (hard version)](https://codeforces.com/problemset/problem/1566/D2) — `Codeforces` `1600` — row sort + Fenwick — Within each row, sorted seats create inversions = steps; BIT on ranks. **(core)**
- [ ] [Reading Books (easy version)](https://codeforces.com/problemset/problem/1374/E1) — `Codeforces` `1600` — multi-bucket sort — Partition both/Alice/Bob likes, sort each, merge prefixes.
- [ ] [Best Price](https://codeforces.com/problemset/problem/2051/E) — `Codeforces` `1600` — unique prices as keys — Sort candidate prices; prefix counts of “would buy / positive” at each threshold.
- [ ] [Correct Placement](https://codeforces.com/problemset/problem/1472/E) — `Codeforces` `1700` — 2D custom order — Sort by width ↑ (height ↓ on ties), scan with running min height; USACO Guide staple. **(core)**
- [ ] [Yet Another Monster Killing Problem](https://codeforces.com/problemset/problem/1257/D) — `Codeforces` `1700` — sort + suffix max — Heroes by power; suffix-max endurance beats monster runs in one day.
- [ ] [Array Optimization by Deque](https://codeforces.com/problemset/problem/1579/E2) — `Codeforces` `1700` — compress + BIT — Rank values; each insert chooses front/back by counting already-placed `<` / `>`. **(core)**
- [ ] [Printing Machine](https://atcoder.jp/contests/abc325/tasks/abc325_d) — `AtCoder` `ABC-D` — deadline sort + set — Sort by print-finish limit; always print the soonest-due job among available. **(stretch)**
- [ ] [Too Many Segments (hard version)](https://codeforces.com/problemset/problem/1249/D2) — `Codeforces` `1800` — sweep + multiset drop — Scan `x`, keep active segments by `r`; greedily delete furthest `r` when coverage `>k`. **(stretch)**
- [ ] [Petya and Array](https://codeforces.com/problemset/problem/1042/D) — `Codeforces` `1800` — compress prefixes + Fenwick — Count pairs with `pref[r]−pref[l]<t` via ranks on prefix sums. **(stretch)**
- [ ] [Feed Cats](https://codeforces.com/problemset/problem/1932/F) — `Codeforces` `1900` — compress `r+1` correctly — Sweep/DP on segments: compress the *removal coordinate* `r+1`, not `rank(r)+1`. **(stretch)**
- [ ] [Hanoi Factory](https://codeforces.com/problemset/problem/777/E) — `Codeforces` `2000` — ring comparator + stack/DS — Sort rings by outer↓ (inner↓ tie-break); nest with a monotonic structure. **(stretch)**
- [ ] [Boring Segments](https://codeforces.com/problemset/problem/1555/E) — `Codeforces` `2100` — sort by weight + window — Sort segments by beauty; two-pointer expand while segtree says `[1..m]` fully covered. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- **Compress the event you update, not a proxy:** for range cover, include `r+1` (or `r` if you store inclusive ends consistently) in the coordinate list — `rank(r)+1` is a different (wrong) point when holes exist.
- **Strict weak order under ties:** when sorting by width then scanning heights (Correct Placement), put equal widths in height-descending order so a same-width peer is not treated as “already seen.”
- **Rewrite before sorting:** inequalities like `a_i+a_j>b_i+b_j` → sort `a−b` (Pair of Topics); don’t invent a 2D cmp.
- **Event secondary key:** decide open-vs-close order explicitly (`+1` before `−1` or the reverse) — Room Allocation / Online games WA if a room frees after the same-time arrival is processed wrong.
- **Offline Fenwick template:** collect every value that will be `update`/`query`’d (array values *and* derived prefixes) → `sort+unique` → `lower_bound` ranks → then scan.
- **Greedy over a sorted stream + multiset:** Knights / Movie Festival II / Too Many Segments — sort the primary key, maintain a dynamic bag of “active ends / loots,” delete the extremal element when a constraint breaks.
- **Exchange argument ⇒ sort key:** Tasks and Deadlines → duration ascending; Hanoi / nesting rings → outer radius descending with a careful inner tie-break.
- **Suffix/prefix after one sort:** Monster Killing (suffix max power), Air Conditioners (prefix/suffix min cost) — once positions are ordered, answers are linear scans.

## Where it appears in OAs / interviews
- **Typed inventory / coupon assign:** “USB vs PS/2” / discount tiers — sort price, fill constrained buckets first.
- **Meeting rooms / k workers:** Room Allocation / Movie Festival II — event sort + reuse earliest-free resource (OA classic).
- **Leaderboard uniqueness / rank remap:** Ratings Change / Best Price — sort preferences or thresholds, assign next free rank or evaluate at compressed candidates.
- **Count inversions / range pairs under 1e9 values:** Seating D2 / Petya and Array / Deque optimization — compress then Fenwick (same family as “count smaller to the right”).
