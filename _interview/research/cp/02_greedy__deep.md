# 02 — Greedy (exchange argument, scheduling) — Depth Pass

**Placement value:** High — post-ladder CF Div2 C/D scheduling & custom-comparator greeds; these are the forms that show up once Movie-Festival / Tasks-Deadlines templates are automatic.
**Prereq topics:** Sorting + heaps/multisets, binary search on answer, exchange-argument proofs (adjacent swap), basic interval sweep.
**Pattern in one paragraph:** After the classic “sort by end / duration / deadline” ladder, deeper greeds ask for a **custom comparator from an n=2 exchange**, a **feasibility check under a guessed answer**, or a **priority queue over the currently available jobs** (earliest exit / reverse-from-deadline). Recognize them when order of items changes the objective by a closed-form delta, when you can binary-search a time/cost and simulate, or when idle gaps must be jumped while always serving the tightest live deadline.

## Ladder (easy -> hard, ~18-28 problems)

- [ ] [Tape](https://codeforces.com/problemset/problem/1110/B) — `Codeforces` `1400` — cover points with k segments / drop largest gaps — **(core)** — total span minus the `(k-1)` largest inter-break gaps; OA-adjacent “segments of tape”
- [ ] [Knights of a Polygonal Table](https://codeforces.com/problemset/problem/994/B) — `Codeforces` `1400` — sort by power, take top-k loot via heap — **(core)** — sliding “who can rob whom” with a size-capped priority queue
- [ ] [The Delivery Dilemma](https://codeforces.com/problemset/problem/1443/C) — `Codeforces` `1400` — binary-search finish time + greedy courier vs pickup — **(core)** — classic BS-on-answer wrapped around a greedy split
- [ ] [Schedule Management](https://codeforces.com/problemset/problem/1701/C) — `Codeforces` `1400` — binary-search hours, reassign overloaded workers — **(core)** — load-balancing feasibility greedy; Div2 C staple
- [ ] [Vanya and Exams](https://codeforces.com/problemset/problem/492/C) — `Codeforces` `1400` — raise grades with min essays — fill lowest-current grades first under essay budget
- [ ] [Stick Divisions](https://cses.fi/problemset/task/1161) — `CSES` `Additional Problems` — reverse Huffman merges — **(core)** — always split using the two current smallest costs; pure exchange/Huffman template
- [ ] [Reading Books](https://cses.fi/problemset/task/1631) — `CSES` `Sorting and Searching` — two-reader schedule — **(core)** — answer is `max(sum, 2·max)`; non-obvious closed form after greedy pairing
- [ ] [Two TVs](https://codeforces.com/problemset/problem/845/C) — `Codeforces` `1500` — schedule on 2 resources — **(core)** — sort by start; track last-end on each TV (bridge to Movie Festival II)
- [ ] [Air Conditioner](https://codeforces.com/problemset/problem/1304/C) — `Codeforces` `1500` — maintain feasible temp interval over time — **(core)** — grow/shrink `[lo,hi]` by elapsed time between customers; reject when empty
- [ ] [Fight with Monsters](https://codeforces.com/problemset/problem/1296/D) — `Codeforces` `1500` — sort leftover HP after full rounds — spend limited “your hits” on monsters needing fewest extra strikes
- [ ] [Stas and the Queue at the Buffet](https://codeforces.com/problemset/problem/1151/D) — `Codeforces` `1600` — exchange comparator `(b−a)` — **(core)** — *the* CF exchange-argument drill: expand cost, sort by adjacent-swap delta
- [ ] [PriceFixed](https://codeforces.com/problemset/problem/1539/D) — `Codeforces` `1600` — 2-for-1 threshold buy order — **(core)** — buy cheapest from the left while unlocking discounts from the right (two pointers)
- [ ] [Counting Kangaroos is Fun](https://codeforces.com/problemset/problem/372/A) — `Codeforces` `1600` — nest smaller into larger — sort + two pointers; at most `⌊n/2⌋` pockets
- [ ] [Hacker, pack your bags!](https://codeforces.com/problemset/problem/822/C) — `Codeforces` `1600` — best voucher per duration, match complements — sort endpoints; keep min-cost for each length
- [ ] [Printing Machine](https://atcoder.jp/contests/abc325/tasks/abc325_d) — `AtCoder` `ABC D (450)` — earliest-exit among available jobs + PQ — **(core)** — jump idle time to next arrival; exchange: always print the live job that leaves first
- [ ] [Exams](https://codeforces.com/problemset/problem/732/D) — `Codeforces` `1700` — binary-search last day + greedy subject prep — **(stretch)** — schedule each subject’s exam on its latest feasible day in the window
- [ ] [Petya and Exam](https://codeforces.com/problemset/problem/1282/C) — `Codeforces` `1800` — solve all easy then hard under time — **(stretch)** — sort by time; try every “last mandatory” cutoff (not the same as 978G)
- [ ] [Salary Changing](https://codeforces.com/problemset/problem/1251/D) — `Codeforces` `1900` — binary-search median salary + greedy assign — **(stretch)** — force `≥ mid` on enough people, dump minimum elsewhere
- [ ] [Case of Fugitive](https://codeforces.com/problemset/problem/555/B) — `Codeforces` `2000` — match bridges to island gaps — **(stretch)** — sort gaps & bridges; multiset `lower_bound` assign tightest fit
- [ ] [TV Shows](https://codeforces.com/problemset/problem/1061/D) — `Codeforces` `2000` — reuse TVs with residual life — **(stretch)** — multiset of free TVs by expiry; buy new only when none fit
- [ ] [Pairs of Segments](https://codeforces.com/problemset/problem/1841/D) — `Codeforces` `2000` — greedily pair intersecting intervals — **(stretch)** — sort by end; when a conflict appears, kill the farther-reaching partner
- [ ] [Money Buys Less Happiness Now](https://codeforces.com/problemset/problem/1974/G) — `Codeforces` `2000` — reverse-day heap schedule — **(stretch)** — process days backward; keep affordable happiness in a max-heap, refund when broke
- [ ] [Portals](https://codeforces.com/problemset/problem/1271/D) — `Codeforces` `2100` — reverse greedy castle capture — **(stretch)** — CM ceiling; defend with portals by reclaiming best unused troops from the past
- [ ] [The Queue](https://codeforces.com/problemset/problem/767/B) — `Codeforces` `2100` — pick arrival to minimize wait — **(stretch)** — scan service gaps before closing; one-pass scheduling arithmetic

## Must-internalize checklist

- **n=2 exchange → comparator:** expand the objective for adjacent `i,j`; the sign of `Δ` after a swap is the sort key (Stas: sort by `b−a`). If the comparator is not a total order, the greedy is wrong.
- **Reverse-from-deadline:** when “once available, always available,” process time backward and always take the best live job (Portals / Money Buys / USACO milk-scheduling pattern).
- **BS + greedy check:** guess time/cost/`mid`; simulate a clear greedy (assign hardest constraints first, dump remainder cheaply). Used in Delivery Dilemma, Schedule Management, Exams, Salary Changing.
- **Available-pool + earliest exit:** keep jobs that have started in a min-heap of deadlines; on idle, jump to the next arrival (Printing Machine). Do not simulate every timestamp to `10^18`.
- **Gap / resource reuse:** Tape = total length − largest `k−1` gaps; TV Shows / Two TVs = multiset of free end-times; Fugitive = sorted gaps matched to bridges via `lower_bound`.
- **Huffman / merge cost:** Stick Divisions — repeatedly combine two smallest; any other merge order can be exchanged toward this without raising cost.
- **Closed forms after greedy:** Reading Books → `max(sum, 2·max)`; don’t over-simulate two pointers when the bottleneck is the single longest book.
- **Conflict pairing:** when you must remove intersecting pairs, sort by end and always resolve the earliest-ending conflict against the farthest intruder (Pairs of Segments).

## Where it appears in OAs / interviews

- “Minimize cost to reach average grade / median hire salary” → deficit fill or BS-on-median + greedy assign (Vanya / Salary Changing family).
- “k servers / 2 machines / reusable licenses for intervals” → sort by start/end + multiset of free end times (Two TVs → TV Shows; OA Meeting-Rooms II variant).
- “Jobs with release time & deadline, one machine” → PQ of earliest deadlines among released jobs (Printing Machine / classic single-machine scheduling).
- “Buy with bulk discount / 2-for-1 once bill passes T” → two-pointer or reverse spend unlocked by expensive items (PriceFixed) — common ecommerce-flavored OA twist.
