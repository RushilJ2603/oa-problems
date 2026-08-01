# 08 — Bit Manipulation & Bitmask Tricks

**Placement value:** High (XOR / popcount / subset masks show up constantly in OAs; bitmask DP is the CM stretch)
**Prereq topics:** Basics of integers, Arrays, Recursion / complete search, Prefix sums (for XOR)

**Pattern in one paragraph:** Treat integers as sets of bits. AND / OR / XOR + shifts give $O(1)$ set ops; $n \& (n-1)$ clears the lowest set bit; $n \& -n$ isolates it; XOR cancels pairs and builds prefix-XOR identities ($a[l..r] = pref[r] \oplus pref[l-1]$). When $n \le 20$, encode subsets as masks and enumerate $2^n$ (or $3^n$ submasks). In statements, look for "bitwise", small $n$, "differ in at most $k$ bits", powers of two, or "minimum / maximum AND/OR/XOR".

## Ladder (easy -> hard, 27 problems)
- [ ] [Single Number](https://leetcode.com/problems/single-number/) — `LeetCode` `Easy` — XOR cancel — NeetCode / Striver staple; every other element appears twice. (core)
- [ ] [Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/) — `LeetCode` `Easy` — popcount / Brian Kernighan — NeetCode classic; write `n &= n-1` from memory. (core)
- [ ] [Power of Two](https://leetcode.com/problems/power-of-two/) — `LeetCode` `Easy` — `n & (n-1) == 0` — Striver A2Z fundamental bit check. (core)
- [ ] [And Then There Were K](https://codeforces.com/problemset/problem/1527/A) — `Codeforces` `800` — clear bits below MSB — Tiny CF intro: answer is the number with only the highest bit of $n$ set.
- [ ] [Raising Bacteria](https://codeforces.com/problemset/problem/579/A) — `Codeforces` `1000` — popcount disguised — Famous A2OJ / beginners' problem: min adds = number of $1$-bits. (core)
- [ ] [Counting Bits](https://leetcode.com/problems/counting-bits/) — `LeetCode` `Easy` — DP on bits — NeetCode; `dp[i] = dp[i>>1] + (i&1)`. (core)
- [ ] [Mocha and Math](https://codeforces.com/problemset/problem/1559/A) — `Codeforces` `900` — AND of all — Shows that AND never increases; optimal is $\bigwedge a_i$.
- [ ] [Fedor and New Game](https://codeforces.com/problemset/problem/467/B) — `Codeforces` `1100` — Hamming via XOR+popcount — A2OJ classic; friends iff `__builtin_popcount(x^y) <= k`. (core)
- [ ] [Gray Code](https://cses.fi/problemset/task/2205) — `CSES` `Introductory Problems` — Gray code — CSES; generate with `i ^ (i >> 1)`.
- [ ] [Petr and a Combination Lock](https://codeforces.com/problemset/problem/1097/B) — `Codeforces` `1200` — enumerate $2^n$ — Mask = clockwise/counterclockwise choices; $n \le 15$. (core)
- [ ] [Apple Division](https://cses.fi/problemset/task/1623) — `CSES` `Introductory Problems` — subset partition — CSES canonical $n \le 20$ mask search for min difference. (core)
- [ ] [Subsets](https://leetcode.com/problems/subsets/) — `LeetCode` `Medium` — bitmask power set — Striver / NeetCode; for mask in $0..2^n-1$ take set bits. (core)
- [ ] [Rock and Lever](https://codeforces.com/problemset/problem/1420/B) — `Codeforces` `1200` — same MSB ⇒ AND ≥ XOR — High-transfer CF observation; group by highest set bit. (core)
- [ ] [Single Number III](https://leetcode.com/problems/single-number-iii/) — `LeetCode` `Medium` — XOR partition by lowest set bit — Striver interview problem; two odds in a sea of pairs. (core)
- [ ] [Range Xor Queries](https://cses.fi/problemset/task/1650) — `CSES` `Range Queries` — prefix XOR — CSES; drill $pref[r] \oplus pref[l-1]$.
- [ ] [Johnny and His Hobbies](https://codeforces.com/problemset/problem/1362/B) — `Codeforces` `1200` — find XOR that closes a set — Try $k = 1..1023$; check $a_i \oplus k$ stays in the set.
- [ ] [Preparing Olympiad](https://codeforces.com/problemset/problem/550/B) — `Codeforces` `1400` — constrained bitmask enum — A2OJ; $2^n$ with min/max/diff constraints.
- [ ] [Powers Of Two](https://codeforces.com/problemset/problem/1095/C) — `Codeforces` `1400` — split into $k$ powers of two — Greedy multiset of powers; OA-flavored constructive.
- [ ] [Array Elimination](https://codeforces.com/problemset/problem/1601/A) — `Codeforces` `1300` — bit-frequency / GCD of counts — $k$ must divide every bit-count; sharp bit-thinking drill.
- [ ] [Maximal AND](https://codeforces.com/problemset/problem/1669/H) — `Codeforces` `1300` — greedy set MSBs with $k$ ops — Placement-band AND maximization by bit counts. (core)
- [ ] [Counting Bits](https://cses.fi/problemset/task/1146) — `CSES` `Bitwise Operations` — count $1$-bits in $1..n$ — CSES Bitwise; $n \le 10^{15}$, digit/bit DP style.
- [ ] [Elevator Rides](https://cses.fi/problemset/task/1653) — `CSES` `Dynamic Programming` — bitmask DP — CSES / USACO Guide Gold; $dp[\text{mask}] = (\text{rides}, \text{last weight})$. (stretch)
- [ ] [Matching](https://atcoder.jp/contests/dp/tasks/dp_o) — `AtCoder` `DP contest O` — assignment bitmask DP — AtCoder Educational DP Contest; count perfect matchings mod $10^9+7$. (stretch)
- [ ] [Maximum Xor Subarray](https://cses.fi/problemset/task/1655) — `CSES` `Bitwise Operations` — XOR binary trie — CSES; maximize $pref[r] \oplus pref[l-1]$ with a bit trie. (stretch)
- [ ] [Minimax Problem](https://codeforces.com/problemset/problem/1288/D) — `Codeforces` `2000` — binary search + bitmasks — CF EDU-adjacent masterpiece; BS on min, check with $2^m$ masks. (stretch)
- [ ] [SOS Bit Problem](https://cses.fi/problemset/task/1654) — `CSES` `Bitwise Operations` — SOS DP — CSES / USACO Guide Plat; counts over submasks / supermasks in $O(2^B \cdot B)$. (stretch)
- [ ] [Grouping](https://atcoder.jp/contests/dp/tasks/dp_u) — `AtCoder` `DP contest U` — submask DP $O(3^n)$ — AtCoder Educational DP Contest; `for (sub = mask; sub; sub = (sub-1)&mask)`. (stretch)

## Must-internalize checklist (5-10 bullets)
- Bit primitives: test / set / clear / toggle bit $i$; isolate lowest set bit (`x & -x`); clear it (`x & (x-1)`); popcount / ctz / clz (or builtins).
- XOR identities: $x \oplus x = 0$, $x \oplus 0 = x$; prefix XOR for subarray XOR; find the one (or two) unique element(s).
- Power-of-two tests and constructions; think bit-independently when AND/OR/XOR constraints separate.
- Enumerate all subsets of $\{0..n-1\}$ with masks when $n \le 20$; iterate submasks in $O(3^n)$.
- Bitmask DP template: `dp[mask]`, transition by adding one element or merging a submask; Elevator / Matching style states.
- XOR trie (binary trie on 30–31 bits) for max XOR pair / max XOR subarray.
- SOS / subset-zeta: push contributions along each bit dimension in $O(2^B \cdot B)$.

## Where it appears in OAs / interviews
- **XOR uniqueness:** "Every element appears twice except one" (or thrice / two singles) — FAANG phone-screen classic (Single Number family).
- **Subset / flag masks:** $n \le 15$–$20$ items with on/off choices (lock dials, team splits, knapsack-like partition) → $2^n$ bitmasks, often without naming "bitmask".
- **Bitwise score / maximize AND-OR:** Flip at most $k$ bits or OR values together to maximize AND / minimize XOR — Amazon / Google OA style.
- **Hidden bit DP:** Assignment / elevator / TSP-on-$n\le20$ graphs — state is "set of used people/nodes"; interviewers call it DP, the encoding is a bitmask.
