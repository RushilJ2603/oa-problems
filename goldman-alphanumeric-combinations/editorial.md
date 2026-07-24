# Editorial — Alphanumeric Combinations (Decode Ways)

DP over prefixes. `dp[i]` = number of ways to decode the first `i` characters:

```
dp[0] = 1
dp[i] += dp[i-1]         if s[i-1] != '0'                  (take one digit, 1..9)
dp[i] += dp[i-2]         if i >= 2 and 10 <= s[i-2..i-1] <= 26   (take two digits)
```

Answer `dp[n]`. Invalid strings (a `0` that can't pair, a leading `0`) naturally yield `0`. `O(n)`.
The count grows like Fibonacci, so use a 64-bit integer (hidden tests are bounded to fit).
