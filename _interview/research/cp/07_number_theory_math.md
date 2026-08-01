# 07 — Number Theory & Math

**Placement value:** Medium (Highly frequent in top-tier OAs (e.g., Google, Citadel, Akuna) and CP rating climbs, though less common in standard web-dev interviews)
**Prereq topics:** Arrays, Basic Hashing, Prefix Sums (helpful for sieves)
**Pattern in one paragraph:** Number theory problems usually ask you to efficiently compute properties related to divisors, primes, greatest common divisors (GCD), or large exponents modulo $M$. Instead of a brute-force approach (which gets TLE), you apply specific math properties like the Sieve of Eratosthenes to precompute primes, prime factorization bounded by $\sqrt{N}$, Fast Exponentiation for $O(\log N)$ powers, or combinations like Fermat's Little Theorem for modular inverses. In problems, these appear when constraints have numbers up to $10^9$ requiring $O(\sqrt{N})$ factors, or arrays of size $10^5$ where you need to check pairs for co-primality.

## Ladder (easy -> hard, ~26 problems)
- [ ] [Divisibility Problem](https://codeforces.com/problemset/problem/1328/A) — `Codeforces` `800` — math, modulo — (CP-31) The absolute basics of $O(1)$ modulo arithmetic in OAs.
- [ ] [LCM Problem](https://codeforces.com/problemset/problem/1389/A) — `Codeforces` `800` — math, LCM — (CP-31) Introduces the property that $LCM(x, 2x) = 2x$.
- [ ] [Almost Prime](https://codeforces.com/problemset/problem/26/A) — `Codeforces` `900` — prime factorization, sieve — (A2OJ) The hello-world of modifying the Sieve of Eratosthenes. **(core)**
- [ ] [Coprime](https://codeforces.com/problemset/problem/1742/D) — `Codeforces` `1100` — gcd, pigeonhole — (CP-31) Essential realization that bounded array values ($A_i \le 1000$) mean we can precompute/hash instead of $O(N^2)$ checks. **(core)**
- [ ] [Pow(x, n)](https://leetcode.com/problems/powx-n/) — `LeetCode` `Medium` — fast exponentiation — (NeetCode, Striver) The canonical interview question for binary exponentiation. **(core)**
- [ ] [Count Primes](https://leetcode.com/problems/count-primes/) — `LeetCode` `Medium` — sieve of Eratosthenes — (NeetCode, Striver) Standard $O(N \log \log N)$ prime counting, an OA staple. **(core)**
- [ ] [Exponentiation](https://cses.fi/problemset/task/1095) — `CSES` `Math` — fast power, modulo — (CSES) Classic template implementation for $(A^B) \pmod M$. **(core)**
- [ ] [Arpa’s hard exam and Mehrdad’s naive cheat](https://codeforces.com/problemset/problem/742/A) — `Codeforces` `1200` — modular exponentiation, period — (A2OJ) Shows how to handle large exponents either by cycle finding or fast power.
- [ ] [Sherlock and his girlfriend](https://codeforces.com/problemset/problem/776/B) — `Codeforces` `1200` — prime numbers, coloring — (Codeforces EDU) Beautiful construction using primes; prime vs composite coloring.
- [ ] [Fadi and LCM](https://codeforces.com/problemset/problem/1285/C) — `Codeforces` `1200` — divisors, lcm — (CP-31) Teaches $O(\sqrt{X})$ divisor traversal to find optimal coprime pairs. **(core)**
- [ ] [T-primes](https://codeforces.com/problemset/problem/230/B) — `Codeforces` `1300` — sieve, perfect squares — (A2OJ, Striver) Classic trick: a number has exactly 3 divisors iff it is the square of a prime. **(core)**
- [ ] [Buying Shovels](https://codeforces.com/problemset/problem/1360/D) — `Codeforces` `1300` — divisors — Simple $O(\sqrt{N})$ divisor finding with a threshold constraint. **(core)**
- [ ] [Counting Divisors](https://cses.fi/problemset/task/1713) — `CSES` `Math` — divisor sieve — (CSES) Introduces $O(X \log X)$ precomputation for divisor counts across multiple queries. **(core)**
- [ ] [Common Divisors](https://cses.fi/problemset/task/1081) — `CSES` `Math` — gcd, frequency array — (CSES) $O(X \log X)$ sieve-like GCD finding; a must-know trick for $O(N)$ GCD pair queries. **(core)**
- [ ] [Binomial Coefficients](https://cses.fi/problemset/task/1079) — `CSES` `Math` — modular inverse, combinatorics — (CSES) The standard $O(N)$ factorial precomputation and Fermat's Little Theorem template. **(core)**
- [ ] [Orac and Models](https://codeforces.com/problemset/problem/1350/B) — `Codeforces` `1400` — dp on divisors — Transitions $DP[i]$ to multiples $DP[i \cdot k]$, teaching the $O(N \log N)$ harmonic sum DP. **(core)**
- [ ] [Collatz Conjecture](https://codeforces.com/problemset/problem/1982/B) — `Codeforces` `1400` — math, simulation — (TLE) Handling large simulations with mathematical cycle skipping.
- [ ] [GCD-sequence](https://codeforces.com/problemset/problem/1980/D) — `Codeforces` `1400` — gcd properties — (TLE) Array manipulation with GCD and handling local monotonicity breaks.
- [ ] [Divisible Numbers (easy version)](https://codeforces.com/problemset/problem/1744/E1) — `Codeforces` `1500` — divisors — Working with the divisors of a product $a \cdot b$ bounded by $C \cdot D$. **(stretch)**
- [ ] [Colliders](https://codeforces.com/problemset/problem/154/B) — `Codeforces` `1500` — prime factorization, data structures — Maintaining sets of prime factors for dynamic co-primality checking. **(stretch)**
- [ ] [Koxia and Number Theory](https://codeforces.com/problemset/problem/1770/C) — `Codeforces` `1700` — CRT, pigeonhole principle — A brilliant application of modular arithmetic to avoid common factors in arrays. **(stretch)**
- [ ] [Trailing Loves (or L'oeufs?)](https://codeforces.com/problemset/problem/1114/C) — `Codeforces` `1700` — Legendre's formula, base conversion — Finding trailing zeros of $N!$ in an arbitrary base $B$. **(stretch)**
- [ ] [Short Task](https://codeforces.com/problemset/problem/1512/G) — `Codeforces` `1700` — divisor sum sieve — $O(N \log N)$ sieve variant to compute the sum of divisors function $\sigma(n)$. **(stretch)**
- [ ] [Same GCDs](https://codeforces.com/problemset/problem/1295/D) — `Codeforces` `1700` — Euler's totient function — Demonstrates that counting $x$ such that $\gcd(a, m) = \gcd(a+x, m)$ maps exactly to $\phi(m / \gcd(a, m))$. **(stretch)**
- [ ] [Fox And Jumping](https://codeforces.com/problemset/problem/510/D) — `Codeforces` `1900` — Bezout's identity, shortest path, dp — Recognizing that reaching anywhere on a line requires the GCD of step sizes to be 1, computed via DP/Dijkstra. **(stretch)**
- [ ] [Strange Beauty](https://codeforces.com/problemset/problem/1475/G) — `Codeforces` `1900` — dp on divisors, sieve — A step up from "Orac and Models"; counting maximum subsets where every pair divides each other perfectly. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- **Sieve of Eratosthenes:** Implement the $O(N \log \log N)$ boolean array to find primes up to $10^7$.
- **Fast Exponentiation (Binary Power):** Write the iterative $O(\log B)$ function to compute $A^B \pmod M$.
- **GCD & LCM:** Write $O(\log (\min(a,b)))$ Euclidean GCD from memory; know that $LCM(a,b) = (a / \gcd(a,b)) \cdot b$ to avoid overflow.
- **Divisor Finding ($O(\sqrt{N})$):** Iterate $i$ from $1$ to $\sqrt{N}$. If $N \pmod i == 0$, both $i$ and $N/i$ are divisors.
- **Prime Factorization ($O(\sqrt{N})$):** Iterate up to $\sqrt{N}$ extracting factors, and handle the remaining $> \sqrt{N}$ prime.
- **Harmonic Sieve ($O(N \log N)$):** Iterate multiples `for (int j = i; j <= N; j += i)` to count/sum divisors or precompute properties for all $i \le N$.
- **Fermat's Little Theorem & Mod Inverse:** Know that if $P$ is prime, $A^{P-1} \equiv 1 \pmod P$, so the modular inverse is $A^{P-2} \pmod P$.
- **Combinatorics ($nCr \pmod M$):** Precompute factorials and their modular inverses in $O(N)$ to answer $nCr$ queries in $O(1)$.

## Where it appears in OAs / interviews
- **"Group the Coprime Elements":** Disguised graph or array problems where elements share an edge if they are coprime or share a common factor (often requires sieving prime factors and treating primes as "bridge" nodes).
- **"Ways to Choose with Constraints":** Combinatorics questions masking a massive modulo math problem. You must formulate the math equation, precompute factorials and inverse factorials, and answer in $O(N)$.
- **"Find the Cycle / Trailing Zeros":** Questions asking for properties of massive outputs, like trailing zeros of a factorial (Legendre's formula) or the last digit of a massive exponentiation (cycle finding / fast power).
- **"Divisibility Count in Array":** Given an array, find pairs where $A_i$ divides $A_j$. If $A_i \le 10^5$, this is solved via a frequency array and harmonic iteration rather than $O(N^2)$ checks.
