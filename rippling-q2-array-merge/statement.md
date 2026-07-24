# Make Two Arrays Equal by Merging

You are given two arrays `X` and `Y` of **positive** integers. In one operation you may pick any
contiguous subarray of **either** array and replace that whole subarray with the **sum** of its
values (so a block of length `L ≥ 2` collapses to a single element in one operation; picking a
length-1 subarray does nothing).

Find the **minimum number of operations** to make `X` and `Y` **identical** (same length, same
values in the same order). If it is impossible, output `-1`.

## Input
```
n
X[0] X[1] … X[n-1]
m
Y[0] Y[1] … Y[m-1]
```

## Output
A single integer — the minimum number of operations, or `-1` if the two arrays can never be made
equal.

## Constraints
- `1 ≤ n, m ≤ 3000`
- `1 ≤ X[i], Y[i] ≤ 10^9`

## Example 1
Input:
```
2
1 1
1
2
```
Output:
```
1
```
Merge `X = [1,1]` into `[2]`; now both arrays are `[2]`.

## Example 2
Input:
```
4
1 3 1 3
4
3 1 3 1
```
Output:
```
2
```
Collapse each whole array to `[8]` in one operation each — 2 total. (Trying to preserve the shared
midpoint `4` would cost more.)

## Example 3
Input:
```
2
1 1
3
1 1 1
```
Output:
```
-1
```
The operation never changes an array's total sum (2 vs 3), so they can never match.
