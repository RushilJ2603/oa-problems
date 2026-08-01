# 19 — Stacks, Queues, Monotonic Deque & Priority Queue (Depth Pass)

**Placement value:** High (contest-form stack/deque/heap greeds beyond LC NGE / sliding-window max / top-K; trains CF-style observation on the same DS).
**Prereq topics:** Arrays, Sorting, Greedy basics, Prefix Sums; base ladder for this topic already done.
**Pattern in one paragraph:** Same LIFO / FIFO / extremum-in-window ideas as the base sheet, but statements hide them behind lex-minimization with a deque, capped “who can take whom” heaps after a sort, cancel-pairs on a stack, nearest-smaller ranges that feed histogram / contribution formulas, or regret-style PQ undos. Recognize it when order of processing is forced (left→right, by power, by deadline), when each index needs its nearest stricter neighbor, when a sliding window only needs min/max (not k-th), or when a global +Δ on all heap keys can be deferred as a lazy offset.

**Technique notes (non-obvious):**
- Nearest-smaller/greater on both sides → for each `i` the maximal segment where `a[i]` is the min (or max); then push answers by segment length (Mike and Feet) or check prefix conditions inside that range (Max GEQ Sum).
- Histogram / Skyscrapers: after L/R bounds, `ans[i]` is often a prefix contribution from the left stack plus a suffix from the right — compute both passes, then pick the best peak.
- Lazy heap offset: store `value - global_add` in the PQ; type-2 “add X to all” only bumps `global_add` (ABC212 D).
- Size-`k` heap for k-th largest in a growing prefix: min-heap of size `k`; top is the answer after each insert (ABC234 D).
- Capped loot heap: process entities sorted by strength; maintain a size-`k` multiset of taken values, evicting the minimum when over capacity (Knights).
- Stack cancel / RBS: push openings; on conflict pop or reject — also builds the “next unmatched” links used in coloring / recovery problems.
- Mono deque DP: window min of `dp[j]` (or of `a[j]`) over a sliding feasible interval turns `O(nk)` into `O(n)` (Strip / Cashback-family).
- Merge-equals / frequency PQ: always combine the current minimum key (or highest freq); use `map`/`multiset` so the next candidate is `O(log n)`.

