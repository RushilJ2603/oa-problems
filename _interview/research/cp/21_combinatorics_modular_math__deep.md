# 21 — Combinatorics & Modular Math — Depth Pass

**Placement value:** High — second wave after CSES fact/invFact / stars-and-bars / Catalan; these are the CF Div2 C–D “count under constraints + mod inverse” drills that show up in harder OAs and blue→CM contests.
**Prereq topics:** Binary exponentiation, fact+invFact `nCr`, stars-and-bars, Fermat inverse; finished the standard Combinatorics & Modular Math ladder
**Pattern in one paragraph:** After Distributing Apples / Two Arrays / Beautiful Numbers, contest combo stops handing you a named sequence and hides a **rewrite**: complementary count (`C(k,2)−∑C(c_i,2)`), contribution of each index as max/min (`∑ a_i·C(i,k−1)`), product of independent column/type choices, or IE on sorted-key collisions. Recognize depth-pass combo when the answer is “ways mod 998244353/1e9+7”, constraints allow `O(n)` after `O(N)` factorial precompute, or the statement mixes counting with construction / binary-search paths / gcd-constrained arrays.

## Ladder (easy -> hard, 25 problems)

- [ ] [Pocket Book](https://codeforces.com/problemset/problem/152/C) — `Codeforces` `1400` — product of column alphabets — **(core)** per column count distinct letters; answer `∏ dist[j]` mod `1e9+7`; OA “independent choices”
- [ ] [Minimum number of steps](https://codeforces.com/problemset/problem/804/B) — `Codeforces` `1400` — right-to-left `a`/`b` doubling — **(core)** each `a` adds current `b`-count then doubles it (`cnt_b = 2·cnt_b`); modular chain-reaction count
- [ ] [Ball in Berland](https://codeforces.com/problemset/problem/1475/C) — `Codeforces` `1400` — complementary pair counting — **(core)** `C(k,2) − ∑ C(boy_c,2) − ∑ C(girl_c,2)`; classic “total − colliding”
- [ ] [Sakurako's Box](https://codeforces.com/problemset/problem/2008/F) — `Codeforces` `1400` — E[product] via inverses — **(core)** `∑_{i<j} a_i a_j / C(n,2)` = `((∑a)^2−∑a^2)/2 · inv(C(n,2))`
- [ ] [Kyoya and Colored Balls](https://codeforces.com/problemset/problem/553/A) — `Codeforces` `1500` — sequential multinomial — **(core)** (USACO Guide Combo) place colors ending with last color fixed; `∏ C(pref+c_i−1, c_i−1)`
- [ ] [Ayoub and Lost Array](https://codeforces.com/problemset/problem/1105/C) — `Codeforces` `1500` — DP on residues mod 3 — **(core)** count `[l,r]` ≡0/1/2; `dp[i][r]` multiply by residue frequencies
- [ ] [Alice and the List of Presents](https://codeforces.com/problemset/problem/1236/B) — `Codeforces` `1500` — `(2^n−1)^m` — **(core)** each box type chooses nonempty friend-subset; independent types → modular pow
- [ ] [Cyclic Permutations](https://codeforces.com/problemset/problem/1391/C) — `Codeforces` `1500` — `n! − 2^{n−1}` — **(core)** total perms minus “connected via successive maxima” bad set; closed-form factorial vs power
- [ ] [Binary Search](https://codeforces.com/problemset/problem/1436/C) — `Codeforces` `1500` — reconstruct BS path counts — **(core)** simulate BS on value `x`; need `L` larger and `S` smaller on path → `C(n−x,L)·C(x−1,S)·(n−1−L−S)!`
- [ ] [Jury Meeting](https://codeforces.com/problemset/problem/1569/C) — `Codeforces` `1500` — perms with unique max adjacency — **(core)** if `max−second > 1` → 0; else `n! / (cnt_second+1)` style with fact/inv
- [ ] [E - Colorful Blocks](https://atcoder.jp/contests/abc167/tasks/abc167_e) — `AtCoder` `ABC E (~1500–1600 CF-eq)` — ≤K adjacent same-color pairs — **(core)** `∑_{i=0}^{K} C(n−1,i)·m·(m−1)^{n−1−i}`
- [ ] [E - Max-Min Sums](https://atcoder.jp/contests/abc151/tasks/abc151_e) — `AtCoder` `ABC E (~1600 CF-eq)` — contribution as max/min — **(core)** sort; `a_i` is max in `C(i,K−1)` subsets, min in `C(n−1−i,K−1)`; OA staple
- [ ] [New Year and Permutation](https://codeforces.com/problemset/problem/1284/C) — `Codeforces` `1600` — sum of segment contributions — **(core)** `∑_{len} (n−len+1)^2 · len! · (n−len)!`; fact template + closed sum
- [ ] [Advertising Agency](https://codeforces.com/problemset/problem/1475/E) — `Codeforces` `1600` — threshold multinomial — **(core)** take top-`k` after sort; if value `v` straddles cutoff, `C(freq[v], need)`
- [ ] [F - Many Many Paths](https://atcoder.jp/contests/abc154/tasks/abc154_f) — `AtCoder` `ABC F (~1600–1700 CF-eq)` — grid paths rectangle sum — **(core)** `#paths (0,0)→(x,y)=C(x+y,x)`; 2D prefix via hockey-stick on binomials
- [ ] [E - NEQ](https://atcoder.jp/contests/abc172/tasks/abc172_e) — `AtCoder` `ABC E (~1700 CF-eq)` — IE on two sequences — **(core)** `P(M,N)^2` total injections; subtract positions with `a_i=b_i` via IE `∑ (−1)^k C(N,k)·P(M−k,N−k)^2`
- [ ] [Bargain](https://codeforces.com/problemset/problem/1422/C) — `Codeforces` `1700` — digit contribution — **(stretch)** for each digit, count how many deletions leave it in place · place-value; prefix/suffix powers of 10
- [ ] [Close Tuples (hard version)](https://codeforces.com/problemset/problem/1462/E2) — `Codeforces` `1700` — `C(cnt,m−1)` windows — **(stretch)** upgrade of E1: for each left endpoint, `C(#in [a_i, a_i+k], m−1)`; two pointers + fact
- [ ] [Number Of Permutations](https://codeforces.com/problemset/problem/1207/D) — `Codeforces` `1800` — IE on sorted keys — **(stretch)** `n! − (#sorted by a) − (#sorted by b) + (#sorted by both)`; inclusion on bad orders
- [ ] [The Intriguing Obsession](https://codeforces.com/problemset/problem/869/C) — `Codeforces` `1800` — bridges between 3 groups — **(stretch)** ways to add edges of length 1–2 between three colored islands; product of `∑ C(a,i)C(b,i)·i!·2^i`-style sums
- [ ] [Count The Blocks](https://codeforces.com/problemset/problem/1327/E) — `Codeforces` `1800` — digit-block contribution — **(stretch)** for each length `len`, count blocks of that length over all `0…10^n−1`; closed form with `10^{n−len}` and `81/9` factors
- [ ] [Rescue Nibel!](https://codeforces.com/problemset/problem/1420/D) — `Codeforces` `1800` — sweep + `C(active,k)` — **(stretch)** sort events; on each new segment opening with `≥k` active, add `C(active−1, k−1)`
- [ ] [Count GCD](https://codeforces.com/problemset/problem/1750/D) — `Codeforces` `1800` — gcd-forced array fill — **(stretch)** fix `gcd=a_1`; each next `a_i` must be multiple of `g` dividing previous pattern → count via factor IE / multiples in `[1,m]`
- [ ] [Shaass and Lights](https://codeforces.com/problemset/problem/294/C) — `Codeforces` `1900` — gaps × `2^{len−1}` — **(stretch)** place remaining off-lights into gaps between ons; multinomial of gap sizes times `2^{gap−1}` per internal gap
- [ ] [Directed Roads](https://codeforces.com/problemset/problem/711/D) — `Codeforces` `1900` — functional graph cycles — **(stretch)** each node outdeg 1; for cycle len `c` multiply `(2^c−2)`, trees off-cycle free `2^{size}`; CM-band combo×graphs

## Must-internalize checklist (technique notes)

- **Complementary counting:** prefer `total − invalid` when invalid partitions by a key (`Ball in Berland`, `Number Of Permutations` IE on sort-keys).
- **Contribution / linearity on subsets:** rewrite `∑_S f(S)` as `∑_i a_i · (#S where i is max/min)` — Max-Min Sums; same idea as digit place-value in Bargain / Count The Blocks.
- **Sequential placement product:** when order of types is forced (last color / last group), answer collapses to `∏ C(prefix+c−1, c−1)` (Kyoya) — not a single multinomial.
- **Residue / constraint DP × count:** pre-count how many values fall in each residue class, then DP the product (Ayoub mod 3); same pattern as “≤K special adjacent pairs” (ABC167E).
- **Sweep with live `C(active,k)`:** openings/closings on a line; add `C(active−1,k−1)` when a new interval starts (Rescue Nibel!).
- **Hockey-stick / path prefix:** `∑_{i=a}^{A} ∑_{j=b}^{B} C(i+j,i) =` difference of `C(·,·)` via `∑ C(i+r,i)=C(n+r+1,n)` (Many Many Paths).
- **IE for labeled injections:** two sequences with forbidden equalities → `∑ (−1)^k C(n,k) P(m−k,n−k)^2` (NEQ); sign alternates on fixed “bad” positions.
- **Gap multinomials:** lights/segments already placed split the line into gaps; answer `multinomial(gap sizes) · ∏ 2^{gap−1}` for internal gaps (Shaass and Lights) — same family as “choose positions then orient”.

## Where it appears in OAs / interviews

- **“Number of ways to assign / product over independent groups mod 1e9+7”** — Pocket Book / Alice Presents / Kyoya; FAANG OA counting with modular pow.
- **“Sum of (max−min) over all k-subsets”** — Max-Min Sums contribution rewrite; common quant/OA twist on plain `nCr`.
- **“Count pairs of pairs with no shared endpoint”** — Ball in Berland complementary `C(k,2)−∑C(c,2)`; disguised graph matching / booking problems.
- **“Expected product / expected score of a random pair”** — Sakurako’s Box; forces `((∑a)^2−∑a^2)·inv(2)·inv(C(n,2))` rather than nested loops.
