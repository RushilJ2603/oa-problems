# 22 — Advanced CP techniques: game / matrix / MITM / ternary / sqrt·Mo (Depth Pass)

**Placement value:** Medium — second ladder after CSES Nim/Fib/MITM/Mo and the Meeting-Place / Magic-Gems classics; these are the Div2 C–E drills that hide Grundy formulas, min-plus matrices, half-enumeration with extras, discrete unimodal costs, and block/residue sqrt rather than announcing the template.
**Prereq topics:** Finished the standard Advanced Techniques ladder (Nim XOR, fib/path matrix expo, CSES MITM, continuous ternary, basic Mo add/remove); binary expo; bitmasks; prefix XOR
**Pattern in one paragraph:** After Stick/Nim/Fib/Meet-in-the-Middle/Meeting-Place/Little-Elephant, contests stop naming the tool. Games become “delete a divisor / take leaves / XOR of segment piles / only care about the MSB with odd count.” Linear recurrences become digit automata, forbidden-pair string graphs, or **min-plus** path products. MITM grows factorials or base-`w` digits. Unimodal costs sit on integer heights / array medians. Offline range asks want odd-parity frequencies or “jump by `k`” chains that scream block by residue. Spot them when `n≤40` / `k≤10^18` / “who wins with optimal play” / unimodal cost / `q·√n` offline.

**Non-obvious tricks (internalize):**
1. XOR of a contiguous range of pile sizes: `pref(r)⊕pref(l−1)` where `pref(n)=⊕_{i=1}^n i` has an `O(1)` closed form from `n mod 4` (Industrial Nim) — never loop to `10^18`.
2. “Remove one coin from each of several nonempty heaps” is **not** Nim: first wins iff some heap has size `>1` (CSES Another Game) — multi-select changes the Sprague–Grundy decomposition.
3. Bit-greedy impartial games (GameGame): only the highest bit where the count of `1`s is odd matters; lower bits are forced replies.
4. Min-plus matrix expo (Graph Paths II): same binary expo skeleton, but `(A⊗B)[i][j]=min_k A[i][k]+B[k][j]`; identity is `0` on diagonal / `+∞` elsewhere.
5. Digit / string automata → matrix: state = last digit (Add One) or last character (Decoding Genome); one step = multiply by the fixed transition matrix, then `M^n`.
6. MITM extras: Anya-and-Cubes splits `n≤25` and tracks how many factorials were used on each half; Vanya-and-Scales is balanced base-`w` (“digits” in `{−1,0,1}`), not subset-sum.
7. Discrete unimodal: prefer **binary search on the derivative** — compare `f(m)` vs `f(m+1)` and shrink (Devu / Maximize! / Restorer); float ternary only when the domain is continuous.
8. Sqrt by parameter: for jumps `i→i+k+a[i]`, if `k≥√n` simulate; if `k<√n` precompute per residue class / rebuild blocks (Array Queries / Cowavans). Mo: sort `(L/B,R)`, maintain `odd_count` or freq→answer in `O(1)`.

## Ladder (easy -> hard, 25 problems)

