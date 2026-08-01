# 21 — Combinatorics & Modular Math

**Placement value:** High (OA “number of ways mod 10^9+7” is ubiquitous; stars-and-bars / nCr / expectation appear in Google/Meta/quant screens; CRT/φ are the rating climb)
**Prereq topics:** Binary exponentiation, GCD/Euclid, basic counting (permutations/combinations intuition), DP intro (for probability DP)
**Pattern in one paragraph:** Constraints force answers modulo a prime ($10^9+7$ / $998244353$), so “division” becomes multiply-by-modular-inverse (Fermat: $a^{p-2}$). Recurring move: rewrite the count as $\binom{n}{k}$ / multinomial / stars-and-bars / Catalan / derangement, then answer in $O(1)$ after $O(N)$ fact + invFact precompute. Inclusion-exclusion and CRT appear when you overcount unions or must satisfy several moduli. Probability/expectation problems either closed-form ($E[\max]$, linearity of indicator r.v.s) or DP on remaining counts. Signal words: “ways modulo”, “expected value”, “coprime / remainder system”, “valid brackets / noncrossing”, “distribute identical items”.

## Ladder (easy -> hard, 26 problems)
- [ ] [Dreamoon and WiFi](https://codeforces.com/problemset/problem/476/B) — `Codeforces` `1300` — counting, probability — Enumerate `?` fillings; intro to “favorable / total” with binomial-style counting.
- [ ] [K-th Beautiful String](https://codeforces.com/problemset/problem/1328/B) — `Codeforces` `1300` — combinatorial construction — Rank/unrank among strings with exactly two `b`s; forces thinking in $\binom{i}{2}$ offsets.
- [ ] [Exponentiation II](https://cses.fi/problemset/task/1712) — `CSES` `Mathematics` — Fermat / Euler tower — (CSES, USACO Guide Modular) Compute $a^{b^c} \bmod p$ via $a^{b^c \bmod (p-1)}$; canonical φ(MOD) drill. **(core)**
- [ ] [Binomial Coefficients](https://cses.fi/problemset/task/1079) — `CSES` `Mathematics` — fact + invFact, Fermat inverse — (CSES, USACO Guide Combo) *The* $O(N)$ precompute / $O(1)$ $\binom{n}{k}$ template. **(core)**
- [ ] [Creating Strings II](https://cses.fi/problemset/task/1715) — `CSES` `Mathematics` — multinomial mod p — (CSES, USACO Guide Combo) $n! / \prod c_i!$ with inverse factorials; multiset permutations. **(core)**
- [ ] [Distributing Apples](https://cses.fi/problemset/task/1716) — `CSES` `Mathematics` — stars and bars — (CSES, USACO Guide Combo) Identical apples → $\binom{m+n-1}{n-1}$; first pure stars-and-bars. **(core)**
- [ ] [Close Tuples (easy version)](https://codeforces.com/problemset/problem/1462/E1) — `Codeforces` `1500` — nCr on sorted array — (USACO Guide Combo) For each left endpoint count valid windows via $\binom{\cdot}{2}$. **(core)**
- [ ] [Journey](https://codeforces.com/problemset/problem/839/C) — `Codeforces` `1500` — expectation on tree — DFS expected path length; linearity / branch probabilities.
- [ ] [Christmas Party](https://cses.fi/problemset/task/1717) — `CSES` `Mathematics` — derangements — (CSES) $!n$ via IE or DP $!(n)=(n-1)(!(n-1)+!(n-2))$. **(core)**
- [ ] [Bracket Sequences I](https://cses.fi/problemset/task/2064) — `CSES` `Mathematics` — Catalan numbers — (CSES) $C_{n/2}=\frac{1}{n/2+1}\binom{n}{n/2}$ mod p; *the* Catalan template. **(core)**
- [ ] [Prime Multiples](https://cses.fi/problemset/task/2185) — `CSES` `Mathematics` — inclusion-exclusion — (CSES) Count $\le n$ divisible by ≥1 of $k\le20$ primes via subset LCM/products. **(core)**
- [ ] [Almost Identity Permutations](https://codeforces.com/problemset/problem/888/D) — `Codeforces` `1600` — partial derangements — (USACO Guide Combo) Sum $\binom{n}{i}\cdot !i$ for $i\le k$; derangement + choose.
- [ ] [Two Arrays](https://codeforces.com/problemset/problem/1288/C) — `Codeforces` `1600` — stars and bars + nCr — Nondecreasing → weakly increasing pairs reduce to $\binom{n+2m-1}{2m}$. **(core)**
- [ ] [Little Pony and Expected Maximum](https://codeforces.com/problemset/problem/453/A) — `Codeforces` `1600` — E[max] closed form — $E[\max]=\sum x\big((x/m)^n-((x-1)/m)^n\big)$; classic expectation. **(core)**
- [ ] [Product 1 Modulo N](https://codeforces.com/problemset/problem/1514/C) — `Codeforces` `1600` — units / Euler totient — Product of $x$ with $\gcd(x,n)=1$ equals $1$ except when a self-inverse remains.
- [ ] [Count the Arrays](https://codeforces.com/problemset/problem/1312/D) — `Codeforces` `1700` — nCr construction — Count arrays with unique max + exactly one duplicate; multi-factor binomial. **(core)**
- [ ] [Santa's Bot](https://codeforces.com/problemset/problem/1279/D) — `Codeforces` `1700` — mod inverse + probability — (USACO Guide Modular) Sum $P(\text{pick }x)\cdot P(\text{child wants }x)$ with inverses. **(core)**
- [ ] [Ilya and Escalator](https://codeforces.com/problemset/problem/518/D) — `Codeforces` `1700` — probability DP — Expected people on escalator; $dp[t][k]$ transition with $p$.
- [ ] [Koxia and Number Theory](https://codeforces.com/problemset/problem/1770/C) — `Codeforces` `1700` — CRT / pigeonhole — Pairwise $\gcd(a_i+d,a_j+d)=1$ ∀d iff no prime divides ≥2 residues. **(stretch)**
- [ ] [Beautiful Numbers](https://codeforces.com/problemset/problem/300/C) — `Codeforces` `1800` — nCr + digit sum — Famous: sum $\binom{n}{i}$ over $a$-$b$-beautiful digit counts. **(stretch)**
- [ ] [Bag of mice](https://codeforces.com/problemset/problem/148/D) — `Codeforces` `1800` — probability DP — Classic princess/dragon draw-without-replacement DP. **(stretch)**
- [ ] [Remainders Game](https://codeforces.com/problemset/problem/687/B) — `Codeforces` `1800` — CRT / LCM — Know $x\bmod c_i$ ⇒ know $x\bmod k$ iff $k\mid\mathrm{lcm}(c_i)$ (prime-power wise). **(stretch)**
- [ ] [Same GCDs](https://codeforces.com/problemset/problem/1295/D) — `Codeforces` `1800` — Euler totient — Count $x\in[0,m)$ with $\gcd(a,m)=\gcd(a+x,m)$ → $\varphi(m/\gcd(a,m))$. **(stretch)**
- [ ] [Bots](https://codeforces.com/problemset/problem/575/H) — `Codeforces` `1800` — Catalan / paths — (USACO Guide Combo) Game-state count reduces to Catalan-like $\binom{2n+2}{n+1}-1$. **(stretch)**
- [ ] [Bad Luck Island](https://codeforces.com/problemset/problem/540/D) — `Codeforces` `1900` — 3-type probability DP — Rock/scissors/paper extinction probs; $dp[r][s][p]$. **(stretch)**
- [ ] [Congruence Equation](https://codeforces.com/problemset/problem/919/E) — `Codeforces` `2100` — CRT / modular order — Solve $n\cdot a^n\equiv b\pmod{p}$ by cycling residues via CRT-style period. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- **Modular inverse (prime MOD):** $a^{-1}\equiv a^{\mathrm{MOD}-2}\pmod{\mathrm{MOD}}$ via binary exponentiation; never “divide” under mod.
- **fact / invFact template:** $fact[i]=fact[i-1]\cdot i$; $invFact[N]=fact[N]^{-1}$; $invFact[i]=invFact[i+1]\cdot(i+1)$; then $\binom{n}{k}=fact[n]\cdot invFact[k]\cdot invFact[n-k]$.
- **Fermat / Euler for towers:** $a^b\bmod p = a^{b\bmod(p-1)}\bmod p$ when $\gcd(a,p)=1$; handle $a\equiv0$ and $0^0$ carefully (Exponentiation II).
- **Stars and bars:** $x_i\ge0$: $\binom{n+k-1}{k-1}$; $x_i\ge1$: $\binom{n-1}{k-1}$; map nondecreasing sequences → this.
- **Catalan:** $C_n=\frac{1}{n+1}\binom{2n}{n}=\binom{2n}{n}-\binom{2n}{n-1}$; brackets, BSTs, Dyck paths, noncrossing.
- **Derangements:** $!n=n!\sum_{i=0}^n\frac{(-1)^i}{i!}$ or $!n=(n-1)(!(n-1)+!(n-2))$.
- **Inclusion-exclusion:** $|∪A_i|=\sum|A_i|-\sum|A_i∩A_j|+\cdots$; bitmask over $k\le20$ sets when $n$ is huge.
- **Euler totient:** $\varphi(n)=n\prod_{p\mid n}(1-1/p)$; counts units mod $n$; appears in “same GCD” / multiplicative group size.
- **CRT intuition:** system $x\equiv a_i\pmod{m_i}$ (coprime $m_i$) has unique solution mod $\prod m_i$; non-coprime ⇒ consistency on $\gcd$; LCM of moduli = information you know.
- **Expectation toolkit:** linearity $E[\sum X_i]=\sum E[X_i]$ (indicators!); $E[\max]$ via CDF; else DP on remaining state for draw/process probs.

## Where it appears in OAs / interviews
- **“Number of ways to form teams / passwords / paths mod 10^9+7”:** Almost always precomputed $\binom{n}{k}$ or multinomial (Creating Strings II / Close Tuples family) — FAANG OA staple.
- **“Distribute identical items into distinct bins (with/without empties)”:** Stars-and-bars disguised as “non-negative integer solutions” or “nondecreasing arrays” (Two Arrays / Distributing Apples).
- **“Expected number of …”:** Linearity on indicators (“expected distinct / expected inversions”) or $E[\max]$ of $n$ dice (Little Pony / Candy Lottery); quant shops love this.
- **“Valid bracket strings / binary trees of size n”:** Catalan closed form under mod (Bracket Sequences I) — sometimes asked raw, sometimes as DP that *is* Catalan.
