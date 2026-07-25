# Valid Memory Block Sizes

A memory allocator tracks `n` blocks whose current sizes are given by the array `memoryBlocks`. Each size satisfies `0 <= memoryBlocks[i] < n`.

You may perform **at most one** operation: pick an index `x` where `memoryBlocks[x] < n - 1` and increase that entry by exactly `1`. You may also choose to do nothing.

After the (optional) operation, the Valid Size is the MEX of the array — the smallest non-negative integer that does not appear. Return **all** distinct Valid Sizes you can achieve, sorted in ascending order, printed space-separated on one line.

## Input Format

- The first line contains an integer `n`.
- The second line contains `n` integers `memoryBlocks[0], ..., memoryBlocks[n-1]`.

## Output Format

Print the achievable MEX values in ascending order, separated by spaces.

## Constraints

- \(1 \le n \le 10^5\)
- \(0 \le memoryBlocks[i] < n\)

## Examples

### Example 1

**Input:**
```
3
0 2 2
```

**Output:**
```
0 1
```

**Explanation:** Doing nothing gives MEX `1`. Incrementing index `0` yields `[1, 2, 2]` with MEX `0`. Achievable sizes: `0 1`.

### Example 2

**Input:**
```
3
2 2 2
```

**Output:**
```
0
```

**Explanation:** The only achievable MEX is `0`; no increment can create a higher MEX.

### Example 3

**Input:**
```
4
0 1 2 3
```

**Output:**
```
0 1 2 4
```

**Explanation:** Doing nothing gives MEX `4`. Incrementing a unique value below the original MEX can make that value the new MEX (`0`, `1`, or `2`).
