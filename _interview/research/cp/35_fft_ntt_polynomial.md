# 35 — FFT / NTT & polynomial multiplication (stretch)

**Placement value:** Medium — almost never a literal OA template (Striver omits this entirely); shows up only in hard screens as “count ways / match strings under large \(n\)” once you already know generating functions. Primarily a Candidate Master+ rating-builder and a CP toolkit milestone.
**Prereq topics:** Modular arithmetic (esp. `998244353`), binary exponentiation, basic combinatorics / generating-function intuition, complex numbers or roots of unity (for FFT), primitive roots / NTT-friendly primes, string matching intuition (KMP-level), basic DP
**Pattern in one paragraph:** Whenever the bottleneck is a **convolution** \(c_k=\sum_{i+j=k}a_ib_j\) (or “multiply two polynomials”, “raise a generating function to the \(k\)-th power”, “count alignments / Hamming mismatches”, “XOR/OR of masks”), replace the \(O(n^2)\) nested loops with FFT/NTT in \(O(n\log n)\). **FFT** = DFT over \(\mathbb{C}\) (watch precision; round to nearest int). **NTT** = same butterfly over a prime \(p=c\cdot 2^k+1\) with a primitive \(2^k\)-th root (no floats; default mod `998244353`). Signals: \(n\sim 10^5\)–\(10^6\) and formula looks like a sum of products over \(i+j=k\); “all pairwise products / digit-sum halves / subset color vectors”; wildcard / multi-alphabet string matching; later — XOR convolution (FWHT), online / divide-and-conquer FFT for DP transitions.

