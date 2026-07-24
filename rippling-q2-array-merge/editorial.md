# Editorial — Make Two Arrays Equal by Merging

Replacing a subarray with its sum keeps the array's **total** unchanged, so if `sum(X) ≠ sum(Y)` the
answer is `-1`.

Otherwise, any reachable array is described by a set of **cut points** = a subset of the prefix sums.
The final common array `Z` must have prefix sums that appear in **both** `X` and `Y` — i.e. `Z`'s cuts
are chosen from the **common prefix sums**. Between two consecutive chosen cuts, `X` needs one
operation iff it spans `≥ 2` original elements (collapse that block), and likewise for `Y`.

So, letting the common prefix sums be `c_0 = 0 < c_1 < … < c_K = total` with `posX[k]`, `posY[k]`
their indices in `X`, `Y`:

```
dp[k] = min over t < k of  dp[t] + [posX[k]-posX[t] ≥ 2] + [posY[k]-posY[t] ≥ 2],   dp[0] = 0
answer = dp[K]
```

**Keeping every common cut is NOT always optimal** — sometimes collapsing across a shared midpoint is
cheaper (see example 2), which is exactly why this is a DP over *which* common cuts to keep, not a
plain two-pointer. `O(K^2)` with `K ≤ min(n,m)+1`. (Values are positive, so prefix sums strictly
increase and the common ones are found with a two-pointer merge.)
