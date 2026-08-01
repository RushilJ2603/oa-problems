# 18 — Strings: Hashing, KMP / Z-function, Trie — Depth Pass

**Placement value:** High — second wave after CSES String Matching / Borders / Periods, Password, Good Substrings, Compress Words, and binary-trie Vasiliy; these hide period constraints, hash-equality trees, trie DP, and KMP-on-compressed / KMP+DP rather than announcing the template.
**Prereq topics:** Rolling hash (double mod), $\pi$-array / Z-function, trie insert/search, binary trie XOR; the standard Strings ladder (CSES string set, Password, Good Substrings, Compress Words, Vasiliy’s Multiset)
**Pattern in one paragraph:** After the famous set, contests stop saying “run KMP” and instead leave a border/period invariant, a dictionary of fragments to glue, a one-mismatch query, or a tiny automaton state. Depth-pass states still look like “compare substrings”, “longest prefix that is also suffix”, or “walk a trie”, but the *extra* work is non-obvious: consistency of forced pattern placements via $\pi$, reverse-trie decoding, hash of every even-split equality class, KMP on run-length blocks, DP on automaton nodes (forbidden / required pattern), or binary-trie counts of XOR prefixes. Spot it when $n\le 10^6$ forces linear string tools, when “exactly one change / one deletion” appears, when answers are counts of strings containing a pattern, or when a dictionary is searched *backwards*.

## Ladder (easy -> hard, 25 problems)

