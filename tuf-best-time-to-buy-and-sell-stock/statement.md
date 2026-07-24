# Best Time to Buy and Sell Stock

You are given an array `arr` of `n` integers where `arr[i]` is the price of a stock on day `i`.
Buy on one day and sell on a **later** day (at most one transaction; you cannot buy and sell on
the same day). Print the **maximum profit**; if no profit is possible, print `0`.

## Input
- Line 1: integer `n`.
- Line 2: `n` integers — `arr[0..n-1]`.

## Output
A single integer: the maximum achievable profit (0 if none).

## Constraints
- `1 <= n <= 10^5`
- `0 <= arr[i] <= 10^6`

## Examples
```
Input:
6
10 7 5 8 11 9
Output:
6
```
```
Input:
5
5 4 3 2 1
Output:
0
```
