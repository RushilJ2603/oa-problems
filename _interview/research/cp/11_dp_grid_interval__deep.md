# 11 — DP II: Grid DP & Interval DP (Depth Pass)

**Placement value:** High — post-Striver second wave: CF/AtCoder/CSES packings of path grids, 2×n tilings/columns, and `dp[l][r]` merges that OAs still reuse under contest wrappers.
**Prereq topics:** Base Grid & Interval DP ladder (paths, MCM/slimes, deque games, Zuma/Clear the String), prefix sums, basic combinatorics (`nCr` mod p) for sparse-grid counting.
**Pattern in one paragraph:** Same engines as the base topic — `dp[r][c]` on grids and length-ordered `dp[l][r]` on arrays/strings — but statements hide the template: 2-row / column / tiling states, lex-min frontiers, sparse obstacle path counts via binomials, flood-fill / bracket / fence recursions, matching people↔positions, or “compress runs then interval-DP.” Recognize it when moves stay right/down (or along a 2×n strip), when only contiguous segments matter, or when cost/ways on `[l,r]` depend only on strictly smaller intervals.

## Technique notes (non-obvious)
- Flood Fill: first compress equal-color runs; then `dp[l][r]` = min recolors to make run-segment monochrome. Matching endpoints often let you “absorb” a side cheaper than painting from scratch — start-square choice folds into which run you grow from.
- Painting Fence: recurse on unfinished `[L,R]` above height `h`. Either pay `(R−L+1)` vertical strokes, or paint one horizontal layer and split into contiguous unpainted subsegments — classic “horizontal vs vertical” branch, not MCM-for-k.
- Coloring Brackets: only *matching* pairs get colors; state is interval plus colors of the outer pair. Transitions color the outer pair then independently solve the inside and the sibling intervals after the match.
- Sparse Grid 2 / binomial paths: with huge `H,W` and few walls, `paths((r1,c1)→(r2,c2)) = C(Δr+Δc, Δr)`. Sort walls; `dp[i]` = ways to first hit wall `i` (subtract paths that hit an earlier wall) — inclusion on the obstacle DAG.
- Empty String: when pairing `s[i]` with equal `s[k]`, empty `[i+1,k−1]` before the pair, then empty `[k+1,j]`; multiply by binomials that interleave the two emptying sequences (pair-removals commute across independent halves).
- Armchairs / ordered matching: people and empty chairs on a line — `dp[i][j]` = cost placing first `i` people into first `j` chairs (chair `j` unused, or person `i` sits there). Monotone structure, not bipartite matching flow.
- Paparazzi: `dp[i]` = best photos ending at celebrity `i`; edge `j→i` exists iff time gap covers Manhattan — DAG DP on points sorted by time, not a full grid walk.
- Minimal Grid Path: at manhattan step `t`, keep only cells still compatible with the lexicographically best prefix so far; take the min letter among candidates, discard the rest — frontier shrinks, no `O(n²)` string DP.

