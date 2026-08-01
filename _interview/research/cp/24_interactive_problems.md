# 24 — Interactive problems (query–response, binary-search interactive)

**Placement value:** Medium — almost never a literal OA template (no flush/interactor), but CF/AtCoder Div2 C–D interactives are common; the skill transfers to “limited oracle / ask ≤ Q questions” interview twists and to any BS-on-answer thinking under a query budget.
**Prereq topics:** Binary search (incl. on answer / unimodal peak), flush I/O basics, bit ops, basic trees/graphs (for mid–stretch reconstruct), optional modular arithmetic for XOR/mod oracles
**Pattern in one paragraph:** The judge holds a hidden object; you print queries, **flush**, read answers, and must finish within a hard query limit (often ≈ log N, N, or N log N). Recognize it by “Interactive” / `?`–`!` protocol / “at most Q questions.” Map the limit to an algorithm: log → binary (or ternary) search; ~N → one pass / degree queries; N log N → sort/merge with comparisons; 2·⌈log⌉ → independent searches on two axes; bit-width → recover each bit with parallel queries. Always flush (`endl` / `fflush` / `sys.stdout.flush`); never read before the query is flushed; print the final `!` answer and exit.

## Ladder (easy -> hard, 28 problems)
- [ ] [Hidden Integer](https://cses.fi/problemset/task/3112) — `CSES` `Interactive` — classic BS + flush — **(core)** CSES Interactive opener; first `?`/`!` + binary search template
- [ ] [Interview](https://codeforces.com/problemset/problem/1807/E) — `Codeforces` `1300` — prefix-sum oracle + BS — **(core)** modern Div2; find differing index via range-sum queries
- [ ] [Bear and Prime 100](https://codeforces.com/problemset/problem/679/A) — `Codeforces` `1400` — factorization queries — **(core)** *the* early CF interactive classic; ≤20 yes/no divisibility asks
- [ ] [Guess the Array](https://codeforces.com/problemset/problem/727/C) — `Codeforces` `1400` — reconstruct from pairwise sums — **(core)** solve 3 eqs for a1..a3 then fill; query-design drill
- [ ] [Last Rook](https://atcoder.jp/contests/abc269/tasks/abc269_e) — `AtCoder` `ABC269 E` — 2D independent BS — **(core)** find missing row & column separately with rectangle-count queries
- [ ] [Colored Chairs](https://cses.fi/problemset/task/3273) — `CSES` `Interactive` — circular BS / parity — **(core)** same-color adjacent on odd cycle; BS the wrap interval
- [ ] [Permuted Binary Strings](https://cses.fi/problemset/task/3228) — `CSES` `Interactive` — bit-by-bit recover — **(core)** ≤10 queries encode position via bitmasks; information-theoretic template
- [ ] [Ruler (easy version)](https://codeforces.com/problemset/problem/1999/G1) — `Codeforces` `1500` — BS for break point — **(core)** find largest x with f(x)=x-style ruler; interactive BS
- [ ] [Guess The Tree](https://codeforces.com/problemset/problem/2001/C) — `Codeforces` `1500` — reconstruct tree — LCA/path-query style; recover parents with few asks
- [ ] [K-th Highest Score](https://cses.fi/problemset/task/3305) — `CSES` `Interactive` — k-th of two sorted lists — **(core)** two-array selection via BS on split; classic interview-adjacent
- [ ] [Guessing the Greatest (easy version)](https://codeforces.com/problemset/problem/1486/C1) — `Codeforces` `1600` — interactive peak / argmax — **(core)** query range second-max → decide which half holds the max
- [ ] [Guess the K-th Zero (Easy version)](https://codeforces.com/problemset/problem/1520/F1) — `Codeforces` `1600` — prefix-count + BS — **(core)** ask sum on [1,r] (zeros), binary-search k-th zero
- [ ] [Fixed Point Guessing](https://codeforces.com/problemset/problem/1698/D) — `Codeforces` `1600` — BS on almost-sorted — **(core)** one swap; count “fixed” side to shrink
- [ ] [Chocolate Bunny](https://codeforces.com/problemset/problem/1407/C) — `Codeforces` `1600` — reconstruct perm via mod — **(core)** ask i%j / j%i; larger residue is the larger value
- [ ] [Hidden Permutation](https://cses.fi/problemset/task/3139) — `CSES` `Interactive` — comparator sort — recover perm with ≤ n log n less-than queries (merge/insertion)
- [ ] [Searching Local Minimum](https://codeforces.com/problemset/problem/1479/A) — `Codeforces` `1700` — unimodal / local-min BS — **(core)** ternary-style: compare a[mid] vs neighbors, shrink
- [ ] [Hidden Permutations](https://codeforces.com/problemset/problem/1621/C) — `Codeforces` `1700` — follow functional cycles — **(core)** query next pointer until cycles close; ≤ n+1 asks
- [ ] [Find a Mine](https://codeforces.com/problemset/problem/1934/C) — `Codeforces` `1700` — geometry + Manhattan oracles — locate mines with distance queries; constructive interactive
- [ ] [Rocket](https://codeforces.com/problemset/problem/1010/B) — `Codeforces` `1800` — lying BS / learn lie pattern — **(stretch)** first learn which answers lie, then BS with known lies
- [ ] [Bit Guessing Game](https://codeforces.com/problemset/problem/1780/D) — `Codeforces` `1800` — recover bits of hidden x — **(stretch)** subtract powers / ask differences to peel bits
- [ ] [Lost Tree](https://codeforces.com/problemset/problem/1534/D) — `Codeforces` `1800` — distance-from-root reconstruct — **(stretch)** bipartite layers from dist queries; O(n) asks
- [ ] [Guessing the Greatest (hard version)](https://codeforces.com/problemset/problem/1486/C2) — `Codeforces` `1900` — peak + tighter budget — **(stretch)** same as C1 with fewer queries; tighter casework
- [ ] [Kuroni and the Celebration](https://codeforces.com/problemset/problem/1305/D) — `Codeforces` `1900` — tree + LCA queries — **(stretch)** query leaves’ LCA, prune; classic interactive tree
- [ ] [XOR Guessing](https://codeforces.com/problemset/problem/1207/E) — `Codeforces` `1900` — pack bits into two queries — **(stretch)** ask 1..100 then shifted; XOR halves to recover
- [ ] [Mahmoud and Ehab and the binary string](https://codeforces.com/problemset/problem/862/D) — `Codeforces` `2000` — BS for both bit positions — **(stretch)** find a `0` and a `1` index under Hamming-distance oracle
- [ ] [The hat](https://codeforces.com/problemset/problem/1019/B) — `Codeforces` `2000` — circular unimodal BS — **(stretch)** n even; compare a[i] vs a[i+n/2] to shrink circle
- [ ] [Subway Pursuit](https://codeforces.com/problemset/problem/1039/B) — `Codeforces` `2100` — shrinking interval + random — **(stretch)** interactive chase; BS while range expands each turn
- [ ] [Guess the K-th Zero (Hard version)](https://codeforces.com/problemset/problem/1520/F2) — `Codeforces` `2200` — multi-query + Fenwick cache — **(stretch)** many k-th-zero asks; cache prefix counts / BIT over answers

## Must-internalize checklist (5-10 bullets)
- Always flush after every query; sync I/O off only if you still flush; terminate immediately after printing `!`.
- Query-limit → complexity: ≈log ⇒ binary/ternary search; ≈n ⇒ linear reconstruct / degree / cycle-follow; ≈n log n ⇒ sorting with comparisons; ≈bitwidth ⇒ recover each bit (often in parallel).
- Interactive BS template: keep a feasible interval (or set); ask a mid that **halves** remaining candidates given the oracle’s answer type (compare / count / second-max / distance).
- Second-max / “argmax on range” oracles: the max lies in the half that contains the global second-max’s side (Guessing the Greatest family).
- Reconstruct permutations: comparator sort; or `a%b` tricks; or follow `p[i]` as a functional graph of cycles.
- Trees: distance-from-one-node → layers/bipartition; LCA(u,v) on leaves → prune toward root (Kuroni / Lost Tree patterns).
- Bit / XOR oracles: ask carefully chosen masks so each answer bit encodes one unknown; or two queries packing low/high halves.
- Lying / adaptive interactors: spend early queries to learn the lie schedule (Rocket) or keep the search range large enough vs expansion (Subway Pursuit).
- Local test: write a local interactor (or CF’s) that checks flush + query count; never assume buffered output reaches the judge without flush.

## Where it appears in OAs / interviews
- “Find the broken version / first bad commit with ≤ log n asks” → classic interactive binary search (Hidden Integer / Interview style), same as git-bisect interviews.
- “Array is hidden; you may query range sums / second maximum — find the maximum / k-th zero” → Guessing the Greatest / Guess the K-th Zero (oracle-complexity interviews).
- “Recover a secret permutation / password with pairwise compares or mod queries under a budget” → Chocolate Bunny / Hidden Permutation / Bear-and-Prime style limited-question reconstruct.
- “Two sorted lists in different APIs — find the global k-th with few fetches” → K-th Highest Score (merge-kth / two-pointers with queries).
