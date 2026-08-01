# 38 — Möbius Function, Multiplicative Functions & Divisor Sums

**Placement value:** Medium (divisor sieves / φ / “count pairs with gcd” show up in harder OAs and quant screens; full Möbius inversion is mainly a CF 1800–2200 rating-builder — Striver never covers it)
**Prereq topics:** Sieve of Eratosthenes, GCD/LCM, $O(\sqrt{n})$ factorization, modular arithmetic / fast pow, basic inclusion-exclusion, harmonic loops (`for (j = i; j <= n; j += i)`)
**Pattern in one paragraph:** Arithmetic functions that respect prime factorization ($\tau,\sigma,\varphi,\mu,\mathrm{id},\mathbf{1}$) are computed via linear/harmonic sieve; divisor-sum identities rewrite $\sum_{i=1}^n f(i)$ as $\sum_d g(d)\lfloor n/d\rfloor$ and collapse into $O(\sqrt{n})$ floor-blocks. The key identity $\sum_{d\mid n}\mu(d)=[n=1]$ turns “exactly gcd $=1$ / exactly divisible by” into Möbius-weighted multiples: if $G(n)=\sum_{n\mid d}F(d)$ or $G(n)=\sum_{d\mid n}F(d)$, invert with $\mu$. Signal words: coprime pairs/subsequences, sum of $\gcd$/$\mathrm{lcm}$, square-free, “gcd exactly $k$”, $\sigma$/number of divisors under large $n$.

