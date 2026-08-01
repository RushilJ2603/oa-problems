# 01 — Implementation, Ad-hoc & Constructive

**Placement value:** High (Tests raw coding fluency, edge-case handling, and translating logic into bug-free code—the most common reason candidates fail OAs).
**Prereq topics:** Arrays, Strings, Loops, Basic Math, Sorting
**Pattern in one paragraph:** These problems don't require advanced data structures or textbook algorithms. Instead, they require you to simulate a process, find a mathematical shortcut (ad-hoc), or build a valid configuration from scratch (constructive). You recognize them when the constraints are small enough for direct simulation, or when the problem asks for "any valid answer" and allows for a surprisingly simple greedy construction.

## Ladder (easy -> hard, ~25 problems)
- [ ] [Weird Algorithm](https://cses.fi/problemset/task/1068) — `CSES` `Introductory` — simulation — **(core)** perfect warmup for state simulation; staple in introductory assessments.
- [ ] [Repetitions](https://cses.fi/problemset/task/1069) — `CSES` `Introductory` — implementation — **(core)** foundational sliding-window / streak-counting logic for OAs.
- [ ] [Bit++](https://codeforces.com/problemset/problem/282/A) — `Codeforces` `800` — implementation — **(core)** quintessential basic parsing and state tracking.
- [ ] [Increasing Array](https://cses.fi/problemset/task/1094) — `CSES` `Introductory` — greedy — **(core)** minimal modification array problem, classic NeetCode/OA overlap.
- [ ] [Spiral Matrix](https://leetcode.com/problems/spiral-matrix/) — `LeetCode` `Medium` — matrix-implementation — **(core)** notorious OA and phone-screen filter for off-by-one errors and loop bounds.
- [ ] [Set Matrix Zeroes](https://leetcode.com/problems/set-matrix-zeroes/) — `LeetCode` `Medium` — in-place-implementation — **(core)** forces space-optimized thinking (O(1) space matrix modification).
- [ ] [Rotate Image](https://leetcode.com/problems/rotate-image/) — `LeetCode` `Medium` — matrix-math — **(core)** tests coordinate mapping and 2D array traversal mastery.
- [ ] [Move Brackets](https://codeforces.com/problemset/problem/1374/C) — `Codeforces` `1000` — greedy / constructive — **(core)** classic balance-tracking; shows up constantly in string OAs.
- [ ] [Number Spiral](https://cses.fi/problemset/task/1071) — `CSES` `Introductory` — ad-hoc math — tests finding O(1) formulas for grid patterns instead of simulating.
- [ ] [Coin Piles](https://cses.fi/problemset/task/1754) — `CSES` `Introductory` — ad-hoc math — canonical modulo/divisibility trick for game-like states.
- [ ] [Frog Jumps](https://codeforces.com/problemset/problem/1324/C) — `Codeforces` `1100` — greedy — identifying the bottleneck (max distance between 'R's); CP-31 staple.
- [ ] [Chewbacca and Number](https://codeforces.com/problemset/problem/514/A) — `Codeforces` `1200` — greedy — **(core)** string/digit manipulation avoiding leading zeros; edge-case heavy.
- [ ] [K-th Not Divisible by n](https://codeforces.com/problemset/problem/1352/C) — `Codeforces` `1200` — ad-hoc math — **(core)** extremely common OA math pattern; O(1) jump logic instead of looping.
- [ ] [Odd Selection](https://codeforces.com/problemset/problem/1363/A) — `Codeforces` `1200` — parity / math — tests exhaustive case-checking for odd/even sums (rating-builder).
- [ ] [Palindrome Reorder](https://cses.fi/problemset/task/1755) — `CSES` `Introductory` — constructive — **(core)** classic frequency-counting and symmetric string construction.
- [ ] [Phoenix and Beauty](https://codeforces.com/problemset/problem/1348/B) — `Codeforces` `1400` — constructive — **(core)** forcing periodicity; brilliant example of loose constraints in constructive algorithms.
- [ ] [Epic Transformation](https://codeforces.com/problemset/problem/1506/D) — `Codeforces` `1400` — greedy / constructive — priority-queue / frequency counting logic that maps directly to LC Hard (e.g. Task Scheduler).
- [ ] [Codeforces Subsequences](https://codeforces.com/problemset/problem/1368/B) — `Codeforces` `1500` — constructive — distributing products evenly to maximize combinations.
- [ ] [k-LCM (hard version)](https://codeforces.com/problemset/problem/1497/C2) — `Codeforces` `1600` — constructive math — reducing a general case (k>3) to a solved base case (k=3).
- [ ] [Maximum Sum on Even Positions](https://codeforces.com/problemset/problem/1373/D) — `Codeforces` `1600` — ad-hoc / dp — mapping a swap operation to a standard Kadane's maximum subarray problem.
- [ ] [Solve The Maze](https://codeforces.com/problemset/problem/1365/D) — `Codeforces` `1700` — constructive / bfs — **(stretch)** block the bad guys instead of helping the good guys; reverse-thinking.
- [ ] [Prefix Flip (Hard Version)](https://codeforces.com/problemset/problem/1381/A2) — `Codeforces` `1700` — constructive — **(stretch)** canonical two-phase string transformation using prefix reversals.
- [ ] [Carousel](https://codeforces.com/problemset/problem/1328/D) — `Codeforces` `1800` — constructive / bipartite — **(stretch)** cycle parity and coloring; beautifully combines graphs and ad-hoc logic.
- [ ] [Phoenix and Science](https://codeforces.com/problemset/problem/1348/D) — `Codeforces` `1900` — constructive / greedy — **(stretch)** bounding growth rates optimally; classic rating-builder for Div 2 C/D.
- [ ] [Directing Edges](https://codeforces.com/problemset/problem/1385/E) — `Codeforces` `2000` — constructive / toposort — **(stretch)** orienting edges in a mixed graph to avoid cycles; standard advanced pattern.

## Must-internalize checklist (5-10 bullets)
- Safely manipulating 2D grids (boundary checks, 4-way/8-way directional arrays).
- Handling strings and numbers as digit arrays, paying attention to leading zeros and parity.
- Finding the invariants (e.g., sum modulo K, parity of inversions) that never change during operations.
- Solving "does there exist" or "construct any" by reducing the problem to its most extreme or simplest valid base case (e.g. sorting, placing all 1s together).
- Avoiding O(N) simulation when an O(1) math formula or division/modulo logic dictates the exact state at step N.
- Tracing cycle bounds and avoiding off-by-one errors when processing matrices in a spiral or diagonal pattern.
- In-place modification techniques (using the first row/column as state markers).

## Where it appears in OAs / interviews
- **Grid Traversal OAs (Amazon, Microsoft):** "Given a grid of robots and obstacles, simulate their movement..." tests pure 2D implementation skills without requiring BFS/DFS.
- **Game Simulations (Citadel, Optiver, HRT):** "Two players play a game with a set of rules. Predict the winner after N turns." Often disguises a O(1) parity check or ad-hoc math trick.
- **Array / String Transformations (Google, Meta):** "Given a string, apply these replacement rules until the string stops changing..." requires finding the invariant or recognizing the string just shrinks to a known pattern.
- **Data Engineering / Pipeline OAs:** "Parse this log format and calculate the streaks of active sessions..." testing pure implementation and edge cases.
