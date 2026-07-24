# Maximum Sum

You are given an array `arr` of size `n` and an integer `k`. In one operation you flip the sign of
any one element. Perform **exactly** `k` sign-flip operations (an element may be flipped more than
once) to maximise the sum of the array. Print the maximum possible sum.

## Input
- Line 1: integer `n`.
- Line 2: integer `k`.
- Then `n` integers (the array).

## Output
A single integer: the maximum achievable sum after exactly `k` flips.

## Constraints
- `1 <= n <= 10^5`
- `0 <= k <= 10^9`
- `-10^9 <= arr[i] <= 10^9`

## Example
```
Input:
5
3
-5 -2 -3 6 7
Output:
23
```
Flip the three negatives -> 5 2 3 6 7, sum 23.
