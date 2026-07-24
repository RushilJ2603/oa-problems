# Editorial — Game of Book Cricket

Ordered compositions of `N` using parts `{2, 4, 6}`. Let `dp[i]` be the number of ways to reach
exactly `i`:

```
dp[0] = 1
dp[i] = dp[i-2] + dp[i-4] + dp[i-6]   (terms included only when the index is ≥ 0)
```

Answer `dp[N]`. `O(N)` time. The count grows quickly, so use a 64-bit integer.
