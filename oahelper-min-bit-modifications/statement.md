# Minimum Bit Modifications to Equalize User Roles

You manage user roles as an integer array `userRoles` of length `n`. In one operation you may flip
a single bit of any one element (0->1 or 1->0). Make **all** elements equal using the minimum
total number of bit flips, and print that minimum.

## Input
- Line 1: integer `n`.
- Line 2: `n` space-separated non-negative integers.

## Output
A single integer: the minimum total bit flips to make all elements equal.

## Constraints
- `1 <= n <= 10^5`
- `0 <= userRoles[i] <= 10^18`

## Example
```
Input:
4
2 1 3 4
Output:
5
```
Each bit position is independent; flip whichever of {0,1} is the minority at that bit.
