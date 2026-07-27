# Minimum Absolute Difference Pairs

You are given an array `A` of `N` integers. Find the pairs of values whose absolute difference is the
**smallest** among all pairs `(x, y)` with `x < y`.

Output every such pair `(x, y)` (with `x < y`) whose difference equals that minimum, in ascending
order of `x`, and then by `y`.

Because equal values do not form a valid pair (they need `x < y`), repeated values are effectively
considered once. If the array has fewer than two **distinct** values, there are no pairs — print
nothing.

## Input

```
N
A_1 A_2 ... A_N
```

- Line 1: `N`.
- Line 2: `N` space-separated integers.

## Output

Each qualifying pair on its own line as `x y`, sorted ascending by `x` then `y`. Print nothing if no
pair exists.

## Constraints

- `2 ≤ N ≤ 200000`
- `-10^9 ≤ A_i ≤ 10^9`

## Example 1

**Input**
```
4
7 2 10 5
```
**Output**
```
5 7
```

The pairwise absolute differences are `5,3,2,8,3,5`; the minimum is `2`, achieved only by `(5, 7)`.

## Example 2

**Input**
```
4
1 2 3 4
```
**Output**
```
1 2
2 3
3 4
```

The minimum difference is `1`, achieved by three consecutive pairs.
