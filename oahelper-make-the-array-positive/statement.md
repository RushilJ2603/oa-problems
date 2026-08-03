# Make the Array Positive

A trading desk stores a risk vector of `n` integers. Compliance requires the vector to be **positive**: every contiguous segment of length at least 2 must have a non-negative sum.

You may rewrite any entry. In one operation you pick an index `i` and a replacement value `x` with `-10^8 ≤ x ≤ 10^8`, and set `arr[i] = x`.

Find the **minimum number of operations** needed to make the array positive.

Formally, after the operations, for every `0 ≤ l < r < n`:

```
arr[l] + arr[l+1] + ... + arr[r] ≥ 0
```

A solution always exists (you may rewrite every entry).

## Input Format

- The first line contains an integer `n`, the size of the array.
- Each of the next `n` lines contains one integer `arr[i]`.

## Output Format

Print a single integer — the minimum number of operations required.

## Constraints

- `1 ≤ n ≤ 10^5`
- `-10^9 ≤ arr[i] ≤ 10^9`
- A replacement value `x` must satisfy `-10^8 ≤ x ≤ 10^8`

## Examples

### Example 1

**Input**

```
5
2
5
-8
-1
2
```

**Output**

```
1
```

**Explanation:** Rewrite index `2` to `10`. The array becomes `[2, 5, 10, -1, 2]`, and every subarray of length ≥ 2 has a non-negative sum.

### Example 2

**Input**

```
5
-1
-1
-1
-1
-1
```

**Output**

```
2
```

**Explanation:** One rewrite is not enough: two adjacent untouched `-1` values still sum to `-2`. Rewriting indices `1` and `3` to a large allowed value works.
