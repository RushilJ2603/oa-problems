# 03 — Two Pointers & Sliding Window (Depth Pass)

**Placement value:** High (contest-form variants of OA sliding-window / pair-counting; trains the “find the monotone trick” skill Striver/LC miss).
**Prereq topics:** Arrays, Sorting, Prefix Sums, Hash Maps; base ladder for this topic already done.
**Pattern in one paragraph:** Same L/R window idea as the base sheet, but statements hide the monotonicity behind forbidden pairs, XOR/bit carries, greedy matching after sort, or “delete one segment / one edit.” Recognize it when a contiguous constraint is monotone in an endpoint, when sorted values let you advance one pointer only forward, or when counting valid subarrays reduces to “for each R, find the farthest/closest valid L.”

**Technique notes (non-obvious):**
- Exactly-k often = `at_most(k) − at_most(k−1)` (distinct values, # of 1s, etc.) — implement one window, call twice.
- XOR == SUM iff no bit collisions (carry-free); maintain OR/AND or per-bit occupancy and shrink when a bit repeats.
- Forbidden-pair / foe-pair segments: for each R, L cannot go left of the latest conflicting index — ans += R−L+1.
- Sorted pair/tuple counts: fix R (or value), binary-search or two-pointer the minimal L with `a[R]−a[L] ≤ Δ`, then add combinations `C(len, k−1)`.
- Greedy kangaroo / match-points: sort, match largest residual to the largest feasible partner from the other end — correctness is the non-obvious part, not the pointers.
- Negative sums break classic shrink-on-sum; use prefix minima, BS-on-length, or reset empty windows carefully (ATM and Students).
- After computing farthest reachable end with two pointers, binary lifting on that sparse table upgrades to “min cuts / jumps” (Cut).
- Opposite-direction string delete (Backspace): simulate from the right with parity of skips — still two pointers, not a stack rewrite.

## Ladder (easy -> hard, 25 problems)
- [ ] [Physics Practical](https://codeforces.com/problemset/problem/253/B) — `Codeforces` `1400` — sort + two pointers — Shrink so `max ≤ 2·min`; classic “delete fewest” framing. **(core)**
- [ ] [Pair of Topics](https://codeforces.com/problemset/problem/1324/D) — `Codeforces` `1400` — transform + pair count — Reduce to counting positive pairwise sums after `a_i−b_i`; OA-adjacent. **(core)**
- [ ] [Unstable String](https://codeforces.com/problemset/problem/1535/C) — `Codeforces` `1400` — window / alternating — Count binary substrings that stay alternating (with `?`); good CF-style counting.
- [ ] [Hossam and Friends](https://codeforces.com/problemset/problem/1771/B) — `Codeforces` `1400` — farthest-left constraint — Prefetch max forbidden left endpoint per R; template for “segment avoids bad pairs.” **(core)**
- [ ] [Array](https://codeforces.com/problemset/problem/224/B) — `Codeforces` `1500` — shortest exactly-k distinct — Minimal window with exactly k distinct; bridges to at-most-k templates. **(core)**
- [ ] [Uniqueness](https://codeforces.com/problemset/problem/1208/B) — `Codeforces` `1500` — delete one segment — Enumerate left keep-prefix; two-pointer the right keep-suffix for unique multiset.
- [ ] [A Tale of Two Lands](https://codeforces.com/problemset/problem/1166/C) — `Codeforces` `1500` — sorted pair count — Count pairs with `|a|+|b|>2·max(|a|,|b|)`; geometry rewritten as inequalities.
- [ ] [Close Tuples (easy version)](https://codeforces.com/problemset/problem/1462/E1) — `Codeforces` `1500` — sort + combinations — For each R, find L with `a[R]−a[L]≤2`, add `C(cnt,2)`. **(core)**
- [ ] [Backspace](https://codeforces.com/problemset/problem/1553/D) — `Codeforces` `1500` — reverse two pointers — Match t inside s deleting only via backspace parity from the right.
- [ ] [Distinct Values Subarrays II](https://cses.fi/problemset/task/2428) — `CSES` `Sorting and Searching` — at most k distinct count — Canonical `ans += r−l+1` with a frequency map. **(core)**
- [ ] [Xor Sum 2](https://atcoder.jp/contests/abc098/tasks/arc098_b) — `AtCoder` `ABC098 D / ~1400` — XOR=SUM window — Bitwise carry-free window; AtCoder classic. **(core)**
- [ ] [Longest k-Good Segment](https://codeforces.com/problemset/problem/616/D) — `Codeforces` `1600` — at most k distinct length — The CF-named form of the CSES count problem; must be automatic. **(core)**
- [ ] [Another Problem on Strings](https://codeforces.com/problemset/problem/165/C) — `Codeforces` `1600` — exactly k ones — Positions of 1s + two pointers / prefix of zeros between them.
- [ ] [Counting Kangaroos is Fun](https://codeforces.com/problemset/problem/372/A) — `Codeforces` `1600` — greedy matching — Sort; pair large into small with `2·small≤large` from both ends. **(core)**
- [ ] [DZY Loves Sequences](https://codeforces.com/problemset/problem/446/A) — `Codeforces` `1600` — one edit + runs — Precompute increasing run lengths; merge across one change.
- [ ] [To Add or Not to Add](https://codeforces.com/problemset/problem/231/C) — `Codeforces` `1600` — sort + cost window — Maximize frequency after ≤k increments using prefix sums on sorted array.
- [ ] [MP3](https://codeforces.com/problemset/problem/1198/A) — `Codeforces` `1600` — compress distinct range — After sorting unique values, minimal window covering enough distinct to fit bit budget.
- [ ] [Binary String](https://codeforces.com/problemset/problem/1680/C) — `Codeforces` `1600` — min-max window — Minimize `max(#0 inside, #1 outside)` via shrinking window on zeros.
- [ ] [Glider](https://codeforces.com/problemset/problem/1041/D) — `Codeforces` `1700` — flight segments — Two pointers over alternating air/ground intervals with a fuel budget. **(stretch)**
- [ ] [Count Triangles](https://codeforces.com/problemset/problem/1355/C) — `Codeforces` `1800` — sides via pointers — Count integer triangles from segment lengths using sorted two pointers. **(stretch)**
- [ ] [ATM and Students](https://codeforces.com/problemset/problem/1611/F) — `Codeforces` `1800` — sum window w/ negatives — Longest subarray with sum ≥s when values can be negative; prefix + careful L move. **(stretch)**
- [ ] [Foe Pairs](https://codeforces.com/problemset/problem/652/C) — `Codeforces` `1800` — forbidden pairs count — Same family as Hossam; tighten L by max foe partner. **(stretch)**
- [ ] [1D Sokoban](https://codeforces.com/problemset/problem/1494/C) — `Codeforces` `1900` — positions + TP — Special cells and boxes on a line; prefix counts + two pointers for best score. **(stretch)**
- [ ] [Match Points](https://codeforces.com/problemset/problem/1156/C) — `Codeforces` `2000` — greedy distance match — Sort; BS answer or two-pointer match with separation ≥z. **(stretch)**
- [ ] [Cut](https://codeforces.com/problemset/problem/1516/D) — `Codeforces` `2100` — TP + binary lifting — Maximal coprime-product segments via two pointers, then lift for min cuts. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- Write `at_most(k)` and derive `exactly(k)` without rethinking the window.
- Maintain freq + `distinct` (or bit occupancy) so each L/R step is O(1) amortized.
- For each R, compute maximal valid L (or minimal) and add `R−L+1` when counting subarrays.
- After sorting, advance only the left pointer for pair/tuple inequalities; never reset.
- Greedy match: decide which end is the “scarce” resource before coding the pointers.
- Prefetch per-index “latest conflict” arrays for forbidden-pair segment counts.
- When sums are non-monotone, switch to prefix sums + BS / deque — do not force a shrink-only window.
- Optional upgrade path: farthest-reach array → sparse table / binary lifting for multi-jump queries.

## Where it appears in OAs / interviews
- **“Count subarrays with ≤k different IDs / SKUs”** — direct reskin of CSES Distinct Values II / Longest k-Good Segment counting form.
- **“Longest session with at most k bad events”** — replacement / zero-flip window (same skeleton as AtCoder Longest X / CF Binary String).
- **“How many pairs of scores differ by at most D”** — sorted two pointers / Close Tuples style after a transform.
- **“Delete one contiguous bad segment to make all unique”** — Uniqueness-style keep-prefix + keep-suffix pointers.
