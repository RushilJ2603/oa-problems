# Application Deployment

You are rolling out a new application across a row of `n` servers. Server `i` has vulnerability score `vulnerability[i]`. You must pick **exactly** `k` servers such that:

1. No two chosen servers are adjacent in the row.
2. Among all such selections, the **maximum** vulnerability in the chosen set is as small as possible.

Return that minimized maximum vulnerability.

## Input Format

- The first line contains an integer `n`.
- Each of the next `n` lines contains an integer `vulnerability[i]`.
- The last line contains an integer `k`.

## Output Format

Print a single integer: the minimum achievable maximum vulnerability.

## Constraints

- \(1 \le n \le 10^5\)
- \(1 \le vulnerability[i] \le 10^9\)
- \(1 \le k \le (n + 1) / 2\)

## Examples

### Example 1

**Input**
```
5
2
4
6
8
10
2
```

**Output**
```
6
```

**Explanation**

Valid length-2 non-adjacent selections include `[2,6]` (max 6), `[2,8]` (max 8), `[4,8]` (max 8), etc. The best maximum is 6.

### Example 2

**Input**
```
5
1
2
1
2
1
3
```

**Output**
```
1
```

**Explanation**

The only length-3 non-adjacent selection is the three `1`s, so the answer is 1.
