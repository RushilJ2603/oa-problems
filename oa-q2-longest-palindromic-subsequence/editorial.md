# Editorial — Longest Palindromic Subsequence

Interval DP. Let `dp[i][j]` be the length of the longest palindromic subsequence of `s[i..j]`.

- `dp[i][i] = 1`.
- If `s[i] == s[j]`: `dp[i][j] = dp[i+1][j-1] + 2`.
- Otherwise: `dp[i][j] = max(dp[i+1][j], dp[i][j-1])`.

Fill by increasing interval length (or `i` descending, `j` ascending). Answer `dp[0][n-1]`.
`O(n^2)` time and space — fine for `n ≤ 1000`. (Equivalently, it's the LCS of `s` and `reverse(s)`.)
