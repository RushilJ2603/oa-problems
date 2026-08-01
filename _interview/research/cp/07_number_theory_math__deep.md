# 07 — Number Theory & Math — Depth Pass

**Placement value:** Medium-High — second wave of CF Div2 C/D number-theory after sieve/GCD/binpow templates; these are the observation + factorization drills that show up in harder OAs and cyan→blue contests.
**Prereq topics:** Euclidean GCD/LCM, O(√n) factorization, Sieve / SPF, binary exponentiation, harmonic loops; finished the standard Number Theory & Math ladder
**Pattern in one paragraph:** After T-primes / Fadi-LCM / Orac-Models, contest NT stops announcing the template and hides a **rewritten invariant**: gcd of shifts becomes gcd of differences; gcd of pairwise LCMs collapses to second-min exponents; “make equal in k divides” is total Ω-count; floor(n/i) jumps in √n blocks. Recognize depth-pass NT when constraints are `n·√A` or `A log A` feasible, values ≤1e6 invite SPF sieves, or the statement mixes GCD/LCM/divisors with construction, games, or range queries.

## Ladder (easy -> hard, 23 problems)

- [ ] [k-th divisor](https://codeforces.com/problemset/problem/762/A) — `Codeforces` `1400` — list divisors O(√n) — **(core)** collect both `i` and `n/i`, sort, pick `k`-th; OA staple “k-th divisor”
- [ ] [Bash's Big Day](https://codeforces.com/problemset/problem/757/B) — `Codeforces` `1400` — max share a prime factor — **(core)** factor each `a_i`, count frequency per prime; largest bucket wins
- [ ] [I Hate 1111](https://codeforces.com/problemset/problem/1526/B) — `Codeforces` `1400` — 11…1 base trick — **(core)** numbers of form `11…1` generate all large enough `x`; check `x - 1111·k` residue / chicken-nugget style bound
- [ ] [Number Game](https://codeforces.com/problemset/problem/1370/C) — `Codeforces` `1400` — game + factorization — **(core)** win/lose from “odd / power-of-two / single odd prime × 2ᵏ”; forces full factor casework
- [ ] [Make It Round](https://codeforces.com/problemset/problem/1759/D) — `Codeforces` `1400` — trailing zeros via 2×5 — **(core)** multiply by 2/5 to balance exponents under budget `m`; classic trailing-zero rewrite
- [ ] [Everyone is a Winner!](https://codeforces.com/problemset/problem/1263/C) — `Codeforces` `1400` — floor blocks — **(core)** distinct `⌊n/i⌋` values; jump `i` to end of each constant segment in O(√n)
- [ ] [Vasya and Petya's Game](https://codeforces.com/problemset/problem/576/A) — `Codeforces` `1500` — primes + prime powers — **(core)** ask all `p^k ≤ n`; minimal questions that cover every composite’s factors
- [ ] [Plus and Multiply](https://codeforces.com/problemset/problem/1542/B) — `Codeforces` `1500` — reverse from `n` by `/a` or `-b` — **(core)** while `n` divisible by `a`, peel; else subtract `b`; careful `a=1` edge
- [ ] [Tile Painting](https://codeforces.com/problemset/problem/1242/A) — `Codeforces` `1500` — period = smallest prime factor — **(core)** if `n` prime → 1 color; if `n=p^k` → `p`; else ≥2 distinct primes → 1
- [ ] [Pride](https://codeforces.com/problemset/problem/891/A) — `Codeforces` `1500` — adjacent replace by gcd — **(core)** if some `a_i=1` answer is count of non-1; else shortest subarray with gcd 1, then `n-1` ops
- [ ] [D - Factorial and Multiple](https://atcoder.jp/contests/abc280/tasks/abc280_d) — `AtCoder` `ABC D (~1600 CF-eq)` — min `N` with `K | N!` — **(core)** factor `K`, binary-search `N` with Legendre counts per prime power
- [ ] [Sum of Divisors](https://cses.fi/problemset/task/1082) — `CSES` `Mathematics` — ∑σ(i) for `n≤1e12` — **(core)** rewrite as ∑ᵢ i·⌊n/i⌋; floor-block the sum in O(√n)
- [ ] [E - Coprime](https://atcoder.jp/contests/abc177/tasks/abc177_e) — `AtCoder` `ABC E (~1600–1700 CF-eq)` — pairwise vs setwise — **(core)** SPF sieve: pairwise iff each prime hits ≤1 element; setwise iff global gcd=1
- [ ] [Row GCD](https://codeforces.com/problemset/problem/1458/A) — `Codeforces` `1600` — gcd(aᵢ+bⱼ) identity — **(core)** `gcd(a₁+b,…)=gcd(a₁+b, a₂−a₁, a₃−a₁,…)`; precompute gcd of diffs
- [ ] [Orac and LCM](https://codeforces.com/problemset/problem/1349/A) — `Codeforces` `1600` — gcd of pairwise LCMs — **(core)** per prime, answer exponent = second-minimum among `a_i` (min if unique); not the same as Orac and Models
- [ ] [Almost All Divisors](https://codeforces.com/problemset/problem/1165/D) — `Codeforces` `1600` — reconstruct `n` from divisor list — **(core)** candidate `n = min·max`; verify sorted proper-divisor list matches
- [ ] [Strange Function](https://codeforces.com/problemset/problem/1542/C) — `Codeforces` `1600` — LCM(1..k) jumps — **(core)** `f(i)=lcm(1..i)` grows only at prime-powers; count how long each plateau lasts up to `n`
- [ ] [Soldier and Number Game](https://codeforces.com/problemset/problem/546/D) — `Codeforces` `1700` — prefix Ω sieve — **(stretch)** `a!/(b!)` prime-factor count = prefix[a]−prefix[b] of big-omega via linear sieve
- [ ] [Quiz Master](https://codeforces.com/problemset/problem/1777/C) — `Codeforces` `1700` — cover 1..m via divisors — **(stretch)** sort skills; two pointers + freq of which topics are hit by current window’s divisors
- [ ] [Power Products](https://codeforces.com/problemset/problem/1225/D) — `Codeforces` `1800` — exponents mod `k` — **(stretch)** map each `a` to prime-exponent vector mod `k`; pair with complementary vector for product = perfect `k`-th power
- [ ] [Integers Have Friends](https://codeforces.com/problemset/problem/1548/B) — `Codeforces` `1800` — longest subarray with gcd(diffs)>1 — **(stretch)** sparse table / stack on gcd of consecutive differences; expand while gcd stays >1
- [ ] [Enlarge GCD](https://codeforces.com/problemset/problem/1034/A) — `Codeforces` `1800` — remove fewest to raise gcd — **(stretch)** divide out global gcd; count multiples of each candidate `d` via harmonic sieve on frequencies
- [ ] [Two Divisors](https://codeforces.com/problemset/problem/1366/D) — `Codeforces` `2000` — split `a` into coprime parts — **(stretch)** CM-band classic: peel SPF power `p^k ‖ a`, set `d₁=p^k`, `d₂=a/d₁`; output if `gcd(d₁+d₂,a)=1` else −1

## Must-internalize checklist (technique notes)

- **Floor blocks:** `⌊n/i⌋` is constant on `[i, n/⌊n/i⌋]`; jump the right endpoint — Everyone is a Winner / CSES Sum of Divisors (never loop `i=1..n` for `n=1e12`).
- **GCD of shifts:** `gcd(a+x,b+x)=gcd(a−b,b+x)`; Row GCD reduces an `n×m` family to one gcd of pairwise diffs plus each `bⱼ`.
- **GCD of pairwise LCMs:** per prime, keep the **two smallest** exponents across the array; answer uses the second-min (Orac and LCM) — not “min of all”.
- **SPF precompute:** sieve `spf[x]` up to `max Aᵢ`; factor in O(log A). Pairwise-coprime checks = “each prime appears in ≤1 element” (ABC177E / Bash's Big Day).
- **Ω / big-omega ops:** “divide out factors exactly `k` times” → count total prime factors with multiplicity (1538D / Soldier and Number Game prefixes).
- **Exponent vectors mod k:** product is a perfect `k`-th power iff every exponent ≡0 (mod k); hash the residue vector and look up its complement (Power Products).
- **GCD on ranges of diffs:** a subarray shares a common divisor >1 iff `gcd(|a₂−a₁|,|a₃−a₂|,…)>1`; RMQ/sparse-table over diffs (Integers Have Friends).
- **Trailing zeros / roundness:** only primes 2 and 5 matter; balance `min(v₂,v₅)` under a multiply-budget (Make It Round) — same Legendre idea as factorial multiples (ABC280D).

## Where it appears in OAs / interviews

- **“k-th divisor / reconstruct number from almost-all divisors”** — direct phone-screen math (762A / 1165D); test O(√n) divisor enumeration and consistency checks.
- **“Make array gcd >1 by deleting fewest / sharing a prime”** — Enlarge GCD / Bash's Big Day / ABC177E; often disguised as “group compatible IDs”.
- **“Trailing zeros after multiplying by ≤m” / “smallest N with K | N!”** — Make It Round / ABC280D; Legendre + binary search, common in quant/OA math rounds.
- **“GCD of all aᵢ+x” or “GCD of all pairwise LCMs”** — Row GCD / Orac and LCM; interviewers love the one-line identity rewrite over brute force.