- [ ] [String Typing](https://codeforces.com/problemset/problem/954/B) — `Codeforces` `1400` — period / copy-from-prefix — **(core)** maximize typed length by duplicating a prefix; forces “what prefixes are periods of the whole string”
- [ ] [Message Transmission Error (easy version)](https://codeforces.com/problemset/problem/2010/C1) — `Codeforces` `1400` — border that covers — **(core)** find a string that is both a proper prefix and proper suffix and whose doubled form covers $s$; border / $\pi$ warm-up past CSES Borders
- [ ] [Spelling Check](https://codeforces.com/problemset/problem/39/J) — `Codeforces` `1500` — hash + one deletion — **(core)** which single index to drop so $s$ becomes $t$; prefix/suffix hash equality, not full edit distance
- [ ] [Nearly Shortest Repeating Substring](https://codeforces.com/problemset/problem/1950/E) — `Codeforces` `1500` — period divisors — **(core)** shortest $t$ with $s\approx t+t+\cdots$ allowing $\le 1$ mismatch per block; check divisors of $n$ with hash
- [ ] [Erase and Extend (Easy Version)](https://codeforces.com/problemset/problem/1537/E1) — `Codeforces` `1600` — Z / lex-smallest cyclic build — **(core)** erase a suffix then extend by repeating the remainder; compare candidates via Z or hash, not $O(n^2)$ string compares
- [ ] [Obtain The String](https://codeforces.com/problemset/problem/1295/C) — `Codeforces` `1600` — next-occurrence jumps — **(core)** build $t$ as subsequence of repeats of $s$; preprocess `nxt[i][c]` like a 1-letter automaton
- [ ] [Color with Occurrences](https://codeforces.com/problemset/problem/1714/D) — `Codeforces` `1600` — cover string by dictionary — **(core)** greedily / DP-cover $t$ with given patterns as substrings; multi-pattern matching without needing full Aho
- [ ] [Required Substring](https://cses.fi/problemset/task/1112) — `CSES` `String Algorithms` — KMP automaton + DP — **(core)** count length-$n$ strings containing a fixed pattern; state = current $\pi$ match length
- [ ] [Equivalent Strings](https://codeforces.com/problemset/problem/559/B) — `Codeforces` `1700` — D&C hash equality — **(core)** two strings equivalent under even splits; recurse on halves or hash both orders of each half
- [ ] [Hacking Cypher](https://codeforces.com/problemset/problem/490/C) — `Codeforces` `1700` — prefix/suffix modular hash — **(core)** split so left $\equiv 0\pmod a$ and right $\equiv 0\pmod b$ with no leading zero; rolling numeric hash
- [ ] [Prefixes and Suffixes](https://codeforces.com/problemset/problem/1092/C) — `Codeforces` `1700` — reconstruct from $2n-2$ borders — **(core)** *not* 432D: given all proper prefixes/suffixes shuffled, recover $s$ and label each as P/S
- [ ] [Message Transmission Error (hard version)](https://codeforces.com/problemset/problem/2010/C2) — `Codeforces` `1700` — hash / Z under large $n$ — **(core)** same border-cover idea as C1 with $n\le 10^6$; linear string tool required
- [ ] [ABCBAC](https://atcoder.jp/contests/abc284/tasks/abc284_f) — `AtCoder` `ABC284 F (~1800 CF-eq)` — Z on $A{+}B$ and $B{+}A$ — **(core)** recover $S$ and cut $i$ from $T=f_i(S)$; canonical ACL Z drill
- [ ] [Tavas and Malekas](https://codeforces.com/problemset/problem/535/D) — `Codeforces` `1900` — forced placements + $\pi$ — **(stretch)** given required starts of $p$ inside $s$, check overlaps via $\pi$, then $26^{\#\text{free}}$ for the rest
- [ ] [Spy Syndrome 2](https://codeforces.com/problemset/problem/633/C) — `Codeforces` `1900` — reverse trie + DP — **(stretch)** decode a lowercased ciphertext using a dictionary trie built on *reversed* words
- [ ] [Palindromic characteristics](https://codeforces.com/problemset/problem/835/D) — `Codeforces` `1900` — hash palindrome DP — **(stretch)** count $k$-palindromes; $s[l..r]$ palindrome via hash, then DP on degree
- [ ] [A Lot of Games](https://codeforces.com/problemset/problem/455/B) — `Codeforces` `1900` — trie game theory — **(stretch)** insert dictionary into a trie; win/lose on “can move / can force opponent into leaf”
- [ ] [Watto and Mechanism](https://codeforces.com/problemset/problem/514/C) — `Codeforces` `2000` — trie / hash, exactly one mismatch — **(stretch)** membership with Hamming distance 1; branch once in a trie or probe three hashes
- [ ] [Obsessive String](https://codeforces.com/problemset/problem/494/B) — `Codeforces` `2000` — KMP + DP on matches — **(stretch)** count substrings that contain $t$ as a substring; combine occurrence ends from $\pi$ with prefix DP
- [ ] [Lucky Common Subsequence](https://codeforces.com/problemset/problem/346/B) — `Codeforces` `2000` — LCS DP + KMP forbid — **(stretch)** LCS of two strings that must *not* contain virus $v$; keep $\pi$-state of $v$ in the DP
- [ ] [Check Transcription](https://codeforces.com/problemset/problem/1056/E) — `Codeforces` `2100` — hash map $0/1\to$ blocks — **(stretch)** pattern of 0/1 over a long string; try length of the `0`-block, verify with rolling hashes
- [ ] [Messenger](https://codeforces.com/problemset/problem/631/D) — `Codeforces` `2100` — KMP on run-length blocks — **(stretch)** match compressed pattern inside compressed text; middle blocks exact, ends as prefix/suffix of a run
- [ ] [Compress String](https://codeforces.com/problemset/problem/1120/C) — `Codeforces` `2100` — DP + Z/hash segments — **(stretch)** min cost to build $s$ by adding a char or copying a prior substring; $z$ from each start, or hash+BS
- [ ] [Beautiful Subarrays](https://codeforces.com/problemset/problem/665/E) — `Codeforces` `2100` — binary trie XOR counts — **(stretch)** count subarrays with XOR $\ge k$; insert prefix XORs into a bit trie (count path, not only max)
- [ ] [Two strings](https://codeforces.com/problemset/problem/762/C) — `Codeforces` `2100` — hash + BS deleted middle — **(stretch)** delete one substring of $a$ so remainder is subsequence of $b$; pref/suff match lengths via two pointers or hash

## Must-internalize checklist (technique notes)

- **Forced placements + $\pi$:** when several starts of $p$ are required inside $s$, an overlap of length $\ell$ is legal iff $p$’s border chain / period divides the gap (Tavas and Malekas); free cells then contribute $26^{\mathrm{cnt}}$.
- **Reverse trie decoding:** store dictionary words reversed; DP from the end of the ciphertext, walking the trie forward = matching a word ending here (Spy Syndrome 2).
- **Even-split equivalence:** $a\sim b$ if $a=b$ or both even-length and halves equivalent in either order — hash both half-orders, recurse (Equivalent Strings); do not expand into $O(n)$ copies.
- **KMP automaton DP:** state = current match length in $\pi$; transitions on alphabet; absorb / forbid / require a pattern (Required Substring, Lucky Common Subsequence, Obsessive String).
- **Run-length KMP:** compress $(c,\mathrm{len})$ blocks; match the interior exactly, treat the first/last block as a prefix/suffix length constraint (Messenger).
- **One-mismatch / one-delete probes:** fix the differing position (or branch once in a trie); compare the two surrounding segments with $O(1)$ hashes (Spelling Check, Watto).
- **Binary trie counts, not only max:** for “XOR $\ge k$”, walk bit-by-bit and add whole subtrees when the bit choice already satisfies the threshold (Beautiful Subarrays) — same structure as Vasiliy, different query.
- **Z for reconstruct / lex build:** Z on $A{+}B$ and $B{+}A$ (ABCBAC) or Z from each index (Erase and Extend / Compress String) replaces nested string compares under $n\le 10^6$.

## Where it appears in OAs / interviews

- **“Autocomplete / dictionary decode”** — Spy Syndrome / Color with Occurrences / A Lot of Games: trie over a word list, sometimes reversed or as a game on missing letters.
- **“Split / validate a serial with modular checks”** — Hacking Cypher / Check Transcription: rolling numeric or block hashes under format constraints (OA-flavoured).
- **“Count strings containing a password / virus”** — Required Substring / Obsessive String / Lucky Common Subsequence: DP on the KMP failure state.
- **“Nearly periodic / one typo”** — Nearly Shortest Repeating / Spelling Check / Watto: period or Hamming-1 membership, common timed-OA twist on plain matching.
