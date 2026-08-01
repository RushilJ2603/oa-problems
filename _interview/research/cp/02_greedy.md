# 02 — Greedy (exchange argument, sorting-by-criterion, scheduling)

**Placement value:** High — OAs and Div2 A–C constantly ask “sort by the right key, then take locally optimal choices”; interval / deadline / pairing variants dominate interview greedy.
**Prereq topics:** Sorting, two pointers / multiset basics, simple proofs by contradiction or adjacent swap.
**Pattern in one paragraph:** A greedy problem asks you to build an optimal answer by repeatedly making a locally best choice under a fixed priority (earliest finish, smallest cost, largest gain, custom comparator from a 2-element swap). Recognize it when the statement maximizes/minimizes a count/sum under constraints and a sort + one left-to-right pass (sometimes with a heap) feels plausible; prove the key with an **exchange argument** (any optimal solution can be swapped toward the greedy order without worsening) or by showing every rejected alternative is dominated.

## Ladder (easy -> hard, ~18-28 problems)

- [ ] [Hit the Lottery](https://codeforces.com/problemset/problem/996/A) — `Codeforces` `800` — coin / denomination greedy — **(core)** — OA warm-up; teaches when canonical denominations make greedy safe (vs general coin DP)
- [ ] [Twins](https://codeforces.com/problemset/problem/160/A) — `Codeforces` `900` — sort-descending + take until threshold — **(core)** — A2OJ / early CF classic; pure “sort by criterion then greed”
- [ ] [Duff and Meat](https://codeforces.com/problemset/problem/588/A) — `Codeforces` `900` — running-minimum buy price — placement-band CF greedy; keep cheapest price seen so far
- [ ] [Dragons](https://codeforces.com/problemset/problem/230/A) — `Codeforces` `1000` — sort by strength, fight in order — **(core)** — A2OJ ladder staple; “order enemies so bonuses unlock the next”
- [ ] [Assign Cookies](https://leetcode.com/problems/assign-cookies/) — `LeetCode` `Easy` — sort both + greedy assign — **(core)** — NeetCode / Striver; OA pairing template (same idea as Ferris Wheel)
- [ ] [Ferris Wheel](https://cses.fi/problemset/task/1090) — `CSES` `Sorting and Searching` — two-pointer weight pairing — **(core)** — CSES / USACO Guide; lightest+heaviest gondola fill
- [ ] [Jump Game](https://leetcode.com/problems/jump-game/) — `LeetCode` `Medium` — farthest-reach scan — **(core)** — NeetCode / Striver; OA staple “reachable frontier” greedy
- [ ] [Jump Game II](https://leetcode.com/problems/jump-game-ii/) — `LeetCode` `Medium` — BFS-layers / range greedy — NeetCode; min jumps from Jump Game invariant
- [ ] [BerSU Ball](https://codeforces.com/problemset/problem/489/B) — `Codeforces` `1200` — sort + greedy matching — A2OJ-era classic; skill pairing within difference 1
- [ ] [Movie Festival](https://cses.fi/problemset/task/1629) — `CSES` `Sorting and Searching` — earliest-ending interval scheduling — **(core)** — CSES / USACO Guide focus problem; *the* activity-selection proof
- [ ] [Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/) — `LeetCode` `Medium` — sort by end, drop conflicts — **(core)** — NeetCode / Striver; Movie Festival rephrased as “min removals”
- [ ] [Minimum Number of Arrows to Burst Balloons](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/) — `LeetCode` `Medium` — sort by end, stab overlapping groups — NeetCode; same comparator as interval scheduling
- [ ] [Tasks and Deadlines](https://cses.fi/problemset/task/1630) — `CSES` `Sorting and Searching` — sort by duration (exchange) — **(core)** — CSES / USACO Guide / CPH Ch.6; canonical exchange-argument scheduling
- [ ] [Megalomania](https://atcoder.jp/contests/abc131/tasks/abc131_d) — `AtCoder` `ABC D` — earliest-deadline-first check — AtCoder ABC classic; deadline sort + simulate finish times
- [ ] [Gas Station](https://leetcode.com/problems/gas-station/) — `LeetCode` `Medium` — circular tank reset — **(core)** — NeetCode / Striver; exchange: if you fail at `i`, no start in the failed segment works
- [ ] [Queue](https://codeforces.com/problemset/problem/545/D) — `Codeforces` `1300` — sort serving times, keep if wait ≤ ti — **(core)** — CF scheduling order; disappointment = wait vs service
- [ ] [Missing Coin Sum](https://cses.fi/problemset/task/2183) — `CSES` `Sorting and Searching` — reachable-prefix greedy — **(core)** — CSES classic; if next coin > `reach+1`, that sum is impossible
- [ ] [USB vs. PS/2](https://codeforces.com/problemset/problem/762/B) — `Codeforces` `1400` — sort mice by cost, fill ports — USACO Guide (Silver greedy-sorting); multi-type resource + cheapest-first
- [ ] [Islands War](https://atcoder.jp/contests/abc103/tasks/abc103_d) — `AtCoder` `ABC D` — sort requests by right end, cut bridge — AtCoder interval-cover greedy (same family as Movie Festival)
- [ ] [Room Allocation](https://cses.fi/problemset/task/1164) — `CSES` `Sorting and Searching` — sweep + assign free room — CSES; free analogue of Meeting Rooms II (LC 253 is Premium)
- [ ] [Boxers](https://codeforces.com/problemset/problem/1203/E) — `Codeforces` `1500` — sort weights, ±1 uniqueness — CF Div3 E; greedy claim of free slots left-to-right
- [ ] [Potions (Hard Version)](https://codeforces.com/problemset/problem/1526/C2) — `Codeforces` `1600` — take all positive, dump worst via heap — placement→stretch bridge; health never negative with max potions
- [ ] [Movie Festival II](https://cses.fi/problemset/task/1632) — `CSES` `Sorting and Searching` — k people, earliest-ending + multiset — **(stretch)** — CSES; multi-resource interval scheduling
- [ ] [Petya's Exams](https://codeforces.com/problemset/problem/978/G) — `Codeforces` `1700` — prepare latest-possible before each exam — **(stretch)** — deadline packing / reverse greedy schedule
- [ ] [Yet Another Tournament](https://codeforces.com/problemset/problem/1783/C) — `Codeforces` `1700` — sort + binary-search wins — **(stretch)** — USACO Guide (Silver greedy-sorting)
- [ ] [Course Schedule III](https://leetcode.com/problems/course-schedule-iii/) — `LeetCode` `Hard` — sort by deadline, max-heap of durations — **(stretch)** — Striver-adjacent OA hard; drop longest course when overdue
- [ ] [Candy](https://leetcode.com/problems/candy/) — `LeetCode` `Hard` — two-pass slope greedy — **(stretch)** — Striver / OA classic; local peaks from left then right

## Must-internalize checklist

- Sort-by-end (or by deadline / duration) then one forward pass for interval / activity selection.
- Exchange argument: compare two adjacent items; if swapping never hurts, the comparator defines an optimal order (Tasks & Deadlines template).
- Pairing: sort + two pointers (cookies / Ferris Wheel / boats) — assign greediest feasible match.
- Reach / tank invariants: Jump Game farthest index; Gas Station “reset start when tank < 0”.
- Constructible / Frobenius-style: Missing Coin Sum — maintain `reach`, accept next iff `≤ reach+1`.
- Multi-resource scheduling: Room Allocation / Movie Festival II — free rooms via multiset of end times.
- When to abandon greedy: general coin change & 0/1 knapsack need DP (USACO Guide “when greedy fails”).
- Proof habit: argue that any optimal solution can be transformed into the greedy one without loss.

## Where it appears in OAs / interviews

- “Max meetings / min removals / burst balloons with arrows” → sort intervals by end time (Movie Festival / LC 435 / LC 452).
- “Can you reach the end / min jumps / circular gas tour” → frontier or tank scan (Jump Game family / Gas Station) — very common FAANG phone-screen.
- “Assign cookies / rescue boats / pair light+heavy under capacity” → sort + two pointers (Assign Cookies / Ferris Wheel).
- “Finish jobs before deadlines / maximize score under time” → sort by deadline or duration, often with a heap to drop the worst (Tasks & Deadlines / Course Schedule III / Potions).