## Ladder (easy -> hard, 22 problems)
- [ ] [Torn Lucky Ticket](https://codeforces.com/problemset/problem/1895/C) — `Codeforces` `1400` — half-sum generating-function idea — **(core)** Digits/halves counting; train “encode counts as a poly / map” *before* writing FFT.
- [ ] [Lightsabers (easy)](https://codeforces.com/problemset/problem/958/F1) — `Codeforces` `1500` — color multiset count — Warmup to the Lightsabers trilogy; “is this color-count vector achievable?”
- [ ] [Knapsack for All Subsets](https://atcoder.jp/contests/abc169/tasks/abc169_f) — `AtCoder` `ABC169 F` — formal power series / knapsack GF — **(core)** Treat knapsack DP as multiplying \((1+x^{A_i})\) factors; GF language without needing NTT yet (\(N,S\le 3000\)).
- [ ] [Lightsabers (medium)](https://codeforces.com/problemset/problem/958/F2) — `Codeforces` `1800` — windowed color counts — Two pointers / frequency window; sets up the hard “product of many polys” version.
- [ ] [Convolution](https://atcoder.jp/contests/practice2/tasks/practice2_f) — `AtCoder` `ACL Practice F` — raw NTT multiply mod \(998244353\) — **(core)** *The* template drill (ACL `convolution` / Library Checker Convolution); implement your own NTT once, then allow the library.
- [ ] [Substring 2](https://atcoder.jp/contests/abc196/tasks/abc196_f) — `AtCoder` `ABC196 F` — Hamming distance via convolution — **(core)** Reverse pattern, 0/1 indicator polys, one (or two) convolutions → min replacements; ACL `convolution` classic.
- [ ] [GCD of Polynomials](https://codeforces.com/problemset/problem/901/B) — `Codeforces` `2200` — Euclidean algorithm on polys — **(core)** Polynomial algebra without FFT: degree / remainder intuition every NTT user still needs.
- [ ] [Bear and Polynomials](https://codeforces.com/problemset/problem/639/C) — `Codeforces` `2200` — evaluate / rewrite a poly — Coefficient surgery and “poly as an array” fluency before heavy transforms.
- [ ] [Yet Another String Matching Problem](https://codeforces.com/problemset/problem/954/I) — `Codeforces` `2200` — multi-alphabet FFT + DSU — **(core)** cp-algorithms staple; per-character-pair convolutions, then merge equated letters.
- [ ] [Product Modulo](https://atcoder.jp/contests/agc047/tasks/agc047_c) — `AtCoder` `AGC047 C` — primitive root → cyclic convolution — **(core)** Map \(x\mapsto \log_g x\), FFT the count array; Errichto editorial pattern.
- [ ] [Nikita and Order Statistics](https://codeforces.com/problemset/problem/993/E) — `Codeforces` `2300` — prefix 0/1 → convolution — **(stretch)** Famous “build \(A(x),B(x)\) from prefix counts of values \(<x\), multiply”; also a precision / big-coeff FFT drill.
- [ ] [Painting Square](https://codeforces.com/problemset/problem/300/D) — `Codeforces` `2300` — DP as polynomial power — **(stretch)** Height-DP coefficients; \(P_{h+1}\) from \(P_h^4\) (naive \(O(k^2)\) or FFT).
- [ ] [Thief in a Shop](https://codeforces.com/problemset/problem/632/E) — `Codeforces` `2400` — indicator poly raised to power \(k\) — **(stretch)** *The* “exactly \(k\) items → \(P(x)^k\)” milestone; binary expo + FFT/NTT; clamp nonzero coeffs to 1 if only reachability matters.
- [ ] [Lucky Tickets](https://codeforces.com/problemset/problem/1096/G) — `Codeforces` `2400` — digit GF power + \(\sum c_i^2\) — **(stretch)** Build \(P=\sum x^{d_i}\), compute \(P^{n/2}\) mod `998244353`, answer \(\sum c_i^2\); pure NTT power template.
- [ ] [Fuzzy Search](https://codeforces.com/problemset/problem/528/D) — `Codeforces` `2500` — wildcard / “within \(k\)” string FFT — **(stretch)** cp-algorithms / string-FFT classic; match with slack via indicator convolution (or squared-diff trick).
- [ ] [Red-White Fence](https://codeforces.com/problemset/problem/1251/F) — `Codeforces` `2500` — combinatorics × NTT — **(stretch)** Count sequences with color constraints; typical “closed form → multiply polys under `998244353`”.
- [ ] [Nim Counting](https://atcoder.jp/contests/abc212/tasks/abc212_h) — `AtCoder` `ABC212 H` — XOR convolution / FWHT — **(stretch)** Game-theory GF over XOR; Hadamard transform instead of cyclic NTT.
- [ ] [Stroll](https://atcoder.jp/contests/abc213/tasks/abc213_h) — `AtCoder` `ABC213 H` — divide-and-conquer (online) FFT — **(stretch)** Canonical CDQ / “online convolution” for DP where \(f[i]\) depends on earlier \(f\) via a convolution.
- [ ] [Lightsabers (hard)](https://codeforces.com/problemset/problem/958/F3) — `Codeforces` `2600` — product of many small polys — **(stretch)** cp-algorithms listed; heap / D&C multiply frequency polys, take \([x^k]\).
- [ ] [Binary Table](https://codeforces.com/problemset/problem/662/C) — `Codeforces` `2600` — FWHT / XOR convolution classic — **(stretch)** Flip columns → minimize ones; *the* Walsh–Hadamard milestone.
- [ ] [Running Competition](https://codeforces.com/problemset/problem/1398/G) — `Codeforces` `2600` — differences via FFT — **(stretch)** cp-algorithms practice list; achievable distances from two position sets.
- [ ] [Typical Convolution Problem](https://atcoder.jp/contests/abc315/tasks/abc315_h) — `AtCoder` `ABC315 Ex` — relaxed / online convolution — **(stretch)** Hard endgame: \(F_n\) defined from earlier \(F\) via a running square-convolution; forces the full online-FFT toolkit.

## Must-internalize checklist (5-10 bullets)
- Convolution recognition: \(c_k=\sum_{i+j=k}a_ib_j\) (also “generate all pairwise sums/products of exponents”) ⇒ multiply polys, don’t nest loops.
- FFT multiply: pad to length \(2^{\lceil\log_2(n+m-1)\rceil}\), forward DFT both, pointwise multiply, inverse DFT, divide by \(n\), round; complexity \(O(n\log n)\).
- NTT multiply: same butterflies over mod \(p=c\cdot 2^k+1\) (stock: `998244353`, \(g=3\)); precompute roots; **no** floating error. Prefer NTT whenever the statement is mod an NTT-friendly prime.
- Arbitrary / non-NTT mod: split coeffs + CRT (3 NTT mods), or `long double` FFT with care (cp-algo “arbitrary modulus”); know when precision dies.
- Poly power: binary expo of polys (\(P^k\)) for “exactly \(k\) summands” / lucky-ticket halves; optionally power in frequency domain if you only need support (Thief).
- String FFT toolkit: reverse pattern; 0/1 (or \(\pm 1\)) indicator arrays per alphabet symbol; wildcard / Hamming via \(\sum (P_j-T_{i+j})^2\) expanded into 2–3 convolutions.
- FWHT: XOR convolution \(c_k=\sum_{i\oplus j=k}a_ib_j\) in \(O(n\log n)\) on length \(2^k\); same idea for OR/AND with different transforms (ABC212H / 662C family).
- Online / D&C FFT: when \(f[i]\) depends on \(\sum_{j<i}f[j]\cdot g[i-j]\), recurse mid, convolve left→right contribution, then solve right (ABC213H / ABC315Ex).
- Ship a battle-tested template (iterative butterflies + bit-reverse) and know ACL `atcoder::convolution` / `convolution_ll` for contests that allow it.

## Where it appears in OAs / interviews
- Almost never asked to code FFT in a timed OA; if it appears, it’s disguised as “count ways two halves have equal sum / product” and \(n\) is small enough for DP — still *recognize* the generating-function shape (Torn Lucky Ticket / Lucky Tickets family).
- Harder online assessments sometimes ask “minimum Hamming / wildcard matches of pattern in text” with \(n\sim 10^5\) — the interview-friendly answer is “FFT convolution of indicators,” even if they accept hashing + BS as a substitute.
- “Unlimited knapsack / exactly \(k\) items, list all possible totals” under large sum bounds → poly power (Thief-in-a-Shop shape); interviewers usually want the GF insight more than the butterflies.
- XOR / bitmask “combine two arrays by XOR of indices” in researchy screens → FWHT one-liner once you’ve done Binary Table / Nim Counting.