- [ ] [Number Game](https://codeforces.com/problemset/problem/1370/C) — `Codeforces` `1400` — prime / parity game — **(core)** post-Nim “find the rule”: `1` lose, prime → take all, even → leave odd, odd composite → leave even.
- [ ] [Tetrahedron](https://codeforces.com/problemset/problem/166/E) — `Codeforces` `1500` — 4-state linear DP / matrix — **(core)** paths of length `n` on `K4` minus self-loops; write the recurrence before matrix-ifying.
- [ ] [Add One](https://codeforces.com/problemset/problem/1513/C) — `Codeforces` `1600` — digit automaton DP — each `+1` is a 10-state transition; precompute / matrix for `m≤10^5` ops (same idea as mat-expo digit machines).
- [ ] [Game On Leaves](https://codeforces.com/problemset/problem/1363/C) — `Codeforces` `1600` — tree leaf-removal game — outcome hinges on degree of the special vertex / “star vs path” observation.
- [ ] [D - Freefall](https://atcoder.jp/contests/abc279/tasks/abc279_d) — `AtCoder` `ABC279 D (~1600 CF-eq)` — ternary on convex `A/√(x+1)+Bx` — **(core)** USACO Guide ternary sibling; integer ternary or derivative + check neighbors.
- [ ] [1-2-K Game](https://codeforces.com/problemset/problem/1194/D) — `Codeforces` `1700` — subtraction `{1,2,k}` Grundy — **(core)** period-3 unless `k%3==0`, then a longer period; forces “compute small grundy → spot cycle.”
- [ ] [Deleting Divisors](https://codeforces.com/problemset/problem/1537/D) — `Codeforces` `1700` — divisor-move game — odd → lose; odd×2^1 special; larger powers of two win — pattern from grundy, not full DP.
- [ ] [MADMAX](https://codeforces.com/problemset/problem/917/B) — `Codeforces` `1700` — graph game DP — state `(u,v,last_char)`; win if exists edge `u→x` with label `≥last` to a losing `(v,x,·)`.
- [ ] [Devu and his Brother](https://codeforces.com/problemset/problem/439/D) — `Codeforces` `1700` — discrete ternary / BS on target — **(core)** make all of `a` ≥ all of `b` by ±1 ops; cost unimodal in the threshold value.
- [ ] [Maximize!](https://codeforces.com/problemset/problem/939/E) — `Codeforces` `1800` — ternary + two pointers — **(core)** max `max−mean` over a prefix-of-sorted shape; maintain candidate multiset while searching.
- [ ] [Graph Paths II](https://cses.fi/problemset/task/1724) — `CSES` `Mathematics` — min-plus matrix expo — **(core)** twin of Graph Paths I; shortest walk with exactly `k` edges via `(min,+)` product.
- [ ] [Another Game](https://cses.fi/problemset/task/2208) — `CSES` `Mathematics` — multi-heap coin game — **(core)** CSES closer after Nim I/II; first wins iff `max(a_i)>1`.
- [ ] [F - Programming Contest](https://atcoder.jp/contests/abc184/tasks/abc184_f) — `AtCoder` `ABC184 F (~1900 CF-eq)` — subset-sum MITM — **(core)** AtCoder twin of CSES MITM; max sum `≤T` via two halves + sort/two-pointers.
- [ ] [F - Dividing Game](https://atcoder.jp/contests/abc368/tasks/abc368_f) — `AtCoder` `ABC368 F (~1900 CF-eq)` — Ω(n) as Nim heap — divide-by-divisor game → grundy = big-omega; XOR piles (cp-algorithms practice).
- [ ] [GameGame](https://codeforces.com/problemset/problem/1383/B) — `Codeforces` `1900` — bitwise Nim observation — **(core)** look at MSB with odd popcount across array; construct win/draw from that bit alone.
- [ ] [Decoding Genome](https://codeforces.com/problemset/problem/222/E) — `Codeforces` `1900` — string transition matrix — **(core)** `#` length-`n` strings with forbidden adjacent pairs = sum of `M^{n-1}` over alphabet states.
- [ ] [Robin Hood Archery](https://codeforces.com/problemset/problem/2014/H) — `Codeforces` `1900` — Mo / even frequencies — **(core)** range is “tie” iff every value appears even times; Mo on `odd_count` (or xor-hashing).
- [ ] [Thanos Nim](https://codeforces.com/problemset/problem/1147/C) — `Codeforces` `2000` — Nim with floor-half constraint — only piles equal to the global minimum matter; count of mins decides.
- [ ] [Industrial Nim](https://codeforces.com/problemset/problem/15/C) — `Codeforces` `2000` — XOR of many contiguous piles — **(core)** each factory contributes `⊕` of an interval; use `⊕_{i=0}^{n} i` closed form.
- [ ] [Array Queries](https://codeforces.com/problemset/problem/797/E) — `Codeforces` `2000` — sqrt by jump size — **(core)** `i := i+k+a[i]` until `>n`; split small-`k` (DP) vs large-`k` (simulate).
- [ ] [Anya and Cubes](https://codeforces.com/problemset/problem/525/E) — `Codeforces` `2100` — MITM + factorials — **(stretch)** USACO Guide MITM hard; halves track sum and `#` of `a_i!` used, map complements.
- [ ] [Okabe and El Psy Kongroo](https://codeforces.com/problemset/problem/821/E) — `Codeforces` `2100` — blocked strip matrix — **(stretch)** DP on height `0..h` with forbidden segments; multiply distinct segment matrices along `x`.
- [ ] [Restorer Distance](https://codeforces.com/problemset/problem/1355/E) — `Codeforces` `2100` — ternary on target height — **(stretch)** USACO Guide ternary; cost to make all pillars height `h` with add/remove/move prices is convex.
- [ ] [Time to Raid Cowavans](https://codeforces.com/problemset/problem/103/D) — `Codeforces` `2100` — sqrt residue queries — **(stretch)** offline queries `(a,b)` sum `a,a+b,a+2b,…`; group by `b`, prefix per residue when `b` small.
- [ ] [Not a Nim Problem](https://codeforces.com/problemset/problem/2004/E) — `Codeforces` `2100` — mex / prime-factor Grundy — **(stretch)** modern CM closer; `g(n)` collapses by smallest prime factor pattern, then XOR.

## Must-internalize checklist (5-10 bullets)

- Pattern → formula before DP: many CF games have `O(1)` or `O(log)` winners once you compute `g(0..32)` and spot the period / bit rule.
- Closed-form `⊕_{i=1}^n i`: values cycle every 4 — mandatory for Industrial-Nim-style segment XORs.
- Matrix checklist: states = what a “column” of DP remembers; transitions linear ⇒ fill `M`; power with `+,*` or `(min,+)` / `(max,+)` / XOR-AND as needed.
- MITM checklist: split, enum with **extra state** (count, mod, factorial uses), sort one side, two-pointers / map for complements under a budget `T` or equality.
- Unimodal on integers: BS `f(m)?f(m+1)`; prove convexity (sum of convex / second difference ≥0) before ternary.
- Mo offline: block sort, `add`/`del` update a single aggregate (`odd_cnt`, sum of `freq[x]==x`, etc.); compress values first.
- Sqrt dualism: either Mo (move `[L,R]`) **or** block/residue precompute when the query is a fixed stride / parameter `k`.
- Impartial sum: independent components → XOR of grundies; if the move can touch several heaps at once, Sprague–Grundy on single piles may **not** apply (Another Game).

## Where it appears in OAs / interviews

- **“Two players delete a divisor / take 1..k / strip leaves — who wins?”** — Number Game / 1-2-K / Deleting Divisors / Game On Leaves; interviewers want the pattern, not a game-tree search.
- **“Ways / shortest with exactly `10^18` steps on a tiny graph / digit machine”** — Tetrahedron / Decoding Genome / Graph Paths II / Add One; matrix expo disguised as “huge `n` DP.”
- **“`n≤40`, best subset under budget / with at most `k` special ops”** — Programming Contest / Anya and Cubes; say “meet-in-the-middle,” not `2^n`.
- **“Offline range: all frequencies even / jump-sum by stride `b`”** — Robin Hood Archery / Cowavans / Array Queries; Mo or sqrt blocks once `n,q∼1e5`.