## Ladder (easy -> hard, 27 problems)
- [ ] [Divisor Chain](https://codeforces.com/problemset/problem/1864/C) — `Codeforces` `1300` — constructive, divisors — Build a short path of proper divisors; forces thinking in primes / halving.
- [ ] [k-th divisor](https://codeforces.com/problemset/problem/762/A) — `Codeforces` `1400` — $O(\sqrt{n})$ divisor list — Canonical “collect then sort divisors” template before sieves.
- [ ] [Fadi and LCM](https://codeforces.com/problemset/problem/1285/C) — `Codeforces` `1400` — divisors, LCM — Minimize $\max(a,b)$ with $\mathrm{lcm}(a,b)=x$ by walking divisors. **(core)**
- [ ] [Orac and Models](https://codeforces.com/problemset/problem/1350/B) — `Codeforces` `1400` — DP on multiples — $dp[i]\to dp[i\cdot k]$ in $O(n\log n)$; the harmonic-DP backbone for later GCD DP. **(core)**
- [ ] [Counting Divisors](https://cses.fi/problemset/task/1713) — `CSES` `Mathematics` — $\tau$ sieve — Precompute number of divisors for all $x\le 10^6$ via multiples. **(core)**
- [ ] [Common Divisors](https://cses.fi/problemset/task/1081) — `CSES` `Mathematics` — frequency + multiples — Max $d$ dividing $\ge 2$ array values; OA-classic harmonic trick. **(core)**
- [ ] [Disjoint Set of Common Divisors](https://atcoder.jp/contests/abc142/tasks/abc142_d) — `AtCoder` `ABC142 D` — gcd, prime factors — Count divisors of $\gcd(A,B)$ that are 1 or prime; factorization drill.
- [ ] [Almost All Divisors](https://codeforces.com/problemset/problem/1165/D) — `Codeforces` `1600` — reconstruct $n$ from divisors — Given all divisors except $1$ and $n$, recover $n$ (product of min/max).
- [ ] [Strange Function](https://codeforces.com/problemset/problem/1542/C) — `Codeforces` `1600` — LCM prefix, floor — Sum $f(i)$ where $f$ is first $k$ with $k\nmid i$; uses $\mathrm{lcm}(1..k)$ jumps.
- [ ] [Sum of Divisors](https://atcoder.jp/contests/abc172/tasks/abc172_d) — `AtCoder` `ABC172 D` — $\sum i\cdot\tau(i)$ — Warm-up for rewriting as $\sum_d\lfloor n/d\rfloor\cdot d$ before the hard floor trick.
- [ ] [Sum of Divisors](https://cses.fi/problemset/task/1082) — `CSES` `Mathematics` — Dirichlet floor blocks — Compute $\sum_{i=1}^n\sigma(i)=\sum_d d\lfloor n/d\rfloor$ for $n\le 10^{12}$ in $O(\sqrt{n})$. **(core)**
- [ ] [Short Task](https://codeforces.com/problemset/problem/1512/G) — `Codeforces` `1700` — $\sigma$ sieve inverse — Precompute $\sigma(x)$ then min $n$ with $\sigma(n)=c$; multiplicative-sieve landmark. **(core)**
- [ ] [Prime Multiples](https://cses.fi/problemset/task/2185) — `CSES` `Mathematics` — inclusion-exclusion — Count $\le n$ divisible by $\ge 1$ of $k\le 20$ primes; Möbius-on-subsets preview. **(core)**
- [ ] [Counting Coprime Pairs](https://cses.fi/problemset/task/2417) — `CSES` `Mathematics` — Möbius sieve — *The* $\sum\mu(d)\binom{cnt[d]}{2}$ template; USACO Guide PIE staple. **(core)**
- [ ] [Sum of gcd of Tuples (Hard)](https://atcoder.jp/contests/abc162/tasks/abc162_e) — `AtCoder` `ABC162 E` — divisor IE / Möbius — $\sum\gcd(A)$ over $[1..K]^N$ via exact-gcd counts from multiples. **(core)**
- [ ] [Same GCDs](https://codeforces.com/problemset/problem/1295/D) — `Codeforces` `1800` — Euler totient — Count $x$ with $\gcd(a,m)=\gcd(a+x,m)$ → $\varphi(m/\gcd(a,m))$.
- [ ] [Enlarge GCD](https://codeforces.com/problemset/problem/1034/A) — `Codeforces` `1800` — frequency of multiples — Drop fewest elements to raise global gcd; sieve over values.
- [ ] [Count GCD](https://codeforces.com/problemset/problem/1750/D) — `Codeforces` `1800` — coprime counting — Arrays with $\gcd=1$ under upper bounds; Möbius / IE over primes of $a_1$.
- [ ] [Power Products](https://codeforces.com/problemset/problem/1225/D) — `Codeforces` `1800` — square-free signature — Pair $a\cdot b=x^k$ by normalizing prime exponents mod $k$.
- [ ] [Strange Beauty](https://codeforces.com/problemset/problem/1475/G) — `Codeforces` `1900` — DP on divisors — Longest subsequence where every pair shares divisibility; stretch of Orac DP. **(stretch)**
- [ ] [Unusual Sequences](https://codeforces.com/problemset/problem/900/D) — `Codeforces` `2000` — Möbius inversion — Sequences summing to $y$ with $\gcd=x$; $f=\mu* 2^{\,\cdot-1}$ on divisors. **(core)**
- [ ] [Coprime Subsequences](https://codeforces.com/problemset/problem/803/F) — `Codeforces` `2000` — Möbius on arrays — Count subsequences with $\gcd=1$ via $\mu$ and $2^{cnt[d]}-1$. **(core)**
- [ ] [Small GCD](https://codeforces.com/problemset/problem/1900/D) — `Codeforces` `2000` — sum of gcd — Triple/pair gcd sums with multiples + inversion; rating-builder. **(stretch)**
- [ ] [Divan and Kostomuksha (easy version)](https://codeforces.com/problemset/problem/1614/D1) — `Codeforces` `2100` — DP on multiples — Max score rearranging with gcd transitions; harmonic DP at scale. **(stretch)**
- [ ] [Winter is here](https://codeforces.com/problemset/problem/839/D) — `Codeforces` `2200` — Möbius + combinatorics — Famous clan-strength sum; invert “gcd divisible by $d$” counts. **(stretch)**
- [ ] [Divide Both](https://atcoder.jp/contests/abc206/tasks/abc206_e) — `AtCoder` `ABC206 E` — Möbius pair count — Count pairs in $[L,R]$ with nontrivial proper gcd; clean contest Möbius. **(stretch)**
- [ ] [LCMs](https://atcoder.jp/contests/agc038/tasks/agc038_c) — `AtCoder` `AGC038 C` — LCM sum via $\mu$ — $\sum_{i<j}\mathrm{lcm}(a_i,a_j)$ reduced with Möbius; milestone stretch. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- **Linear / harmonic sieve for $\mu,\varphi,\tau,\sigma$:** smallest-prime sieve in $O(n)$; or for $\mu$: mark square factors and flip signs on square-free; for $\tau/\sigma$: `for (i) for (j=i;j<=n;j+=i)`.
- **Möbius definition:** $\mu(1)=1$; $\mu(p_1\cdots p_k)=(-1)^k$ if distinct primes; $\mu=0$ if a squared factor. Identity: $\sum_{d\mid n}\mu(d)=[n=1]$.
- **Inversion forms:** $G(n)=\sum_{d\mid n}F(d)\Rightarrow F(n)=\sum_{d\mid n}\mu(d)G(n/d)$; multiples form $G(n)=\sum_{n\mid m}F(m)\Rightarrow F(n)=\sum_{n\mid m}\mu(m/n)G(m)$.
- **Coprime-pair template:** $\sum_{i<j}[\gcd(a_i,a_j)=1]=\sum_d\mu(d)\binom{c(d)}{2}$ where $c(d)=\#\{a_i:d\mid a_i\}$ (CSES Counting Coprime Pairs).
- **Floor / Dirichlet blocks:** $\sum_{i=1}^n\lfloor n/i\rfloor$ (and $\sum i\lfloor n/i\rfloor$) in $O(\sqrt{n})$ by jumping $r=n/(n/l)$.
- **Exact-gcd from multiples:** compute $cnt_{\mathrm{mult}}[d]$, then $cnt_{=}[d]=cnt_{\mathrm{mult}}[d]-\sum_{k\ge2}cnt_{=}[kd]$ (or $\sum\mu(k)cnt_{\mathrm{mult}}[kd]$).
- **Euler totient links:** $n=\sum_{d\mid n}\varphi(d)$, $\varphi=n\prod_{p\mid n}(1-1/p)$, and $\varphi=\mu*\mathrm{id}$; use for “same GCD” / unit-group sizes.
- **Product / sum of divisors:** $\sigma$ multiplicative; product of all divisors of $n$ is $n^{\tau(n)/2}$ (careful with powers of primes / mod $\varphi$).

## Where it appears in OAs / interviews
- **“How many pairs in the array are coprime?”** — almost always frequency array + Möbius / IE over multiples (CSES Counting Coprime Pairs family); appears in harder OA number-theory rounds.
- **“Sum of gcd / lcm over all pairs (or over $[1..n]^k$)”** — rewrite with $\sum_d\varphi(d)$ or $\mu$-inversion; AtCoder ABC162 E / AGC LCM-sum style, also common in Codeforces Div1 B/C.
- **“Smallest $n$ with divisor-sum / divisor-count $=c$” or “answer $\sum\sigma(i)$ for huge $n$”** — Short Task / CSES Sum of Divisors; tests sieve vs floor-block maturity.
- **“Maximize gcd after deleting $k$ elements” / “check pairwise coprime”** — Enlarge GCD / ABC177-style; disguise as array cleanup rather than “number theory”.
