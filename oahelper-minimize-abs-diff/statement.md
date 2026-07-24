# Minimize Sum of Absolute Differences

Given an array of `n` integers, remove exactly one **contiguous subarray of length `k`** so that
the sum of absolute differences between adjacent elements of the **resulting** array is minimised.
Print that minimum sum.

## Input
- Line 1: two integers `n` and `k`.
- Line 2: `n` space-separated integers.

## Output
A single integer: the minimum possible sum of adjacent absolute differences after the removal.

## Constraints
- `1 <= k < n <= 10^5`
- `-10^9 <= a[i] <= 10^9`

## Example
```
Input:
5 2
1 3 7 2 5
Output:
4
```
Removing `[7, 2]` leaves `[1, 3, 5]` -> |1-3| + |3-5| = 4.
