# Editorial — Beautiful Arrangement

`n ≤ 15`, so a bitmask over "which values are already placed" is the natural state.

Let `dp[mask]` = number of ways to fill the first `popcount(mask)` positions using exactly the set
of values in `mask`. The next position to fill is `pos = popcount(mask) + 1`. From `mask`, try every
unused value `x`; if `x % pos == 0` or `pos % x == 0`, it may go in position `pos`:

```
dp[mask | (1<<(x-1))] += dp[mask]
```

The answer is `dp[(1<<n) - 1]`. Complexity `O(2^n · n)` — about 500k operations at `n = 15`.

Equivalent backtracking (place positions 1→n, try valid unused values, prune) also passes because
the divisibility constraint prunes the search heavily.
