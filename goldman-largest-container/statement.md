# Largest Container

You are given a **circular** array `container` of length `n` (indices are taken modulo `n`), and
three arrays of equal length `m`: `firstPos`, `secondPos`, and `slide`. Swap operation `i`
connects the two indices `(firstPos[i] - slide[i]) mod n` and `(secondPos[i] + slide[i]) mod n`:
the elements at those two indices may be exchanged. **You may apply any swap any number of times,
in any order.** Return the container rearranged to be **lexicographically largest**.

(Because swaps may be reused, any set of indices linked directly or indirectly by swaps can be
permuted freely among themselves.)

## Input
- Line 1: integer `n`.
- Line 2: `n` integers — `container[0..n-1]`.
- Line 3: integer `m`.
- Line 4: `m` integers — `firstPos[i]`.
- Line 5: `m` integers — `secondPos[i]`.
- Line 6: `m` integers — `slide[i]`.
(Lines 4-6 are empty when `m = 0`.)

## Output
`n` integers: the lexicographically largest arrangement, space-separated.

## Constraints
- `1 <= n <= 10^5`, `0 <= m <= 10^5`
- `1 <= container[i] <= 10^9`
- `0 <= firstPos[i], secondPos[i] <= n-1`, `0 <= slide[i] <= 10^9`

## Examples
```
Input:
3
1 2 3
2
0 1
1 2
0 0
Output:
3 2 1
```
Swaps link {0,1} and {1,2}, so all three indices form one group; sorted descending -> 3 2 1.
```
Input:
4
2 1 4 3
1
0
2
0
Output:
4 1 2 3
```