## Ladder (easy -> hard, 22 problems)
- [ ] [Basketball Exercise](https://codeforces.com/problemset/problem/1195/C) — `Codeforces` `1400` — 2-row grid pick DP — **(core)** choose/skip heights from two rows without consecutive same-row picks
- [ ] [a-Good String](https://codeforces.com/problemset/problem/1385/D) — `Codeforces` `1500` — divide-and-conquer on intervals — **(core)** power-of-two “c-good” string; recurse left/right halves + change-cost
- [ ] [Nikita and string](https://codeforces.com/problemset/problem/877/B) — `Codeforces` `1500` — 3-block string DP — **(core)** maximize `a*b*a*` subsequence via prefix counts / small DP
- [ ] [Maximum Submatrix 2](https://codeforces.com/problemset/problem/375/B) — `Codeforces` `1600` — 2D ones histogram — **(core)** per-row consecutive-1 heights, then sort/scan for largest all-1 submatrix
- [ ] [Counting Towers](https://cses.fi/problemset/task/2413) — `CSES` `DP` — 2×n tiling DP — **(core)** fused vs separate top cells; precompute to `1e6`
- [ ] [Rectangle Cutting](https://cses.fi/problemset/task/1744) — `CSES` `DP` — 2D cut interval DP — **(core)** `dp[a][b]` min cuts into squares; try every first horizontal/vertical cut
- [ ] [Edit Distance](https://cses.fi/problemset/task/1639) — `CSES` `DP` — classic 2D string table — **(core)** insert/delete/replace grid; OA/interview staple in contest form
- [ ] [Barcode](https://codeforces.com/problemset/problem/225/C) — `Codeforces` `1700` — column DP on grid — **(core)** paint each column mono; track `#` of groups of consecutive same-color columns
- [ ] [Bicolorings](https://codeforces.com/problemset/problem/1051/D) — `Codeforces` `1700` — 2×n coloring DP — **(core)** count colorings with exactly `k` same-color adjacent pairs
- [ ] [Armchairs](https://codeforces.com/problemset/problem/1525/D) — `Codeforces` `1800` — ordered matching DP — **(core)** seat `1`s into `0` chairs minimizing Σ|pos|; sequence DP not flow
- [ ] [Explorer Space](https://codeforces.com/problemset/problem/1517/D) — `Codeforces` `1800` — grid k-step return — **(core)** min weight closed walk of length `k` from each cell; parity / layer DP
- [ ] [Grid Puzzle](https://codeforces.com/problemset/problem/1990/D) — `Codeforces` `1800` — strip covering DP — cover `1` cells on 2×n with tromino-like ops; process columns left→right
- [ ] [Colored Rectangles](https://codeforces.com/problemset/problem/1398/D) — `Codeforces` `1800` — 3-sequence merge DP — pick pairs from three sorted RGB piles; `dp[i][j][k]` on remaining prefixes
- [ ] [Flood Fill](https://codeforces.com/problemset/problem/1114/D) — `Codeforces` `1900` — interval DP on color runs — **(core)** USACO Guide staple; min recolors to one color
- [ ] [Coloring Brackets](https://codeforces.com/problemset/problem/149/D) — `Codeforces` `1900` — bracket interval + colors — **(stretch)** color matching pairs with adjacency constraints; count ways mod 1e9+7
- [ ] [Painting Fence](https://codeforces.com/problemset/problem/448/C) — `Codeforces` `1900` — recursive horizontal/vertical — **(stretch)** min strokes; split after painting a height layer
- [ ] [Palindromic characteristics](https://codeforces.com/problemset/problem/835/D) — `Codeforces` `1900` — k-palindrome DP — **(stretch)** `dp[l][r][k]` / layer counts of palindromic substrings of degree ≥k
- [ ] [Empty String](https://cses.fi/problemset/task/1080) — `CSES` `DP` — interval ways to empty — **(stretch)** USACO Guide; pair equal ends + binomial interleaving
- [ ] [Minimal Grid Path](https://cses.fi/problemset/task/3359) — `CSES` `DP` — lex-min right/down path — **(stretch)** maintain compatible frontier per diagonal; pick min letter each step
- [ ] [The Hard Work of Paparazzi](https://codeforces.com/problemset/problem/1427/C) — `Codeforces` `2000` — timed grid DAG DP — **(stretch)** max photos under Manhattan+time feasibility between celebrities
- [ ] [Grid 2](https://atcoder.jp/contests/dp/tasks/dp_y) — `AtCoder` `EDPC Y` — sparse obstacle path count — **(stretch)** Educational DP sequel to Grid 1; binomials + obstacle DP
- [ ] [Recovering BST](https://codeforces.com/problemset/problem/1025/D) — `Codeforces` `2100` — interval BST + gcd — **(stretch)** `can[l][r]` / left-right rootability; edges when `gcd>1`

## Must-internalize checklist (5-10 bullets)
- Write length-ordered interval loops (`len`, then `l`, set `r=l+len-1`) and know when to add a split `k` vs only endpoint transitions.
- Compress equal runs before Flood-Fill-style interval DP; never interval-DP the raw `n=5000` array without RLE when runs dominate.
- 2×n / column DPs: state is “configuration of the last column” (colors, fused/separate, group count) — not a full `H×W` table.
- Sparse large grids: precompute factorial/invfactorial; path counts are binomials; DP only on the obstacle list.
- Ordered matching on a line (`Armchairs`): one pointer for people, one for seats — `O(#people · #chairs)`.
- Bracket/fence recursions: identify the *canonical* outer structure (matching pair / height layer) before writing transitions.
- Lex-min / multi-criteria grid paths: advance a frontier of still-optimal cells; don’t store full path strings in DP.
- Always check `n≤400/500` ⇒ `O(n³)` interval OK; `n≤5000` ⇒ need `O(n²)` after compression or endpoint-only transitions.

## Where it appears in OAs / interviews
- **2-row / strip games:** “Pick from two rows of heights without consecutive same-row” → Basketball Exercise; common OA recoloring of path DP.
- **Min operations to unify a segment:** “Recolor connected same-value components” / “paint fence with horizontal or vertical strokes” → Flood Fill / Painting Fence interview variants.
- **Seat assignment / taxi pickup on a line:** “Move people to empty seats minimizing total |Δ|” → Armchairs (sequence DP disguised as matching).
- **Edit / align two strings:** Edit Distance table is still the OA default for “grid-shaped” DP interviews; contest form is CSES, not LeetCode.
