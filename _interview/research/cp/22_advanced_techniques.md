# 22 — Advanced CP techniques: game theory, matrix expo, MITM, ternary search, sqrt / Mo

**Placement value:** Medium — rarely the literal OA template, but Nim-XOR / “nth term of recurrence” / “n≤40 subset sum” / unimodal optimization show up in harder screens; primarily Candidate Master rating-builders Striver never covers.
**Prereq topics:** Binary exponentiation, bitmasks & subset enumeration, binary search (incl. on answer), basic DP, XOR / bit ops, offline queries intuition (from range-query topic)
**Pattern in one paragraph:** These are five “recognize the shape → apply the template” CP tools. **Game theory (impartial):** terminal = lose; win if any move to a lose; multi-pile → XOR of Grundy/nimbers (`mex` of reachable). **Matrix expo:** linear recurrence / fixed-size DP transition with huge `n` → encode transition as `k×k` matrix, power in `O(k³ log n)`. **Meet-in-the-middle:** `n≤40` / `2^n` too big → split halves, enumerate `2^{n/2}`, combine with sort/hash. **Ternary search:** cost `f(x)` is unimodal (decrease then increase) on a continuous or discrete line → ternary (or BS on derivative). **Sqrt / Mo:** many offline range queries with add/remove-friendly state → sort by block, move `[L,R]` pointers in `O((n+q)√n)`.

