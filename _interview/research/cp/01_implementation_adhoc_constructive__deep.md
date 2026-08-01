# 01 — Implementation, Ad-hoc & Constructive (Depth Pass)

**Placement value:** High (Second ladder for post-basics CF fluency — the “any valid construction / find the invariant” skill that separates green from cyan–blue in contests and still shows up as OA twist questions).
**Prereq topics:** Arrays, Strings, Prefix sums, Basic greedy, Parity / XOR intuition, Finished the standard Implementation & Constructive ladder
**Pattern in one paragraph:** Depth-pass constructive/ad-hoc problems rarely need fancy DS. You win by discovering a **small certificate** (parity, first vs last, max frequency gap, degree ≥ 3 vertex, Hamming-1 candidate) and then **building the simplest object that meets it** — zig-zag permutations, powers-of-two arrays, two RBS from a 0/1 mask, MEX placements, difference-array rewrites. Recognize them when the statement says “construct any”, “minimum length sequence”, or “prove impossible”; constraints usually allow O(n log n) or O(n·alphabet), not heavy algorithms.

**Non-obvious tricks (internalize):**
1. “No subset sums to S/2” → dump almost-all 1s and one big leftover (Game With Array).
2. Sum can drop by ≤50% → replace each aᵢ with nearest power of two (Find The Array).
3. Prefix-sum collision → insert a cut / reset the running sum set (Non-zero Segments).
4. Tree edge labels / MEX path → put small labels on a high-degree vertex’s edges (Path-etic MEXs).
5. XOR+sum reconstruct → length ≤ 3 always; cases on u⊕s and bit carries (Ehab the Xorcist).
6. Ops `aᵢ −= i·x`, `aⱼ += i·x` → mass moves in multiples of indices; gather then redistribute (Make Them Equal).
7. Color digraph edges with few colors ↔ chromatic number of conflict = 1 or 2 by directed-cycle parity (Coloring Edges).

