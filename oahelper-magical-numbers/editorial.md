# Magical Numbers

## The two halves of the value set behave completely differently

Magical numbers are powers of two plus factorials, and those two families are not symmetric:

- **Powers of two are dense and complete.** Every positive integer is a sum of distinct powers of
  two — that is just its binary representation — and that representation is the *unique* one, so if
  you are only allowed powers of two the answer is forced: `popcount(n)`.
- **Factorials are sparse.** Below `10^9` there are only thirteen of them, and `0! = 1! = 1` and
  `2! = 2` are already powers of two. So the factorials that add anything at all are

  `6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600`

  — **ten values.**

Ten is a small enough number to brute force. Enumerate every subset of those ten (`2^10 = 1024`),
subtract its sum from `n`, and fill the remainder with distinct powers of two, which costs exactly
`popcount(remainder)`:

```
answer = min over subsets S of the ten factorials, with sum(S) <= n, of
             |S| + popcount(n - sum(S))
```

`1024 × 100` test cases is nothing. The whole solution is a loop and a `__builtin_popcountll`.

## Why the ten exclude 1 and 2 — the distinctness trap

Distinctness is by **value**, not by justification. `1` is magical as `2^0` *and* as `1!`, but it is
one number and can appear once. If your factorial list includes `1` and `2` and you then add
`popcount` of the remainder, you can spend `1` twice — once as "the factorial 1!" and once as bit 0
of the remainder — and report an answer one too small.

Dropping every factorial that is already a power of two removes the overlap by construction, which
is why the reference builds its list with `if (v & (v - 1))`. `tests/edge/06.in` probes one either
side of every magical value; `brute.py` deliberately works from the plain *set* of magical values so
that a double-spend would show up as a disagreement rather than being reproduced.

## Why using a factorial ever helps

Because `popcount` is what you are trying to beat. `127 = 1111111` in binary needs **seven** powers
of two. But `127 = 120 + 6 + 1`, and `120 = 5!` and `6 = 3!`, so **three** magical numbers suffice.
The all-ones values are exactly the adversarial family here, which is what `tests/edge/05.in` is.

## The `-1` never happens

The output spec asks for `-1` when no representation exists, and it is worth noticing that this can
never fire: every `n >= 1` has a binary representation, so a representation into distinct magical
numbers always exists, and the answer is at most `popcount(n) <= 30`. Across the whole test suite the
largest answer observed is 15.

Keep the branch anyway — it costs nothing and the grader may feed it — but do not spend interview
time reasoning about when it triggers. Recognising that a stated case is vacuous is worth saying out
loud.

> **A note on this problem's source.** The original statement's worked example claims `7 → -1`. That
> is wrong: `7 = 1 + 6` and both are magical and distinct, so the answer is `2` — which is exactly
> what the platform's own judge returns. The statement here has been corrected against the real
> tests. Do not trust a sample line over the judge.

## Complexity

| Step | Cost |
|---|---|
| Enumerate factorial subsets | `2^10 = 1024` per query |
| `popcount` of the remainder | `O(1)` |
| **Total** | **`O(t · 2^10)`** |
