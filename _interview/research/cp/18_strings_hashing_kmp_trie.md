# 18 — Strings: Hashing, KMP / Z-function, Trie

**Placement value:** High (pattern matching, tries, and rolling hashes show up constantly in OAs; KMP/Z are the standard upgrade from naive search)
**Prereq topics:** Arrays, Strings basics, Prefix sums, Binary search, DFS / backtracking (for trie+grid)

**Pattern in one paragraph:** Treat strings as sequences you can compare or search in near-linear time. Rolling hash turns any substring into an $O(1)$ fingerprint (precompute prefix hashes; double-hash on CF). KMP’s $\pi$-array / Z-function answer “longest prefix that is also a suffix / matches at $i$” and unlock matching, borders, and periods in $O(n)$. A trie stores a dictionary by shared prefixes for insert/search/`startsWith`, XOR-maximization (binary trie), and multi-pattern search. Problem signals: find / count pattern occurrences, longest border / period, merge on overlapping prefix-suffix, distinct substrings under constraints, autocomplete / dictionary queries, maximize XOR with inserts/deletes.

## Ladder (easy -> hard, 26 problems)
- [ ] [Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/) — `LeetCode` `Medium` — trie insert/search/startsWith — NeetCode / Striver base template; every OA trie question builds on this. **(core)**
- [ ] [Find the Index of the First Occurrence in a String](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/) — `LeetCode` `Easy` — KMP / hashing / Z — Striver classic “needle in haystack”; forces you past naive $O(nm)$. **(core)**
- [ ] [Repeated Substring Pattern](https://leetcode.com/problems/repeated-substring-pattern/) — `LeetCode` `Easy` — period / KMP — OA-friendly: $s$ is $t$ repeated iff a border / `(s+s)[1:-1]` contains $s$. **(core)**
- [ ] [Substrings Sort](https://codeforces.com/problemset/problem/988/B) — `Codeforces` `1100` — substring containment — Light placement warm-up on nested-string ordering.
- [ ] [War of the Corporations](https://codeforces.com/problemset/problem/625/B) — `Codeforces` `1200` — pattern matching — First CF “count non-overlapping occurrences” drill before full KMP.
- [ ] [Registration System](https://codeforces.com/problemset/problem/4/C) — `Codeforces` `1300` — string map / hashing — A2OJ ladder staple; map names → next free suffix.
- [ ] [String Matching](https://cses.fi/problemset/task/1753) — `CSES` `String Algorithms` — KMP / Z / Rabin–Karp — CSES + USACO Guide focus problem; implement all three once. **(core)**
- [ ] [String Functions](https://cses.fi/problemset/task/2107) — `CSES` `String Algorithms` — Z-function + $\pi$-array — Pure template dump of both arrays; memorize before harder uses. **(core)**
- [ ] [Finding Borders](https://cses.fi/problemset/task/1732) — `CSES` `String Algorithms` — borders via $\pi$ / hashing — CSES classic; walk the KMP border chain. **(core)**
- [ ] [Finding Periods](https://cses.fi/problemset/task/1733) — `CSES` `String Algorithms` — periods via Z / hash — CSES + USACO Guide hashing module; $i$ is a period iff $i+z[i]\ge n$. **(core)**
- [ ] [Common Divisors](https://codeforces.com/problemset/problem/182/D) — `Codeforces` `1400` — string periods + hashing — Count strings that divide both inputs; period check + hash compare.
- [ ] [Design Add and Search Words Data Structure](https://leetcode.com/problems/design-add-and-search-words-data-structure/) — `LeetCode` `Medium` — trie + DFS wildcards — NeetCode; `.` wildcard forces branching DFS on the trie. **(core)**
- [ ] [Word Combinations](https://cses.fi/problemset/task/1731) — `CSES` `String Algorithms` — trie + DP — CSES / USACO Guide: ways to build a string from a dictionary. **(core)**
- [ ] [Prefix-Suffix Palindrome (Easy version)](https://codeforces.com/problemset/problem/1326/D1) — `Codeforces` `1500` — hashing / KMP palindrome — CF EDU-adjacent; longest palindrome from a prefix + a suffix. **(core)**
- [ ] [Who Says a Pun?](https://atcoder.jp/contests/abc141/tasks/abc141_e) — `AtCoder` `ABC141 E` — hashing / Z + binary search on length — Canonical ABC E for longest duplicated substring.
- [ ] [Camp Schedule](https://codeforces.com/problemset/problem/1137/B) — `Codeforces` `1600` — KMP greedy reconstruct — Rebuild using the border of the target pattern under letter budgets.
- [ ] [Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/) — `LeetCode` `Hard` — KMP on $s\,\#\,\mathrm{rev}(s)$ — Striver / interview classic for “add fewest chars in front”. **(core)**
- [ ] [Word Search II](https://leetcode.com/problems/word-search-ii/) — `LeetCode` `Hard` — trie + grid backtracking — NeetCode hard; prune DFS with a dictionary trie. **(core)**
- [ ] [Password](https://codeforces.com/problemset/problem/126/B) — `Codeforces` `1700` — Z-function (or hash + BS) — cp-algorithms / A2OJ milestone: longest string that is prefix, suffix, and interior occurrence. **(stretch)**
- [ ] [Good Substrings](https://codeforces.com/problemset/problem/271/D) — `Codeforces` `1800` — rolling hash + set — USACO Guide / cp-algorithms hashing poster child; count distinct “good” substrings. **(stretch)**
- [ ] [MUH and Cube Walls](https://codeforces.com/problemset/problem/471/D) — `Codeforces` `1800` — KMP on difference array — Pattern matching after reducing heights to adjacent diffs. **(stretch)**
- [ ] [Vasiliy's Multiset](https://codeforces.com/problemset/problem/706/D) — `Codeforces` `1800` — binary trie (XOR) — USACO / A2OJ classic: insert/delete numbers, query max XOR. **(stretch)**
- [ ] [Prefix-Suffix Palindrome (Hard version)](https://codeforces.com/problemset/problem/1326/D2) — `Codeforces` `1800` — Manacher / hash / KMP — Same as D1 under large $n$; forces a linear palindrome tool. **(stretch)**
- [ ] [Compress Words](https://codeforces.com/problemset/problem/1200/E) — `Codeforces` `2000` — KMP / hashing merge — CF EDU favourite: repeatedly glue on the longest overlapping prefix-suffix. **(stretch)**
- [ ] [Prefixes and Suffixes](https://codeforces.com/problemset/problem/432/D) — `Codeforces` `2000` — Z / $\pi$ + occurrence counts — Famous Codeforces EDU-style milestone on borders that are also prefixes. **(stretch)**
- [ ] [Finding Patterns](https://cses.fi/problemset/task/2102) — `CSES` `String Algorithms` — suffix array / automaton — CSES suffix-structure entry: multi-pattern existence queries. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- Rolling-hash template: prefix hashes, $O(1)$ substring hash, two mods (or $2^{61}-1$), base $>|\Sigma|$, map `'a'\mapsto 1$ (never $0$).
- Write $\pi$-array (KMP failure) and Z-function from memory; convert matching into a single concatenated string with a sentinel.
- Recover all borders by repeatedly jumping $\pi[i]-1$; detect periods from Z / borders.
- Trie node: `next[26]` / map + `isEnd` (+ optional `cnt`); DFS for `.` wildcards; prune Word-Search-style board DFS through the trie.
- Binary trie for max-XOR with insert/delete and path counts.
- Know when to prefer hash (flexible compares / BS on length) vs KMP/Z (exact linear, no collision worry) vs trie (many patterns / prefixes).
- (stretch) Build a suffix array or use a suffix automaton enough to solve CSES Finding Patterns / Distinct Substrings.

## Where it appears in OAs / interviews
- **Dictionary / autocomplete APIs:** implement Trie with `insert` / `search` / `startsWith`, sometimes with `.` wildcards (LC 208 / 211 style — Amazon, Google phone screens).
- **Needle in haystack / period checks:** “first index of pattern”, “is the string a repeated block”, “shortest palindrome by prepending” — KMP or hashing in timed OAs.
- **Grid word hunt:** find all dictionary words on a board (Word Search II) — trie + backtracking is the expected optimal path.
- **Contest-style CP:** overlapping word compression, good-substring counts, and max-XOR multiset queries (CF hashing / binary-trie patterns) show up in online assessments that copy Codeforces Div. 2 C/D ideas.
