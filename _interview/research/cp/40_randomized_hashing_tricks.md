# 40 — Randomized algorithms & hashing tricks

**Placement value:** Medium — custom/`unordered_map` safety and pair-sum / set-hash tricks show up in OAs; random-sample & Zobrist are CF/AtCoder rating skills Striver never covers.
**Prereq topics:** Hash maps / sets, modular arithmetic, basic probability (independence, union bound), binary search, interactive I/O (for the pivot/sample problems), string hashing basics (from topic 18)
**Pattern in one paragraph:** When a deterministic scan is too slow or a structure is hard to compare, inject randomness. **Birthday / pigeonhole:** after ~√M samples into a space of size M you expect a collision — use it for pair-sum equals, anti-hash sizing, and “have I seen this fingerprint?”. **Random pivots / samples:** if a good object occupies ≥1/k of the space, pick O(k log(1/ε)) random candidates and verify (majority queries, interactive lower_bound, geometry). **Zobrist / XOR hashing:** assign each value a random 64-bit id; XOR (or mod-P sum) is a fingerprint of a set / parity-multiset — equal fingerprints ⇒ equal sets w.h.p.; seed RNG from the clock so open hacks fail. Signals: “≥ half / third of the range”, interactive query limits too small for full scans, “are these two sets/multisets equal?”, “is every frequency even / a multiple of 3?”, “find any collision among pairs”.

