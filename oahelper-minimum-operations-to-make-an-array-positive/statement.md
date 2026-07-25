# Minimum Operations to Make an Array Positive

A trading desk stores `n` signed risk scores in an array `arr`. Compliance requires the book to be **positive**: every contiguous segment of length at least `2` must have a non-negative sum.

Formally, after your edits, for every pair `(l, r)` with `0 <= l < r < n`:

```
arr[l] + arr[l+1] + ... + arr[r] >= 0
```

In one operation you may pick any index `i` and replace `arr[i]` with any integer `x` in `[-10^18, 10^18]`.

Find the **minimum** number of operations needed to make the array positive.

## Input Format

- Line 1: an integer `n` — the length of the array.
- Line 2: `n` space-separated integers `arr[0] .. arr[n-1]`.

## Output Format

Print a single integer — the minimum number of operations.

## Constraints

- `1 <= n <= 10^5`
- `-10^9 <= arr[i] <= 10^9`

## Examples

### Example 1

**Input**

```
5
-1 -1 -1 -1 -1
```

**Output**

```
2
```

**Explanation**

One valid repair is to overwrite indices `1` and `3` (for example with large positives), producing `[-1, 10, -1, 15, -1]`. Every length-`>=2` subarray then has a non-negative sum. Two operations are necessary and sufficient.

### Example 2

**Input**

```
6
6 -5 5 10 -1 12
```

**Output**

```
0
```

**Explanation**

Every subarray of length at least `2` already has a non-negative sum, so no edits are required.

### Example 3

**Input**

```
3
1 -3 1
```

**Output**

```
1
```

**Explanation**

The length-2 windows `1 + (-3)` and `(-3) + 1` are both negative, and the full array sums to `-1`. Overwriting the middle element once repairs every bad window.
