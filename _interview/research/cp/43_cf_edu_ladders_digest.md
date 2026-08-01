# 43 — CF EDU + A2OJ / CP-31 ladders: what to grind, in order

**Placement value:** High — this is the post-Striver bridge: CF EDU installs the CP-native templates Striver under-teaches (segtree, lazy, Z, DSU polish, contest two-pointers / BS-on-answer), while CP-31 + A2OJ rating ladders train the observation/ad-hoc skill that OAs and Div2 share.
**Prereq topics:** Finished Striver A2Z (LC-style arrays / BS / graphs / classic DP / KMP-level strings); basic CF multi-test I/O; willingness to enroll in [ITMO Academy pilot](https://codeforces.com/edu/courses) (course 2)
**Pattern in one paragraph:** Do **not** grind randomly. Run two tracks in lockstep: (1) **CF EDU modules** for templates Striver never drilled in contest form — grind order (not lesson number order): Two Pointers (lesson 9) → Binary Search (lesson 6) → DSU (lesson 7) → Segment Tree Pt1 (lesson 4) → Z-function (lesson 3) → Segment Tree Pt2 lazy (lesson 5, stretch) → Suffix Array (lesson 2, stretch); (2) **rating ladders** for volume — skip CP-31 800–1200, clear **CP-31 1300→1900** ([TLE sheet](https://www.tle-eliminators.com/cp-sheet), [announce](https://codeforces.com/blog/entry/139079)), and keep an **A2OJ-style rating ladder** matched to current rating ([mirrors](https://a2oj.netlify.app/ladders), [origin](https://codeforces.com/blog/entry/47442)). Rule: finish the EDU practice for a module, then immediately transfer with the contest problems below at that band; climb one CP-31 rating block (~31 problems) before unlocking the next EDU-heavy DS module. Signal you are on-map when a Div2 C/D is either “EDU template + twist” or “CP-31-style observation,” not “I need a brand-new algorithm.”

## Ladder (easy -> hard, 26 problems)
*Transfer drills after each EDU module / rating block. EDU practice stays on CF EDU; these are the contest problems that prove the skill. Order by difficulty within the overall roadmap.*

- [ ] [Number of Pairs](https://codeforces.com/problemset/problem/1538/C) — `Codeforces` `1300` — EDU Two Pointers / CP-31 — **(core)** first post-Striver TP transfer: sorted two-pointers / BS count of pairs with sum in `[l,r]`
- [ ] [Chat Ban](https://codeforces.com/problemset/problem/1612/C) — `Codeforces` `1300` — EDU Binary Search — **(core)** monotonic “how many messages until ban” → BS on answer; CP-31 1300 pace
- [ ] [3SUM Closure](https://codeforces.com/problemset/problem/1698/C) — `Codeforces` `1300` — CP-31 observation — **(core)** ladder skill Striver never trains: 2-min casework kills O(n²); if you invent DP here you failed the map
- [ ] [Factory Machines](https://cses.fi/problemset/task/1620) — `CSES` `Sorting and Searching` — EDU Binary Search twin — **(core)** *the* “can we finish by time T?” check; same predicate shape as EDU BS Step 2
- [ ] [Maximum Median](https://codeforces.com/problemset/problem/1201/C) — `Codeforces` `1400` — EDU BS / CP-31 — **(core)** BS on median value + greedy spend; CP-31 1400 staple
- [ ] [Books](https://codeforces.com/problemset/problem/279/B) — `Codeforces` `1400` — EDU Two Pointers / A2OJ — **(core)** classic A2OJ ladder TP: longest prefix of books under time `t`
- [ ] [Learning Languages](https://codeforces.com/problemset/problem/277/A) — `Codeforces` `1400` — EDU DSU — employees linked via shared languages; first DSU after EDU lesson 7 (+ empty-language edge)
- [ ] [Magic Powder - 2](https://codeforces.com/problemset/problem/670/D2) — `Codeforces` `1500` — EDU Binary Search — BS on cookies baked; check burns powder; EDU “search on answer” textbook
- [ ] [Kefa and Company](https://codeforces.com/problemset/problem/580/B) — `Codeforces` `1500` — EDU Two Pointers — **(core)** sort by money, sliding window friendship sum; A2OJ/EDU overlap
- [ ] [Knight Tournament](https://codeforces.com/problemset/problem/356/A) — `Codeforces` `1500` — EDU DSU / set — paint survivors in ranges; DSU “next alive” or set erase — bridge into segtree thinking
- [ ] [Dynamic Range Sum Queries](https://cses.fi/problemset/task/1648) — `CSES` `Range Queries` — EDU Segment Tree Pt1 — **(core)** point update + range sum; implement Fenwick *or* EDU segtree once from memory
- [ ] [Hotel Queries](https://cses.fi/problemset/task/1143) — `CSES` `Range Queries` — EDU Segment Tree walk — **(core)** descend to first hotel with `≥x` rooms; same “first at least X” pattern as EDU segtree steps
- [ ] [Hamburgers](https://codeforces.com/problemset/problem/371/C) — `Codeforces` `1600` — EDU Binary Search — BS on count of hamburgers; recipe + money check; mid-band CP-31/A2OJ energy
- [ ] [Destroying Array](https://codeforces.com/problemset/problem/722/C) — `Codeforces` `1600` — EDU DSU — **(core)** reverse deletions → unions, track max component sum; *the* reverse-DSU classic after EDU
- [ ] [Distinct Characters Queries](https://codeforces.com/problemset/problem/1234/D) — `Codeforces` `1600` — EDU Segment Tree / BIT — **(core)** 26 BITs or OR-segtree; OA-shaped “presence on `[l,r]`”
- [ ] [Segment Tree](https://atcoder.jp/contests/practice2/tasks/practice2_j) — `AtCoder` `ACL Practice J` — EDU Segment Tree Pt1 template — ACL RMQ + point set; clean mirror of EDU Pt1 before CF twists
- [ ] [Xenia and Bit Operations](https://codeforces.com/problemset/problem/339/D) — `Codeforces` `1700` — EDU Segment Tree — alternating OR/XOR by layer; proves you own the tree layout, not just sum/min
- [ ] [Password](https://codeforces.com/problemset/problem/126/B) — `Codeforces` `1700` — EDU Z-function — **(core)** longest string that is prefix, suffix, *and* interior occurrence; Z / π milestone after EDU lesson 3
- [ ] [Coffee and Coursework (Hard Version)](https://codeforces.com/problemset/problem/1118/D2) — `Codeforces` `1700` — EDU BS / CP-31 — BS on days with penalty decay; CP-31 1700 rating-builder
- [ ] [Path Queries](https://codeforces.com/problemset/problem/1213/G) — `Codeforces` `1800` — EDU DSU — offline: sort edges by weight, DSU merge, answer path-count queries; DSU beyond connectivity
- [ ] [Roads not only in Berland](https://codeforces.com/problemset/problem/25/D) — `Codeforces` `1900` — EDU DSU — **(stretch)** build tree from redundant edges: find cycles, rewire with DSU
- [ ] [Range Updates and Sums](https://cses.fi/problemset/task/1735) — `CSES` `Range Queries` — EDU Segment Tree Pt2 — **(stretch)** lazy add + assign + range sum; finish EDU lesson 5 then this
- [ ] [Sereja and Brackets](https://codeforces.com/problemset/problem/380/C) — `Codeforces` `2000` — EDU custom-merge segtree — **(stretch)** node = (matched, open, close); *the* merge-struct milestone
- [ ] [Prefixes and Suffixes](https://codeforces.com/problemset/problem/432/D) — `Codeforces` `2000` — EDU Z — **(stretch)** all borders that are prefixes + occurrence counts; Z / π endgame
- [ ] [Minimax Problem](https://codeforces.com/problemset/problem/1288/D) — `Codeforces` `2000` — EDU BS + bitmasks — **(stretch)** BS on min, check with `2^m` masks; Candidate Master combo
- [ ] [XOR on Segment](https://codeforces.com/problemset/problem/242/E) — `Codeforces` `2000` — EDU Segtree Pt2 / lazy — **(stretch)** range XOR flip + range sum; lazy or 20 bit-segtrees

## Must-internalize checklist (5-10 bullets)
- **Grind order (post-Striver):** EDU TP → EDU BS → EDU DSU → EDU Segtree Pt1 (+ CSES Range Queries) → EDU Z → (stretch) EDU Segtree Pt2 → (stretch) Suffix Array; never start at Suffix Array / lazy.
- **Ladder rule:** CP-31 skip ≤1200; clear each rating block 1300→1900 before living in the next. Parallel A2OJ/C2-style ladder = problems near *your current* rating, not random tags.
- **Two-pointer template:** sorted or sliding window where the second index only moves forward; count pairs / longest valid segment in `O(n)` after sort.
- **BS-on-answer template:** predicate `can(mid)` monotonic; binary-search the answer space (time, count, median, distance); always prove monotonicity before coding.
- **DSU toolkit:** path compression + union by size/rank; reverse-offline (delete→add backwards); component size / sum on merge; “next surviving index” via DSU or set.
- **Segtree Pt1 from memory:** build / point-update / range-query for associative `op`; tree-walk for “first index with value ≥ x” (Hotel Queries).
- **Z-function from memory:** `z[i]` = LCP of `s` and `s[i:]`; derive prefix-border / period / pattern match without reaching for KMP first.
- **Lazy Pt2 (stretch):** store pending add/assign on node; `push` before touching children; compose tags correctly (assign kills prior add).
- **Weekly split:** ~40% EDU practice + transfer problems above, ~40% CP-31 current rating, ~20% virtual contest + 24h upsolve — rating without EDU stalls on DS Div2 Ds; EDU without ladders stalls on ad-hoc Cs.

## Where it appears in OAs / interviews
- Timed OA (60–90 min, 2–4 tasks): Task 1–2 are CP-31 1300–1500 observation/greedy; Task 3 is often “many queries on an array” → Fenwick/segtree (EDU Pt1), not recomputing prefixes each time.
- “Minimum days / machines / powder to produce `k` items” → binary search on answer with a greedy/feasibility check (Factory Machines / Magic Powder / Hamburgers family) — extremely common in OA math sections.
- “Count pairs / longest subarray with at most `k` distinct / sum ≤ `t`” → two pointers (Number of Pairs / Books / k-Good Segment), not nested loops — HackerRank/HackerEarth classics.
- Connectivity after merges/splits, or “process deletions offline” → DSU (Learning Languages / Destroying Array); interviewers ask for the reverse-union insight more often than for Kruskal MST code.
