# The Magic Graph

You have a graph of **N** nodes numbered from **1** to **N**. You are also given **M** magical ranges. Range **i** is described by integers **L[i]**, **R[i]**, and an identifier **C[i]**.

If you activate range **i**, every pair of nodes whose indices lie in the closed interval **[L[i], R[i]]** becomes fully connected (all pairs among those nodes get edges). Equivalently, activating a range covers every consecutive unit-edge \((k, k+1)\) for \(L[i] \le k < R[i]\).

Choose a non-empty subset of ranges so that node **1** becomes connected to node **N**, while minimizing **max(C) − min(C)** among the chosen ranges.

It is guaranteed that at least one connecting subset always exists. When **N = 1**, the answer is **0** (already connected).

## Input Format

- Line 1: integer **N**
- Line 2: integer **M**
- Next **M** lines: **L[i]** (one per line)
- Next **M** lines: **R[i]** (one per line)
- Next **M** lines: **C[i]** (one per line)

## Output Format

Print a single integer: the minimum achievable **max(C) − min(C)**.

## Constraints

- \(1 \le N \le 10^5\)
- \(1 \le M \le 10^5\)
- \(1 \le L[i], R[i] \le N\)
- \(1 \le C[i] \le 10^9\)

## Examples

### Example 1

**Input**
```
3
3
1
1
1
2
2
3
3
5
7
```

**Output**
```
0
```

Choosing only the third range connects 1 to 3 with a single ID, so the difference is 0.

### Example 2

**Input**
```
4
3
1
1
2
2
3
4
3
7
9
```

**Output**
```
2
```

Choosing the second and third ranges gives IDs 7 and 9; difference 2.

### Example 3

**Input**
```
10
4
1
3
5
2
3
5
10
10
1
3
5
7
```

**Output**
```
4
```
