# 30 — Strings Advanced: Manacher, Z / Hashing, Palindromic Structures

**Placement value:** Medium (LPS / “is substring a palindrome?” show up in OAs via expand-around-center or hash; full Manacher, Z-period tricks, and k-palindrome DP are mainly CF rating builders toward ~2100)
**Prereq topics:** Rolling hash (double mod), Z-function / $\pi$-array (topic 18), binary search on length, Fenwick or segment tree (for hash updates), basic interval DP

**Pattern in one paragraph:** Palindromes are symmetric substrings; under $n\le 10^6$ you need a linear “all centers” tool (Manacher’s $d_{\mathrm{odd}}/d_{\mathrm{even}}$, or hash + binary search per center) instead of $O(n^2)$ expand. Forward/reverse rolling hashes give $O(1)$ “is $s[l..r]$ a palindrome?” and power Z / period arguments for “longest border that also appears inside”, glue-on-overlap merges, and $(AB)^kA$-style prefixes. Higher structure = k-palindromes (half is also a palindrome), palindrome-count DP on ranges, and (stretch) reconstructing a string from Manacher radii. Spot it when the statement asks for longest / count / queries of palindromic substrings, prefix+suffix palindrome builds, or period constraints with $n$ too large for quadratic DP.

## Ladder (easy -> hard, 24 problems)
- [ ] [Common Divisors](https://codeforces.com/problemset/problem/182/D) — `Codeforces` `1400` — period + hash equality — Count strings that divide both inputs; forces “$t$ is a period of $s$ iff hash-blocks match”. **(core)**
- [ ] [Prefix-Suffix Palindrome (Easy version)](https://codeforces.com/problemset/problem/1326/D1) — `Codeforces` `1500` — hash / KMP palindrome — Take matching prefix+suffix shell, then longest palindromic extension of the middle; OA-flavoured CF classic. **(core)**
- [ ] [Palindrome pairs](https://codeforces.com/problemset/problem/159/D) — `Codeforces` `1500` — all centers / Manacher radii — Count pairs of non-overlapping palindromic substrings; first “use every center’s radius” drill. **(core)**
- [ ] [Spelling Check](https://codeforces.com/problemset/problem/39/J) — `Codeforces` `1500` — hash, one deletion — Which index to drop so $s$ becomes $t$; prefix/suffix hash equality, not edit DP.
- [ ] [Longest Palindrome](https://cses.fi/problemset/task/1111) — `CSES` `String Algorithms` — Manacher LPS — Canonical $n\le 10^6$ Manacher template; cp-algorithms + CSES milestone. **(core)**
- [ ] [Erase and Extend (Easy Version)](https://codeforces.com/problemset/problem/1537/E1) — `Codeforces` `1600` — Z / lex cyclic build — Erase a suffix then repeat the remainder; Z (or hash) replaces $O(n^2)$ string compares.
- [ ] [Palindrome Pairs](https://codeforces.com/problemset/problem/1045/I) — `Codeforces` `1600` — hash / bitmask of counts — Count pairs that concatenate to a palindrome; frequency parity + hash map.
- [ ] [Who Says a Pun?](https://atcoder.jp/contests/abc141/tasks/abc141_e) — `AtCoder` `ABC141 E` — hash / Z + BS on length — Longest duplicated substring; standard ABC E for “BS length, hash-check occurrence”. **(core)**
- [ ] [Password](https://codeforces.com/problemset/problem/126/B) — `Codeforces` `1700` — Z-function (or hash + BS) — Longest string that is prefix, suffix, *and* an interior occurrence; Z-milestone on every sheet. **(core)**
- [ ] [Equivalent Strings](https://codeforces.com/problemset/problem/559/B) — `Codeforces` `1700` — D&C hash equality — Even-length halves equivalent in either order; hash both half-orders, recurse. **(core)**
- [ ] [Palindrome Queries](https://cses.fi/problemset/task/2420) — `CSES` `String Algorithms` — forward/reverse hash + Fenwick — Point updates + “is $s[a..b]$ a palindrome?”; dynamic hash black-box. **(core)**
- [ ] [Prefix-Suffix Palindrome (Hard version)](https://codeforces.com/problemset/problem/1326/D2) — `Codeforces` `1800` — Manacher / hash / KMP — Same as D1 with $n\le 10^6$; forces linear palindrome tool. **(core)**
- [ ] [Queries for Number of Palindromes](https://codeforces.com/problemset/problem/245/H) — `Codeforces` `1800` — palindrome DP + prefix sums — Precompute `isPal[l][r]` then 2D prefix for $q$ range counts; classic $n\le 5000$ structure problem. **(core)**
- [ ] [Palindrome Shuffle](https://codeforces.com/problemset/problem/2069/D) — `Codeforces` `1800` — hash + two pointers — Shortest prefix to shuffle into a palindrome; hash verifies candidate middles.
- [ ] [ABCBAC](https://atcoder.jp/contests/abc284/tasks/abc284_f) — `AtCoder` `ABC284 F` — Z on $A{+}B$ and $B{+}A$ — Recover $S$ and cut from $T=f_i(S)$; ACL Z drill. **(core)**
- [ ] [Palindromic characteristics](https://codeforces.com/problemset/problem/835/D) — `Codeforces` `1900` — k-palindrome hash DP — Count substrings that are $k$-palindromes (half is $(k{-}1)$-pal); hash + degree DP. **(core)**
- [ ] [Palindromes](https://codeforces.com/problemset/problem/137/D) — `Codeforces` `1900` — DP partition into $\le k$ pals — Min changes so $s$ splits into $\le k$ palindromes; reconstruct the cuts. **(stretch)**
- [ ] [Division + LCP (easy version)](https://codeforces.com/problemset/problem/1968/G1) — `Codeforces` `1900` — Z / hash LCP — Max times you can cut equal-LCP blocks; advanced Z/hash on periods. **(stretch)**
- [ ] [Non-Palindromic Substring](https://codeforces.com/problemset/problem/1943/B) — `Codeforces` `2000` — hash range palindrome checks — Query $f(s[l..r])$ via which lengths admit a non-palindrome; $O(1)$ pal-check black box. **(stretch)**
- [ ] [Compress Words](https://codeforces.com/problemset/problem/1200/E) — `Codeforces` `2000` — KMP / hashing merge — Glue words on longest overlapping prefix-suffix; CF EDU-style hash/Z application. **(stretch)**
- [ ] [Prefixes and Suffixes](https://codeforces.com/problemset/problem/432/D) — `Codeforces` `2000` — Z / $\pi$ + occurrence counts — All borders that are also prefixes, with occurrence counts; Z milestone. **(stretch)**
- [ ] [Palindrome Degree](https://codeforces.com/problemset/problem/7/D) — `Codeforces` `2200` — hash + recursive pal-degree — Sum of k-palindrome degrees of all prefixes; $n\le 5\cdot 10^6$ forces pure hash. **(stretch)**
- [ ] [Om Nom and Necklace](https://codeforces.com/problemset/problem/526/D) — `Codeforces` `2200` — Z / KMP periods — Mark prefixes of form $(AB)^kA$; linear period arithmetic. **(stretch)**
- [ ] [Palindrome Construction](https://atcoder.jp/contests/abc349/tasks/abc349_g) — `AtCoder` `ABC349 G` — Manacher radii → string — Given odd radii $A_i$, build lex-smallest $S$ (or impossible); Manacher as a constraint system. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- Manacher template: compute $d_{\mathrm{odd}}[i]$ / $d_{\mathrm{even}}[i]$ (or `#`-joined odd-only) in $O(n)$; recover LPS and “longest palindrome centered at $i$”.
- Palindrome black box: forward + reverse prefix hashes ⇒ $s[l..r]$ is a palindrome iff $\mathrm{hash}(l,r)=\mathrm{hash}_{\mathrm{rev}}(n-r+1,n-l+1)$ in $O(1)$.
- Hash + Fenwick/seg for point updates (CSES Palindrome Queries); never rebuild $O(n)$ hashes per query.
- Z / $\pi$ from memory; Password / Prefixes-and-Suffixes pattern: longest border that also occurs strictly inside.
- Prefix–suffix palindrome build (1326D1/D2): peel matching shell, then Manacher/hash the remaining middle from both ends.
- k-palindrome recurrence: if $s[l..r]$ is a palindrome and the left half is $(k{-}1)$-pal, degree rises (835D / 7D).
- Range palindrome counts: `isPal[l][r]` from shorter lengths, then 2D prefix sums for queries (245H) when $n\le 5000$.
- Period checks via Z/hash: $i$ is a period iff blocks of length $i$ match; necklace / common-divisor style.
- (stretch) Treat Manacher radii as equality constraints between mirrored positions (ABC349 G).

## Where it appears in OAs / interviews
- **Longest palindromic substring / count palindromic substrings** — expand-around-center is the interview default; knowing Manacher (or hash+BS) is the CP upgrade when $n$ hits $10^6$ (CSES / CF D2).
- **“Make it a palindrome with fewest front inserts / prefix+suffix keep”** — Shortest Palindrome / Prefix-Suffix Palindrome style prompts in timed OAs; KMP on $s\#\mathrm{rev}(s)$ or Manacher on the middle.
- **“Is this range a palindrome after edits?”** — forward/reverse hash with updates (CSES Palindrome Queries pattern) appears in online assessments that copy CF string-hash ideas.
- **Contest Div. 2 D/E:** k-palindrome counts, Z-password borders, and compress-on-overlap merges are the rating stretch after the OA core.
