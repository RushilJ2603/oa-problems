# Shrink the Array

You are given an array `A` of size `N`. For every group of equal values, replace the element at
the group's **middle position** with the **sum** of all elements in that group, and remove all the
other elements of the group. The kept element stays at its original position. When a group has an
even count (two middle positions), use the second (later) of the two middle positions. Print the final array in
original order.

## Input
- Line 1: integer `N`.
- Line 2: `N` space-separated integers.

## Output
The final array after shrinking, space-separated, in original order.

## Constraints
- `1 <= N <= 10^5`
- `1 <= A[i] <= 10^9`

## Example
```
Input:
10
1 2 2 1 1 2 1 3 3 3
Output:
6 4 9
```
Value 1 (indices 0,3,4,6) keeps index 4 -> sum 4; value 2 (2,3,6) keeps index 3 -> 6; value 3
(7,8,9) keeps index 8 -> 9. In order: 6 4 9.
