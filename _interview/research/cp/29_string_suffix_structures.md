# 29 — String Suffix Structures: Suffix Array, Suffix Automaton, Aho–Corasick

**Placement value:** Medium — almost never a literal OA template (Striver skips these), but multi-pattern dictionary search, distinct/repeated substrings, and “k-th substring” show up in harder screens; primarily Candidate Master rating-builders.
**Prereq topics:** Strings (hashing, KMP / Z-function, trie), sorting + radix intuition, binary search, basic DP, DFS on trees (fail / link trees)

**Pattern in one paragraph:** Index *all* substrings of a text (or a dictionary) so queries become walks or binary searches, not $O(n^2)$ scans. **Suffix array (SA)** = sorted list of suffix starts; pair with **LCP** (Kasai) for adjacent overlaps — distinct count $= n(n+1)/2 - \sum\mathrm{LCP}$, longest repeat $= \max\mathrm{LCP}$, pattern search = binary search on SA. **Suffix automaton (SAM)** = minimal DFA of all substrings ($O(n)$ states); `len[v] - len[link[v]]` = new distinct substrings ending in state $v$; `endpos` / link-tree DP for occurrences. **Aho–Corasick (AC)** = trie of many patterns + KMP-style fail links — scan the text once and aggregate matches on the fail tree. Signals: “many patterns vs one text”, “count distinct / k-th / repeating substrings”, “substring that appears in ≥2 places”, “build string avoiding / forcing a pattern”.