## Ladder (easy -> hard, 27 problems)
- [ ] [Stick Game](https://cses.fi/problemset/task/1729) — `CSES` `Mathematics` — win/lose DP — CSES; first “position is W iff some move to L” drill before Nim
- [ ] [Nim Game I](https://cses.fi/problemset/task/1730) — `CSES` `Mathematics` — classic Nim XOR — **(core)** CSES / USACO Guide Game Theory; xor≠0 ⇒ first wins
- [ ] [MEX Game 1](https://codeforces.com/problemset/problem/1943/A) — `Codeforces` `1300` — MEX / game greedy — modern Div2; mex intuition without full Grundy tables
- [ ] [Everything Nim](https://codeforces.com/problemset/problem/1965/A) — `Codeforces` `1400` — Nim variant / observation — reduce pile game to a parity rule; CF-style “find the trick”
- [ ] [Nim Game II](https://cses.fi/problemset/task/1098) — `CSES` `Mathematics` — subtraction game Grundy — **(core)** CSES / USACO Guide; pile `mod (k+1)` then XOR
- [ ] [Motarack's Birthday](https://codeforces.com/problemset/problem/1301/B) — `Codeforces` `1500` — ternary on replace value — **(core)** USACO Guide Ternary; unimodal max adjacent |diff|
- [ ] [Fibonacci Numbers](https://cses.fi/problemset/task/1722) — `CSES` `Mathematics` — 2×2 matrix expo — **(core)** CSES / USACO Guide Matrix Expo / Errichto; *the* fib template mod 1e9+7
- [ ] [Stair Game](https://cses.fi/problemset/task/1099) — `CSES` `Mathematics` — stair Nim — **(core)** CSES; XOR only odd-indexed piles
- [ ] [Meet in the Middle](https://cses.fi/problemset/task/1628) — `CSES` `Advanced Techniques` — subset-sum MITM — **(core)** CSES / USACO Guide / CPH; `n≤40`, count subsets summing to `x`
- [ ] [Throwing Dice](https://cses.fi/problemset/task/1096) — `CSES` `Mathematics` — linear recurrence matrix — CSES; dice-sum recurrence powered for huge `n`
- [ ] [The Meeting Place Cannot Be Changed](https://codeforces.com/problemset/problem/780/B) — `Codeforces` `1600` — ternary on continuous line — **(core)** *the* continuous ternary classic; min time for all to meet
- [ ] [Meeting on the Line](https://codeforces.com/problemset/problem/1730/B) — `Codeforces` `1600` — ternary + time — modern Div2; unimodal with per-person delays
- [ ] [Graph Paths I](https://cses.fi/problemset/task/1723) — `CSES` `Mathematics` — adj-matrix power — **(core)** CSES / USACO Guide; `#` walks of length `k` = `(A^k)[s][t]`
- [ ] [Walk](https://atcoder.jp/contests/dp/tasks/dp_r) — `AtCoder` `DP contest R` — matrix path count — **(core)** AtCoder DP contest; `K≤10^18`, `N≤50`
- [ ] [Iterated Linear Function](https://codeforces.com/problemset/problem/678/D) — `Codeforces` `1700` — affine matrix / closed form — `f(x)=ax+b` iterated `n` times mod `m`
- [ ] [Grundy's Game](https://cses.fi/problemset/task/2207) — `CSES` `Mathematics` — mex DP Grundy — **(core)** CSES / USACO Guide; split-heap game, precompute until pattern stabilizes
- [ ] [Distinct Values Queries](https://cses.fi/problemset/task/1734) — `CSES` `Range Queries` — Mo’s / offline distinct — **(core)** CSES; Mo add/remove frequency (also last-occurrence Fenwick)
- [ ] [Maximum Subsequence](https://codeforces.com/problemset/problem/888/E) — `Codeforces` `1800` — MITM mod sum — **(core)** USACO Guide MITM; max subset sum `mod m` via two halves
- [ ] [Little Elephant and Array](https://codeforces.com/problemset/problem/220/B) — `Codeforces` `1800` — Mo’s frequency — **(core)** CF Mo classic; count values equal to their frequency on `[l,r]`
- [ ] [Xor-sequences](https://codeforces.com/problemset/problem/691/E) — `Codeforces` `1900` — matrix on graph — USACO Guide Matrix Expo; transitions when `popcount(a_i⊕a_j)` odd
- [ ] [A Lot of Games](https://codeforces.com/problemset/problem/455/B) — `Codeforces` `1900` — trie Grundy — **(stretch)** win/lose on string trie + “can force”
- [ ] [Weakness and Poorness](https://codeforces.com/problemset/problem/578/C) — `Codeforces` `2000` — ternary + kadane — **(stretch)** cp-algorithms Ternary classic; min max |subarray sum| after subtract `x`
- [ ] [Wet Shark and Blocks](https://codeforces.com/problemset/problem/621/E) — `Codeforces` `2000` — digit DP × matrix — **(stretch)** count numbers with remainder `x` after `b` blocks
- [ ] [Cut and Stick](https://codeforces.com/problemset/problem/1514/D) — `Codeforces` `2000` — Mo / majority — **(stretch)** mode-frequency on ranges; Mo or “>len/2” observation
- [ ] [Magic Gems](https://codeforces.com/problemset/problem/1117/D) — `Codeforces` `2100` — recurrence matrix — **(stretch)** ways to tile length `n` with 1s and `m`-blocks
- [ ] [Xor-Paths](https://codeforces.com/problemset/problem/1006/F) — `Codeforces` `2100` — grid MITM — **(stretch)** USACO Guide MITM; meet at diagonal, XOR halves
- [ ] [Game of Stones](https://codeforces.com/problemset/problem/768/E) — `Codeforces` `2100` — constrained Grundy — **(stretch)** USACO Guide; unique moves per pile → precomputed nimbers + XOR

## Must-internalize checklist (5-10 bullets)
- Impartial game → Grundy: `g(s)=mex{g(t): s→t}`; sum of independent games = XOR of Grundies; `g=0` is second-player win.
- Standard Nim: `g(pile)=size`; subtraction-`{1..k}`: `g(n)=n mod (k+1)`.
- Matrix expo template: build transition `M` so `state_{i+1}=M·state_i`; answer from `M^n · state_0` in `O(k³ log n)` (always mod).
- Path counts / fixed-size DP: adjacency (or DP-transition) matrix raised to `k`; AtCoder DP `R` / CSES Graph Paths are the same idea.
- MITM: split `n` in half, enum `2^{n/2}` subset sums (or XORs), sort one side, binary-search complements; complexity `O(n·2^{n/2})`.
- Ternary search: only on **strictly** unimodal `f`; for floats run ~100–200 iters; discrete: compare `f(m)` vs `f(m+1)` and shrink.
- Mo’s algorithm: block size `~√n` (or `n/√q`); sort by `(L/B, R)`; maintain `add(i)` / `remove(i)` updating the answer in `O(1)` or `O(log)`.
- Sqrt blocking intuition: precompute per-block aggregates; full blocks `O(√n)`, edges brute; when Mo’s “add/remove” isn’t natural, prefer blocks / rebuild.

## Where it appears in OAs / interviews
- “Two players take objects from piles / subtract a set of sizes — who wins?” → Nim XOR or short Grundy table (CSES Nim I/II style).
- “Compute the n-th Fibonacci / number of ways for length `10^18`” → matrix exponentiation (fib / tiling / graph walks).
- “Array size ≤40, count subsets with sum = X” → meet-in-the-middle (CSES MITM), not `2^n` DP.
- “Minimize the maximum of a unimodal cost over a real parameter” → ternary search (Meeting Place / Motarack family).