## Ladder (easy -> hard, 24 problems)
- [ ] [Registration System](https://codeforces.com/problemset/problem/4/C) — `Codeforces` `1300` — hash map — **(core)** OA staple; first CF “string → frequency map” drill (and why you later need an anti-hash)
- [ ] [Summarize to the Power of Two](https://codeforces.com/problemset/problem/1005/C) — `Codeforces` `1300` — hash set lookups — **(core)** placement classic; for each `a_i` probe `2^k−a_i` — use a custom/`splitmix64` hash on CF to avoid TLE hacks
- [ ] [Diluc and Kaeya](https://codeforces.com/problemset/problem/1536/C) — `Codeforces` `1500` — hash of reduced ratios — prefix `(D,K)` counts → `map` of `D/g : K/g`; teaches hashing pairs, not strings
- [ ] [Empty Triangle](https://codeforces.com/problemset/problem/2074/E) — `Codeforces` `1600` — random sample interactive — **(core)** modern Div. 3; keep sampling 3 random points until the triangle is empty (query budget forces randomness)
- [ ] [Prefix Equality](https://atcoder.jp/contests/abc250/tasks/abc250_e) — `AtCoder` `ABC250 E` — Zobrist set hash — **(core)** USACO Guide XOR-hash focus; random 64-bit per value, prefix XOR of *first* occurrences, compare sets in O(1)
- [ ] [Three Days Ago](https://atcoder.jp/contests/abc295/tasks/abc295_d) — `AtCoder` `ABC295 D` — Zobrist parity — **(core)** count substrings where every digit appears even times = count equal prefix XOR hashes
- [ ] [Going Home](https://codeforces.com/problemset/problem/1500/A) — `Codeforces` `1800` — birthday / pigeonhole pair sums — **(core)** find `a_x+a_y=a_z+a_w`; store one pair per sum — after O(max a) pairs a collision is forced
- [ ] [Tournament Countdown](https://codeforces.com/problemset/problem/1713/D) — `Codeforces` `1800` — random elimination interactive — **(core)** query 4 random alive players, drop two losers; expected O(n) queries to crown the winner
- [ ] [Guess the Cycle Size](https://codeforces.com/problemset/problem/1729/E) — `Codeforces` `1800` — random queries + birthday — **(core)** random vertex pairs until a cycle-distance collision reveals `n`; classic interactive birthday
- [ ] [Power Products](https://codeforces.com/problemset/problem/1225/D) — `Codeforces` `1800` — hash of prime-exponent signature — strip exponents mod `k`, look for complementary signature in a map
- [ ] [Robin Hood Archery](https://codeforces.com/problemset/problem/2014/H) — `Codeforces` `1900` — Zobrist even-frequency — **(core)** range is “all even counts” iff prefix XOR-hashes match; modern Div. 3 H Zobrist template
- [ ] [Rearrange Query](https://atcoder.jp/contests/abc367/tasks/abc367_f) — `AtCoder` `ABC367 F` — multiset hash — **(core)** random id per value + prefix *sums* (not XOR) to compare multisets on ranges
- [ ] [Interactive LowerBound](https://codeforces.com/problemset/problem/843/B) — `Codeforces` `2000` — random pivots — **(core)** *the* CF random-pivot classic: sample ~√n random nodes, jump from the best ≤x predecessor
- [ ] [Something with XOR Queries](https://codeforces.com/problemset/problem/870/D) — `Codeforces` `2000` — random interactive XOR — reconstruct a hidden permutation via random `a_i⊕a_j` queries
- [ ] [Watto and Mechanism](https://codeforces.com/problemset/problem/514/C) — `Codeforces` `2000` — polyhash set + 1-edit — **(core)** store rolling hashes; query = any hash differing in exactly one position (double-hash / big mod for birthday safety)
- [ ] [Pair Of Lines](https://codeforces.com/problemset/problem/961/D) — `Codeforces` `2000` — random / candidate lines — cover points by 2 lines; randomize first line through two points, or check the 3 canonical pairs
- [ ] [Check Transcription](https://codeforces.com/problemset/problem/1056/E) — `Codeforces` `2100` — hash + birthday-safe compare — **(stretch)** USACO Guide hashing; assign `0/1` blocks to pattern letters and verify the split
- [ ] [Subway Pursuit](https://codeforces.com/problemset/problem/1039/B) — `Codeforces` `2100` — randomized shrinking search — **(stretch)** interactive: binary-search the range, then randomly probe when the window is still large
- [ ] [Buratsuta 3](https://codeforces.com/problemset/problem/2149/G) — `Codeforces` `2100` — random sample majority — **(stretch)** modern Div. 3 G; sample ~50 positions per query to hit every >⌊len/3⌋ value w.h.p.
- [ ] [Preorder](https://codeforces.com/problemset/problem/1671/E) — `Codeforces` `2100` — tree hashing — **(stretch)** hash rooted binary-tree shapes (min of swapped-child hashes) to count distinct / good labelings
- [ ] [Arithmetic Progression](https://codeforces.com/problemset/problem/1114/E) — `Codeforces` `2200` — random sample + gcd — **(stretch)** interactive: find max by `> x` BS, sample ~30 random `a_i`, gcd of diffs → `d`
- [ ] [ZS and The Birthday Paradox](https://codeforces.com/problemset/problem/711/E) — `Codeforces` `2300` — birthday probability math — **(stretch)** exact `P(collision)` among `k` people over `2^n` days as reduced `A/B` mod `10^6+3`
- [ ] [Ghd](https://codeforces.com/problemset/problem/364/D) — `Codeforces` `2900` — random sample ≥1/2 — **(stretch)** Errichto / USACO Guide Randomness milestone; sample ~15 `a_i`, try their divisors as Ghd candidates
- [ ] [Three Occurrences](https://codeforces.com/problemset/problem/1418/G) — `Codeforces` `2500` — XOR / trit hashing — **(stretch)** USACO Guide XOR-hash hard; random ids + base-3 digit sum so each value appears ×3 ⇒ hash 0

## Must-internalize checklist (5-10 bullets)
- RNG: `mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());` + `uniform_int_distribution`; never fixed seeds on CF open-hacking; avoid raw `rand()` / `RAND_MAX`.
- Anti-hash: custom hash for `unordered_map`/`gp_hash_table` (e.g. `splitmix64` xor’d with a random salt); or just use `map` when TL allows.
- Birthday rule of thumb: collision among `m` hashes into modulus `M` has prob ~`m²/M`; for string/set fingerprints prefer 64-bit (`2^61−1` or unsigned overflow) or **two** independent hashes.
- Zobrist template: `h[v] = rng();`, set hash = XOR of `h[v]` for members; toggle add/remove with another XOR; for multisets use `+` mod big prime (or 128-bit) instead of XOR.
- Random sample when a target occupies ≥`1/k` of positions: `T ≈ k·ln(1/ε)` trials ⇒ fail prob ≤`ε`; verify each candidate in `O(log n)` (position lists) or `O(len)`.
- Random pivot (Las Vegas): sample candidates, pick the best feasible pivot, finish with a short deterministic walk / recurse — expected `O(√n)` or `O(n)` depending on the problem (843B / Quickselect intuition).
- Interactive hygiene: flush (`endl` / `cout.flush()`), respect query caps, treat `-1` as immediate exit.
- Know Monte Carlo (tiny error OK, e.g. Zobrist) vs Las Vegas (always correct, runtime random).

## Where it appears in OAs / interviews
- “For each element, is there another that sums with it to a power of two / target?” → hash set with complementary lookup (1005C-style); interviewers expect O(n) with a set, not O(n²).
- “Count ways to split so far with the same D:K ratio / same reduced fraction” → hash pairs `(a/g,b/g)` (Diluc / Zero-Quantity family) — common in OA “running condition” problems.
- “Do these two windows contain the same multiset of values?” → sort+compare is the safe interview answer; Zobrist/sum-hash is the CF speed trick (ABC367F / Prefix Equality).
- “Interactive: find the answer with too few queries to scan everything” → sample randomly, then binary-search / walk from the best sample (LowerBound / AP / Subway Pursuit) — shows up in Codeforces-style company contests more than classic phone screens.