## Ladder (easy -> hard, ~25 problems)
- [ ] [Game With Array](https://codeforces.com/problemset/problem/1355/D) — `Codeforces` `1400` — constructive / subset-sum dodge — **(core)** canonical “force no half-sum” construction; OA-style case split on S≥2N.
- [ ] [Find The Array](https://codeforces.com/problemset/problem/1463/B) — `Codeforces` `1400` — bitmasks / constructive — **(core)** nearest power-of-two rewrite under a sum bound; reusable CF observation.
- [ ] [Element Extermination](https://codeforces.com/problemset/problem/1375/C) — `Codeforces` `1400` — constructive / invariant — **(core)** reduces to `a[1] < a[n]`; teaches “simulate mentally, not literally.”
- [ ] [Bracket Coloring](https://codeforces.com/problemset/problem/1837/D) — `Codeforces` `1400` — RBS / constructive — **(core)** color by sign of balance; 1 vs 2 colors from global regularity.
- [ ] [Phoenix and Towers](https://codeforces.com/problemset/problem/1515/C) — `Codeforces` `1400` — greedy constructive — **(core)** always assign next block to current shortest tower (set/heap); height-gap ≤ x proof.
- [ ] [Omkar and Baseball](https://codeforces.com/problemset/problem/1372/C) — `Codeforces` `1500` — constructive / segments — **(core)** answer is 0/1/2 from the single unsorted contiguous segment pattern.
- [ ] [Binary String Reconstruction](https://codeforces.com/problemset/problem/1352/F) — `Codeforces` `1500` — constructive — **(core)** stitch runs from (n0,n1,n2) pair counts; careful with the n1=0 edge.
- [ ] [Non-zero Segments](https://codeforces.com/problemset/problem/1426/D) — `Codeforces` `1500` — prefix sums / constructive — **(core)** set of seen prefixes; on repeat, cut and restart — OA-transferable.
- [ ] [Sage's Birthday (hard version)](https://codeforces.com/problemset/problem/1419/D2) — `Codeforces` `1500` — zig-zag constructive — **(core)** small/large interleaving to maximize local minima; binary-search count optional.
- [ ] [Ehab and Path-etic MEXs](https://codeforces.com/problemset/problem/1325/C) — `Codeforces` `1500` — tree labeling — put 0,1,2 on edges of a deg≥3 vertex (else path ends); maximises path MEXs.
- [ ] [Special Permutation](https://codeforces.com/problemset/problem/1352/G) — `Codeforces` `1600` — constructive permutation — **(core)** build with consecutive diffs in {2,3,4}; impossibility for n≤3.
- [ ] [Ehab and Prefix MEXs](https://codeforces.com/problemset/problem/1364/C) — `Codeforces` `1600` — MEX constructive — **(core)** when aᵢ increases, place missing values; fill rest with a safe unused.
- [ ] [Balance the Bits](https://codeforces.com/problemset/problem/1503/A) — `Codeforces` `1600` — double RBS — **(core)** two bracket strings from a 0/1 mask; parity of zeros + leading/trailing ones.
- [ ] [Grid-00100](https://codeforces.com/problemset/problem/1371/D) — `Codeforces` `1600` — matrix constructive — place k ones on wrapped diagonals; row/col sums differ by ≤1.
- [ ] [D - Non-decreasing](https://atcoder.jp/contests/abc081/tasks/arc086_b) — `AtCoder` `ARC086 D / ~1600 CF-eq` — operation constructive — multiply-by-2 / add-neighbor moves to force sorted; direction choice from max |aᵢ|.
- [ ] [Ehab the Xorcist](https://codeforces.com/problemset/problem/1325/D) — `Codeforces` `1700` — XOR constructive — **(stretch)** build shortest array with given XOR & sum; length 1/2/3 casework.
- [ ] [Helping the Nature](https://codeforces.com/problemset/problem/1700/C) — `Codeforces` `1700` — diff-array constructive — **(stretch)** turn range ±1 ops into prefix/suffix fixes; count from difference array.
- [ ] [Pinkie Pie Eats Patty-cakes](https://codeforces.com/problemset/problem/1393/C) — `Codeforces` `1700` — frequency constructive — **(stretch)** answer `⌊(n−cnt_max)/(f−1)⌋ − 1` with `f` = max freq, `cnt_max` = #values at that freq.
- [ ] [Extreme Subtraction](https://codeforces.com/problemset/problem/1442/A) — `Codeforces` `1800` — diff-array / invariant — **(stretch)** prefix↓ + suffix↓ ops ↔ non-increasing positive difference check.
- [ ] [Diane](https://codeforces.com/problemset/problem/1554/D) — `Codeforces` `1800` — string constructive — **(stretch)** every substring occurs odd times → `a…a + b(+c) + a…a` (odd+even run of `a`).
- [ ] [Edge Weight Assignment](https://codeforces.com/problemset/problem/1338/B) — `Codeforces` `1800` — tree XOR constructive — **(stretch)** min colors = 1 or 3 from leaf-parity; max = n−1−(extra leaf edges at same vertex).
- [ ] [A/B Matrix](https://codeforces.com/problemset/problem/1360/G) — `Codeforces` `1900` — matrix constructive — **(stretch)** cyclic column shifts of a row with a ones; existence via `n·a = m·b`.
- [ ] [Replace by MEX](https://codeforces.com/problemset/problem/1375/D) — `Codeforces` `1900` — MEX operations — **(stretch)** sort via ≤2n MEX placements; park n then fix positions 0..n−1.
- [ ] [Make Them Equal](https://codeforces.com/problemset/problem/1416/B) — `Codeforces` `2000` — constructive ops — **(stretch)** two-phase: gather total sum to index 1, redistribute multiples of i; impossible if sum ∤ n.
- [ ] [Coloring Edges](https://codeforces.com/problemset/problem/1217/D) — `Codeforces` `2100` — graph constructive — **(stretch)** 1 color if DAG, else 2 (back-edge vs tree-edge by DFS timestamp).

## Must-internalize checklist (5-10 bullets)
- Always hunt an **invariant / certificate** before coding a simulation (first vs last, parity, sum mod, max frequency).
- Prefer **canonical skeletons**: all-1s + leftover, powers of two, zig-zag permute, wrapped diagonals, two RBS twins.
- Prefix-sum sets, difference arrays, and MEX-placement loops are the “DS” of constructive — know them cold.
- Tree/path label problems: concentrate extreme labels on a **high-degree** or **endpoint** edge set.
- XOR/sum and bit constructions: enumerate tiny lengths (1–3) and bit-disjoint splits.
- Matrix fill: equalize row/col loads via cyclic shifts; check global `n·a = m·b` before building.
- When ops are reversible, rephrase as “reach sorted / zero / equal” and count the rewritten form, don’t simulate each op.

## Where it appears in OAs / interviews
- **“Construct any array/string under constraints”** (Google/Meta phone screens): often the Game-With-Array or Balance-the-Bits pattern — existence check + one simple builder.
- **Prefix-sum / cut problems** (Amazon OA variants): “split so no subarray sums to 0” ≡ Non-zero Segments.
- **Scheduling / load balance** (Microsoft-style): Phoenix and Towers / Grid-00100 — always give next job to the lightest bin.
- **Graph orientation / coloring twists** (harder onsite): Coloring Edges-style “1 or 2 labels depending on cycles” without naming the theorem.