## Ladder (easy -> hard, 24 problems)
- [ ] [Stack of Presents](https://codeforces.com/problemset/problem/1279/C) — `Codeforces` `1400` — stack simulation — Pop until the needed present is on top; count wasted removals. **(core)**
- [ ] [T-shirt Buying](https://codeforces.com/problemset/problem/799/B) — `Codeforces` `1400` — 3 multisets by color — Always take the cheapest available for the asked front color. **(core)**
- [ ] [Knights of a Polygonal Table](https://codeforces.com/problemset/problem/994/B) — `Codeforces` `1400` — sort + capped heap — Process by power; keep top-`k` loot in a size-limited multiset. **(core)**
- [ ] [Epic Transformation](https://codeforces.com/problemset/problem/1506/D) — `Codeforces` `1400` — frequency max-heap — Pair distinct values until ≤1 type left; answer = leftover count. **(core)**
- [ ] [Minimize the Error](https://codeforces.com/problemset/problem/960/B) — `Codeforces` `1500` — max-heap residuals — Always decrement the largest `|a_i−b_i|` over `k1+k2` ops.
- [ ] [Binary String To Subsequences](https://codeforces.com/problemset/problem/1399/D) — `Codeforces` `1500` — two queues of IDs — Assign `0`/`1` by reusing an opposite-parity open subsequence. **(core)**
- [ ] [Lunar New Year and Food Ordering](https://codeforces.com/problemset/problem/1106/B) — `Codeforces` `1500` — PQ of dishes — Serve preferred dish first, then globally cheapest remaining stock. **(core)**
- [ ] [Prefix K-th Max](https://atcoder.jp/contests/abc234/tasks/abc234_d) — `AtCoder` `ABC234 D (~1400)` — size-`k` min-heap — Streaming k-th largest on growing prefixes. **(core)**
- [ ] [Querying Multiset](https://atcoder.jp/contests/abc212/tasks/abc212_d) — `AtCoder` `ABC212 D (~1600)` — PQ + lazy offset — Global add without touching every key. **(core)**
- [ ] [Sliding Window Minimum](https://cses.fi/problemset/task/3221) — `CSES` `Sliding Window` — monotonic deque — Canonical `O(n)` window minima (generator input, xor the mins). **(core)**
- [ ] [Movie Festival II](https://cses.fi/problemset/task/1632) — `CSES` `Sorting and Searching` — multiset of end times — `k` resources: assign each film to the latest free end `≤ start`. **(core)**
- [ ] [Alternating Current](https://codeforces.com/problemset/problem/343/B) — `Codeforces` `1600` — stack cancel — Adjacent equal brackets cancel; empty stack ⇒ yes.
- [ ] [Minimize The Integer](https://codeforces.com/problemset/problem/1251/C) — `Codeforces` `1600` — two queues by parity — Merge odd/even digits preserving relative order for lex-min.
- [ ] [Merge Equals](https://codeforces.com/problemset/problem/962/D) — `Codeforces` `1600` — map/heap merges — Repeatedly replace two equal values by `2x` at the later index. **(core)**
- [ ] [Preparing for Merge Sort](https://codeforces.com/problemset/problem/847/B) — `Codeforces` `1600` — decreasing piles — Greedily append to the leftmost pile whose last `< x` (patience-style).
- [ ] [Tree Infection](https://codeforces.com/problemset/problem/1665/C) — `Codeforces` `1600` — PQ on subtree sizes — Infect largest pending components first after the root inject. **(core)**
- [ ] [Minimum Array](https://codeforces.com/problemset/problem/1157/E) — `Codeforces` `1700` — multiset `lower_bound` — For each `a_i` pick smallest `b` with `(a_i+b)%n` minimal. **(core)**
- [ ] [Minimal String](https://codeforces.com/problemset/problem/797/C) — `Codeforces` `1700` — stack + suffix mins — Push from `s`; pop to `u` while top ≤ remaining minimum. **(core)**
- [ ] [Maximum Xor Secondary](https://codeforces.com/problemset/problem/280/B) — `Codeforces` `1800` — monotonic stack — Max `a_i XOR a_j` over segments whose max is at an endpoint. **(stretch)**
- [ ] [Max GEQ Sum](https://codeforces.com/problemset/problem/1691/D) — `Codeforces` `1800` — mono stack + prefix — For each max-range, verify no subarray sum exceeds the max. **(stretch)**
- [ ] [Mike and Feet](https://codeforces.com/problemset/problem/547/B) — `Codeforces` `1900` — nearest-smaller ranges — Max of minima for every length via L/R bounds + suffix max. **(stretch)**
- [ ] [Skyscrapers (Hard Version)](https://codeforces.com/problemset/problem/1313/C2) — `Codeforces` `1900` — mono stack both sides — Unimodal array maximizing ∑ under neighbor constraints. **(stretch)**
- [ ] [Strip](https://codeforces.com/problemset/problem/487/B) — `Codeforces` `2000` — mono deque + DP — Min pieces with length ≥`l` and range ≤`s`. **(stretch)**
- [ ] [DZY Loves Modification](https://codeforces.com/problemset/problem/446/B) — `Codeforces` `2000` — two heaps row/col — Prefetch best `p` row picks and `q` col picks with cross penalty `k`. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- Write nearest-smaller/greater L/R arrays in one left-to-right and one right-to-left mono-stack pass.
- Convert L/R bounds into length-indexed answers (`ans[len]=max(ans[len],a[i])`) then suffix-max sweep.
- Maintain a monotonic deque of indices for window min/max; expire from the front, pop dominated from the back.
- Size-`k` heap / capped multiset templates for streaming k-th and “top-k loot while scanning.”
- Lazy global offset on a PQ (`store x−add`, bump `add`) for “add to all keys” queries.
- Stack greedy for lex-smallest output: pop while safe w.r.t. a precomputed suffix minimum (Minimal String).
- Multiset `lower_bound` / `upper_bound` for modular or interval assignment (Minimum Array, Movie Festival II).
- When DP transition is `min` over a sliding feasible window of prior states, reach for a mono deque — not a segtree.

## Where it appears in OAs / interviews
- **“Serve customers from preferred then cheapest stock”** — Lunar New Year / multi-queue inventory simulation.
- **“k workers watching the most non-overlapping intervals”** — Movie Festival II / Meeting Rooms II with `k` rooms.
- **“Running k-th largest in a stream / prefix”** — ABC234 D; same as top-K heap interview staple.
- **“For every window length, max of the window minimum”** — Mike and Feet; histogram / contribution interviews in CF clothing.