## Ladder (easy -> hard, 26 problems)
- [ ] [Number of Substrings](https://atcoder.jp/contests/practice2/tasks/practice2_i) — `AtCoder` `ACL Practice I` — SA + LCP distinct count — ACL `suffix_array` / `lcp_array` template; formula $n(n+1)/2-\sum\mathrm{LCP}$. **(core)**
- [ ] [Distinct Substrings](https://cses.fi/problemset/task/2105) — `CSES` `String Algorithms` — SA+LCP or SAM — CSES / USACO Guide / cp-algorithms staple; implement both once. **(core)**
- [ ] [Repeating Substring](https://cses.fi/problemset/task/2106) — `CSES` `String Algorithms` — max LCP — Longest substring with ≥2 occurrences = max adjacent LCP. **(core)**
- [ ] [Minimal Rotation](https://cses.fi/problemset/task/1110) — `CSES` `String Algorithms` — Booth / SA of $s+s$ — Least cyclic shift; SA on $s+s$ or Booth’s $O(n)$. **(core)**
- [ ] [Finding Patterns](https://cses.fi/problemset/task/2102) — `CSES` `String Algorithms` — SA binsearch or AC — Multi-pattern existence in one text; SA range or Aho walk. **(core)**
- [ ] [Counting Patterns](https://cses.fi/problemset/task/2103) — `CSES` `String Algorithms` — AC fail-tree counts — Mark visits on AC nodes, push counts up the fail tree. **(core)**
- [ ] [Pattern Positions](https://cses.fi/problemset/task/2104) — `CSES` `String Algorithms` — AC / SA first index — Same automaton, report leftmost occurrence per pattern. **(core)**
- [ ] [Word Combinations](https://cses.fi/problemset/task/1731) — `CSES` `String Algorithms` — AC / trie + DP — Ways to build a string from a dictionary; AC speeds matching inside DP. **(core)**
- [ ] [Required Substring](https://cses.fi/problemset/task/1112) — `CSES` `String Algorithms` — pattern automaton DP — Count length-$n$ strings that contain a given pattern (KMP/AC state DP). **(core)**
- [ ] [Erase and Extend (Easy Version)](https://codeforces.com/problemset/problem/1537/E1) — `Codeforces` `1600` — lex-smallest via SA / dueling — Build shortest string by erase-prefix + append under a length cap. **(core)**
- [ ] [Spy Syndrome 2](https://codeforces.com/problemset/problem/633/C) — `Codeforces` `1900` — reverse trie decode — Recover a word segmentation from a ciphertext; dictionary trie on reversed words.
- [ ] [Division + LCP (easy version)](https://codeforces.com/problemset/problem/1968/G1) — `Codeforces` `1900` — LCP / Z periods — Max pieces equal to a prefix; Z/LCP period checks. **(core)**
- [ ] [Common Prefixes](https://atcoder.jp/contests/abc213/tasks/abc213_f) — `AtCoder` `ABC213 F` — SA + LCP stack — Sum of LCP between every pair of suffixes via SA order + monotonic stack.
- [ ] [Substring Distribution](https://cses.fi/problemset/task/2110) — `CSES` `String Algorithms` — SA+LCP by length — How many distinct substrings of each length; difference-array on LCP contributions. **(core)**
- [ ] [Substring Order I](https://cses.fi/problemset/task/2108) — `CSES` `String Algorithms` — k-th distinct substring — Walk SA/SAM counting new prefixes per state. **(core)**
- [ ] [Count Substring Query](https://atcoder.jp/contests/abc362/tasks/abc362_g) — `AtCoder` `ABC362 G` — SA occurrence queries — Count suffixes with a given pattern as prefix; SA + binary search (ACL).
- [ ] [Watto and Mechanism](https://codeforces.com/problemset/problem/514/C) — `Codeforces` `2000` — trie ±1 mismatch — Dictionary membership with exactly one change; classic trie / hashing hybrid.
- [ ] [String](https://codeforces.com/problemset/problem/128/B) — `Codeforces` `2100` — k-th substring SA/SAM — Lex-ordered list of *all* (multiplicity) substrings; SA+LCP or SAM path counts. **(stretch)**
- [ ] [Two Strings](https://atcoder.jp/contests/abc272/tasks/abc272_f) — `AtCoder` `ABC272 F` — SA of carefully padded concat — Count pairs of cyclic shifts with $f(S,i)\le f(T,j)$. **(stretch)**
- [ ] [Substring Order II](https://cses.fi/problemset/task/2109) — `CSES` `String Algorithms` — k-th with multiplicity — SAM `endpos` sizes × path DP; harder twin of Order I. **(stretch)**
- [ ] [Inverse Suffix Array](https://cses.fi/problemset/task/3225) — `CSES` `String Algorithms` — reconstruct from SA — Given a permutation, recover any string that produces it (or impossible). **(stretch)**
- [ ] [String Transform](https://cses.fi/problemset/task/1113) — `CSES` `String Algorithms` — BWT inverse — Invert Burrows–Wheeler; SA / last-to-first mapping. **(stretch)**
- [ ] [Match & Catch](https://codeforces.com/problemset/problem/427/D) — `Codeforces` `2200` — unique LCS via SAM/SA — Shortest string that appears once in each of two texts. **(stretch)**
- [ ] [Erase and Extend (Hard Version)](https://codeforces.com/problemset/problem/1537/E2) — `Codeforces` `2200` — same as E1, large $n$ — Forces linear / $O(n\log n)$ SA or dueling, not $O(n^2)$. **(stretch)**
- [ ] [Division + LCP (hard version)](https://codeforces.com/problemset/problem/1968/G2) — `Codeforces` `2200` — LCP / Z + math — Hard twin of G1 under tighter constraints. **(stretch)**
- [ ] [Deletion of Repeats](https://codeforces.com/problemset/problem/19/C) — `Codeforces` `2200` — SA / hashing repeats — Delete a repeated block greedily; suffix-structure or hash classic. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- Build SA in $O(n\log n)$ (doubling + radix) or call ACL `suffix_array`; always build Kasai LCP in $O(n)$ next.
- Distinct substrings: $n(n+1)/2 - \sum\mathrm{LCP}[i]$; longest repeating substring length = $\max\mathrm{LCP}$.
- Pattern in text: binary-search the SA for the first/last suffix with that prefix ($O(|P|\log n)$ compares).
- SAM node fields: `next[]`, `link`, `len` (+ `firstpos` / `endpos` size); online `sam_extend(c)`; distinct $= \sum(\mathrm{len}[v]-\mathrm{len}[\mathrm{link}[v]])$.
- Occurrence counts: propagate `endpos` sizes up the SAM link tree (larger `len` → smaller); clone nodes start at 0.
- Aho–Corasick: insert patterns into a trie, BFS fail links (`fail` = KMP on the trie), `go(v,c)` transitions; exit/output links for matches.
- Multi-pattern counts: while scanning the text, `++cnt[state]`, then sum `cnt` over fail-tree subtrees (or push to parent).
- Automaton DP: states = KMP/AC/SAM nodes; transitions on next character; mark “accepted / forbidden” for contain/avoid problems.
- Pick tool: one pattern → KMP/Z/hash; many patterns → AC; all-substring aggregates / k-th / LCS of two strings → SA+LCP or SAM.

## Where it appears in OAs / interviews
- **Longest duplicated / repeated substring:** “longest substring that appears ≥ twice” → max LCP (or binary search + hash); LC-style Hard screens.
- **Dictionary / multi-needle search:** “find which of these keywords appear in the document” → Aho–Corasick (or SA if one fixed text, many queries).
- **Distinct substrings / k-th substring:** count or report the k-th lex substring — SA+LCP or SAM path DP (CSES Order I/II / CF 128B shape).
- **Harder CP assessments:** cyclic minimal rotation, “string must contain pattern $P$”, or lex-smallest build under erase/append ops (CSES Required Substring / CF Erase and Extend).
