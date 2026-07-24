# Largest Container

You are given a **circular** array `container` of length `n` (indices are taken modulo `n`), and
three arrays of equal length `m`: `firstPos`, `secondPos`, and `slide`. Swap `i` exchanges the
elements at indices `(firstPos[i] - slide[i]) mod n` and `(secondPos[i] + slide[i]) mod n`.

You have exactly `m` swaps. **Each swap may be used at most once.** You may apply **any subset** of
them, in **any order** you like. Return the container arranged to be **lexicographically largest**
over every reachable arrangement.

(Because a swap can't be reused, this is not the same as freely permuting connected indices — e.g.
with `[1,2,3]` and swaps `{0,1}` and `{1,2}` you can reach `3 1 2` but **not** `3 2 1`, since the
latter would need swap `{0,1}` twice. The intended inputs are small.)

## Input
- Line 1: integer `n`.
- Line 2: `n` integers — `container[0..n-1]`.
- Line 3: integer `m`.
- Line 4: `m` integers — `firstPos[i]`.
- Line 5: `m` integers — `secondPos[i]`.
- Line 6: `m` integers — `slide[i]`.
(Lines 4-6 are empty when `m = 0`.)

## Output
`n` integers: the lexicographically largest reachable arrangement, space-separated.

## Constraints
- `1 <= n <= 10`, `0 <= m <= 12`
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
3 1 2
```
Swaps are {0,1} and {1,2}, each usable once. Best is applying {1,2} then {0,1}: 1 2 3 -> 1 3 2 -> 3 1 2.
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
