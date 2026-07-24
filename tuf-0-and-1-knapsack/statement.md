# 0/1 Knapsack

Given `val[i]` and `wt[i]` for `N` items and a knapsack capacity `W`, choose a subset of items with total weight `<= W` maximising total value. Print that maximum value.

## Input
- Line 1: `N` `W`.
- Line 2: `N` integers `val[i]`.
- Line 3: `N` integers `wt[i]`.

## Output
A single integer: the maximum achievable value.

## Constraints
- `1 <= N <= 500`
- `1 <= W <= 1000`
- `1 <= wt[i] <= 500`
- `1 <= val[i] <= 500`

## Examples
```
Input:
3 50
60 100 120
10 20 30
Output:
220
```
