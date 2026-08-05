# Palindromic Paths to the Root

## Two reductions

**1. A palindrome is a parity condition.** A multiset of letters can be rearranged into a palindrome
iff at most one letter occurs an odd number of times. Only the 26 parities matter, so a path is
fully described by a 26-bit mask, and the test is `popcount(mask) <= 1` — 27 acceptable masks in
total for a given path (the mask itself being zero, or differing from zero in one bit).

**2. Path masks are XOR differences of root masks.** Let `pre(x)` be the XOR of the letter-bits from
the root down to `x`, and let `pre(parent of root) = 0`. Then

```
mask(path u..v) = pre(u) XOR pre(parent(v))
```

So for a fixed `u`, the query counts how many of the masks *hanging above* `u` — the set
`{0} ∪ {pre(x) : x a proper ancestor of u}` — are equal to `pre(u)` or differ from it in exactly one
of 26 bits. That is **27 lookups**, whatever the depth.

## Algorithm

One DFS from the root answers every node at once:

- Keep a counter `cnt[mask]` of the prefix masks currently on the root-to-current path, seeded with
  `cnt[0] = 1` (that is the empty prefix above the root, and it is what lets `v = 0` score).
- On **entering** `u`: compute `pre(u) = pre(parent) XOR bit(letter[u])`, then
  `ans[u] = cnt[pre(u)] + Σ(c = 0..25) cnt[pre(u) XOR (1 << c)]`, then `cnt[pre(u)] += 1`.
- On **leaving** `u`: `cnt[pre(u)] -= 1`.

Queries are then array reads. **Complexity:** O(26·n + q).

Two implementation notes that matter at `n = 200000`:

- `cnt` cannot be a flat array — `2^26` counters is 268 MB. Use a hash map; at most `n+1` distinct
  masks are ever inserted, and keys only need decrementing (never deleting), so a small
  open-addressing table with no tombstones is enough.
- The DFS must be **iterative**. A path-shaped tree of 200,000 nodes overflows the call stack.

## Traps

- **The edges are unordered pairs.** Building a directed graph from `treeFrom[i] → treeTo[i]` gives
  a graph where node `0` may not look like the root at all, and any traversal that respects that
  direction gets the wrong tree — which is exactly the "were the arrays given reversed?" confusion
  this problem is known for. Build both directions and root at `0`; then the question of which
  endpoint was written first never arises. Sample 2 is sample 1 with every edge flipped, and the
  answers are identical.
- **`v = u` counts.** A single node is a one-letter palindrome, so every answer is at least 1.
- **`v = 0` counts.** The walk includes the root.
- **The per-query walk is quadratic.** With a 200,000-deep path and 200,000 queries at the bottom it
  is 4·10¹⁰ character updates — tens of seconds even with an O(26) check, which is precisely how the
  original OA separated the intended solution from the natural one. Answer every node in one pass
  instead.
