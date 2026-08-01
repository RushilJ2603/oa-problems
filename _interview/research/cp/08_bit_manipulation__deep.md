# 08 — Bit Manipulation & Bitmask Tricks (Depth Pass)

**Placement value:** High (second ladder after XOR/popcount/`2^n` basics — the CF/AtCoder “bits are independent / rewrite with ⊕ and &” observations that dominate Div2 C–D and still appear as OA twists)
**Prereq topics:** Bit primitives (set/clear/`x&-x`/popcount), prefix XOR, finished the standard Bit Manipulation ladder; light greedy + binary search for range-AND checks
**Pattern in one paragraph:** After Single-Number / Fedor / Rock-and-Lever / Elevator-style templates, contest bit problems hide the algebra: rewrite sum as `(a⊕b)+2(a&b)`, force a nonzero total XOR by flipping one cell, maximize progressive OR by always taking the element that sets the most new high bits, or build a binary trie / linear basis when the ask is “max XOR under updates / among subsets.” Recognize them when constraints are bit-width (`≤30`/`≤60`), when AND/OR/XOR of a range or of all subarrays appears, or when you may only flip/OR/AND with a small menu of values.

**Non-obvious tricks (internalize):**
1. `a + b = (a ⊕ b) + 2(a & b)` — Vlad: given `x = a⊕b = (a+b)/2` ⇒ `a&b = x/2` (fail if `x` odd or `(x/2)&x ≠ 0`); Make Good appends using the same identity.
2. Bit flips on `1..n`: bit `k` toggles every `2^k` steps → closed form for Johnny-style “rating drop” counts.
3. Range AND is monotone under extension: binary-search / sparse-table the farthest `r` with `AND[l..r] ≥ k` (Iva & Pav).
4. Max XOR in `[L,R]`: take the highest bit where `L` and `R` differ, then set all lower bits to `1` (Little Girl) — no need to try every pair.
5. Progressive OR: at most `B≈30` useful picks; always grab the unused `a_i` maximizing `cur | a_i` (Orray).
6. XOR binary trie: walk MSB→LSB preferring the opposite bit; supports insert/delete for online max XOR (Vasiliy).
7. Linear basis (Gaussian on bits): insert MSB-greedy; max subset XOR and `#distinct subset XORs = 2^{rank}` (CSES Maximum Xor Subset).
8. Bit-cost of connecting `0..n−1`: for xor-MST, bit `b` contributes `⌊n/2^{b+1}⌋·2^b + max(n % 2^{b+1} − 2^b, 0)` (959E).

