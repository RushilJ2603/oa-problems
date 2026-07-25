# Alternating Sign Subsequence with Bonus

A trading desk scores market signals by picking a subsequence of price moves whose signs strictly alternate — positive then negative then positive, or the opposite pattern.

You are given an array `a` of `N` integers (none of which is zero in the intended use, though zeros may be ignored) and a non-negative bonus `B`. For a chosen subsequence of length `L`, the score is the sum of its elements plus `B × (L − 1)` when `L ≥ 2` (and just the single element when `L = 1`). The empty subsequence scores `0`.

Find the maximum achievable score.

## Input Format

- The first line contains an integer `N`.
- The second line contains an integer `B`.
- Each of the next `N` lines contains one integer `a[i]`.

## Output Format

Print a single integer — the maximum score.

## Constraints

- `1 ≤ N ≤ 10^5`
- `0 ≤ B ≤ 10^9`
- `-10^9 ≤ a[i] ≤ 10^9`
- `a[i] ≠ 0` in all official tests

## Examples

### Example 1

Input:
```
3
10
10
-10
10
```

Output:
```
30
```

Explanation: Taking all three elements gives sum `10` and two alternations: `10 + (−10) + 10 + 2×10 = 30`.

### Example 2

Input:
```
5
100
10
20
30
40
50
```

Output:
```
50
```

Explanation: All values are positive, so any alternating subsequence has length at most 1. The best choice is the largest element `50`.

### Example 3

Input:
```
4
100
10
-20
5
-1
```

Output:
```
294
```

Explanation: Taking the full alternating sequence `10, −20, 5, −1` yields sum `−6` plus three bonuses of `100`, for a total of `294`.
