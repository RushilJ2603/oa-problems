# Editorial — Online Auction Sniper Detector

Bids arrive in increasing time, so the set of bids inside the window `[t_i - W, t_i]` only ever
**gains** the new bid on the right and **loses** old bids on the left — a textbook **sliding
window** (two pointers).

Maintain, over the current window `[left, i]`:
- `cnt[user]` — how many of that user's bids are in the window. Ids reach `10^9`, so this must be
  a **hash map**, not an array.
- `snipers` — an ordered `set` of users whose `cnt >= K`. The smallest sniper is `*snipers.begin()`.

Per bid `i`:
1. Add bid `i`: `++cnt[u]`; if it just hit `K`, insert `u` into `snipers`.
2. Evict from the left while `t_i - t_left > W`: decrement that user's count; if it just dropped
   to `K - 1`, erase it from `snipers`.
3. `flag = (cnt[u] >= K)`; `smallest = snipers.empty() ? -1 : *snipers.begin()`.

Each bid enters and leaves the window once, so the whole thing is `O(N log N)` — comfortable for
`N = 2·10^5`.

**The three traps** (all in the wrapping, not the algorithm):
1. Ids and timestamps up to `10^9` force `long long` and a hash map — a count array MLEs/overflows.
2. The output is **two** values per line; the C version of the harness delivers them via
   out-parameter arrays rather than a return value.
3. The window boundary is **inclusive**: a bid at `t'` counts iff `t_i - t' ≤ W`. Getting `<` vs
   `≤` wrong is the whole correctness of the problem — pin it down from the worked example.