## Ladder (easy -> hard, 25 problems)
- [ ] [Johnny and Another Rating Drop](https://codeforces.com/problemset/problem/1362/C) — `Codeforces` `1400` — bit-flip count on `1..n` — **(core)** closed-form per bit; high-consensus Div2 C after the basic popcount ladder.
- [ ] [Fortune Telling](https://codeforces.com/problemset/problem/1634/B) — `Codeforces` `1400` — XOR parity invariant — **(core)** only the parity of the array XOR vs `y` matters; kills fake “simulate all ops” traps.
- [ ] [AND Sequences](https://codeforces.com/problemset/problem/1513/B) — `Codeforces` `1400` — global AND placement — **(core)** `AND` of all must appear ≥2 times; then `(cnt)·(cnt−1)·(n−2)!` permutations.
- [ ] [Make Good](https://codeforces.com/problemset/problem/1270/C) — `Codeforces` `1400` — sum / XOR constructive — **(core)** append `0` values using `sum` and `xor` so new sum `= 2·xor`; OA-flavored ≤3 appends.
- [ ] [Vlad and a Pair of Numbers](https://codeforces.com/problemset/problem/1790/E) — `Codeforces` `1400` — sum↔XOR↔AND algebra — **(core)** given `x = a⊕b = (a+b)/2`, set `a&b = x/2`; impossible if odd or AND overlaps XOR bits.
- [ ] [Bitwise Balancing](https://codeforces.com/problemset/problem/2020/C) — `Codeforces` `1400` — bit-by-bit construction — find `a` with `(a|b) − (a&c) = d`; each bit of `a` is independent (no borrow across bits).
- [ ] [Iva & Pav](https://codeforces.com/problemset/problem/1878/E) — `Codeforces` `1400` — range AND + binary search — **(core)** for each `L`, farthest `R` with `AND ≥ k`; sparse table / bin lifts on AND.
- [ ] [AGAGA XOOORRR](https://codeforces.com/problemset/problem/1516/B) — `Codeforces` `1500` — prefix-XOR partition — **(core)** split into ≥2 contiguous parts with equal XOR (⇒ total XOR `0` or a three-way repeat of the same prefix value).
- [ ] [Powers of Two](https://codeforces.com/problemset/problem/702/B) — `Codeforces` `1500` — pairs summing to `2^k` — **(core)** map frequencies; try all `≤30` powers (distinct from 1095C’s split-into-`k`-powers).
- [ ] [Orray](https://codeforces.com/problemset/problem/1742/G) — `Codeforces` `1500` — greedy progressive OR — **(core)** ≤30 meaningful moves; then dump the rest — reusable “OR saturation” template.
- [ ] [Divan and bitwise operations](https://codeforces.com/problemset/problem/1614/C) — `Codeforces` `1500` — XOR-sum of all subarrays — **(core)** if any forced-zero bit appears in a covering segment, that bit dies everywhere; else each free bit contributes `bit · 2^{n−1}`.
- [ ] [D - XOR World](https://atcoder.jp/contests/abc121/tasks/abc121_d) — `AtCoder` `ABC121 D (~1500)` — XOR of a range via `f(n)=⊕_{i=0}^n i` — AtCoder classic; `f(n)` cycles every 4, answer `f(R)⊕f(L−1)`.
- [ ] [D - Popcount and XOR](https://atcoder.jp/contests/abc347/tasks/abc347_d) — `AtCoder` `ABC347 D (~1600)` — construct `X,Y` with given popcounts and `X⊕Y=C` — bit-type inventory `(0,0)/(0,1)/(1,0)/(1,1)` must match.
- [ ] [Boboniu and Bit Operations](https://codeforces.com/problemset/problem/1395/C) — `Codeforces` `1600` — minimize OR of pairwise ANDs — **(core)** candidate answers are OR-masks of `b_j` values; check each bit budget against some `b_j`.
- [ ] [Dima and a Bad XOR](https://codeforces.com/problemset/problem/1151/B) — `Codeforces` `1600` — force nonzero matrix XOR — **(core)** pick first row arbitrarily; if total XOR `0`, swap one cell in a row that has a differing entry.
- [ ] [Interesting Sequence](https://codeforces.com/problemset/problem/1775/C) — `Codeforces` `1600` — minimal `m` with range AND — smallest `m ≥ n` s.t. `n & (n+1) & … & m = x`; clear excess `1`-bits by jumping to the next power boundary.
- [ ] [Little Girl and Maximum XOR](https://codeforces.com/problemset/problem/276/D) — `Codeforces` `1700` — max XOR in a numeric range — **(stretch)** MSB where `L,R` differ ⇒ answer `(1<<(msb+1))−1`.
- [ ] [AND, OR and square sum](https://codeforces.com/problemset/problem/1368/D) — `Codeforces` `1700` — redistribute bits across array — **(stretch)** OR/AND ops move `1`-bits freely per position; pile bits onto as few numbers as possible to max `∑ a_i^2`.
- [ ] [Bits](https://codeforces.com/problemset/problem/484/A) — `Codeforces` `1700` — max popcount in `[L,R]` — **(stretch)** greedily set the lowest clear bit of `L` while staying `≤ R`.
- [ ] [Zookeeper and The Infinite Zoo](https://codeforces.com/problemset/problem/1491/D) — `Codeforces` `1800` — subsequence-of-bits reachability — **(stretch)** `u → v` iff `u` is a submask of `v` in order (scan bits left-to-right with a running surplus of `u`-bits).
- [ ] [Vasiliy's Multiset](https://codeforces.com/problemset/problem/706/D) — `Codeforces` `1800` — online XOR trie — **(stretch)** insert/delete values; query max `x ⊕` element — the CF multiset form of CSES Maximum Xor Subarray.
- [ ] [Apollo versus Pan](https://codeforces.com/problemset/problem/1466/E) — `Codeforces` `1800` — contribution per bit over all triples — **(stretch)** count how many `a_i` have bit `b`; closed form for `∑ (x_i & x_j)·(x_j | x_k)` style sums.
- [ ] [Maximum Xor Subset](https://cses.fi/problemset/task/3191) — `CSES` `Bitwise Operations` — XOR linear basis — **(stretch)** insert into basis MSB-first; answer = XOR of all basis vectors taken greedily.
- [ ] [Dr. Evil Underscores](https://codeforces.com/problemset/problem/1285/D) — `Codeforces` `1900` — minimax XOR via bit trie/DnC — **(stretch)** choose `X` minimizing `max (a_i ⊕ X)`; recurse on bit partitions (same family as binary-trie thinking).
- [ ] [Mahmoud and Ehab and the xor-MST](https://codeforces.com/problemset/problem/959/E) — `Codeforces` `1900` — cost of XOR edges on `0..n−1` — **(stretch)** CM-band bit counting; sum per-bit connectivity contributions without building the graph.

## Must-internalize checklist (5-10 bullets)
- Rewrite identities cold: `a+b = (a⊕b)+2(a&b)`, `a|b = (a⊕b)+(a&b)`, `a&b = (a+b−(a⊕b))/2`.
- Process bits independently MSB→LSB whenever the score is AND/OR/XOR/popcount of a construction.
- Prefix XOR + “equal segment XOR” ⇒ total XOR `0` or a value that appears as a prefix at least three times (AGAGA).
- Range AND tools: sparse table (`O(1)`), or binsearch + rolling AND; never recompute naively per query.
- XOR trie (30–31 bits): child `[0/1]`, subtree counts for delete; query prefers `!bit`.
- Linear basis: `bas[b] =` vector with highest bit `b`; insert by reducing against existing basis; max query greedily OR-in.
- Progressive OR / bit saturation: at most one useful improvement per bit position (`≤B` steps).
- When simulating `1..n` bit flips or xor-MST on a path of integers, prefer `O(B log n)` floor-counting formulas over loops to `n`.

## Where it appears in OAs / interviews
- **Sum & XOR reconstruct:** “Find any array / pair with given sum and XOR” — Make Good / Vlad algebra; common phone-screen follow-up to Single Number.
- **Pair counts with bit target:** “How many pairs XOR / sum to a power of two” — 702B / Arpa-style hash maps; Amazon OA staple.
- **Maximize OR / AND under k moves:** Orray / Boboniu / Iva & Pav — “flip ≤k bits” or “OR a subset to maximize score.”
- **Online max XOR:** “Maintain a set; answer max XOR with `x`” — Vasiliy / trie; also the interview form of “maximum XOR of two numbers in an array.”
