# Minimum Operations for Odd Computation Times

A neural-network inference engine records the per-layer computation time in an array `computationalTime` of length \(n\). For the next release, every layer must run in an **odd** number of time units.

You may perform the following operation any number of times:

- Choose an **even** value \(c\) that currently appears in the array.
- Replace **every** occurrence of \(c\) with \(c / 2\) (integer division).

Find the **minimum** number of operations needed so that every entry is odd.

## Input

- First line: an integer \(n\) — the number of layers.
- Second line: \(n\) integers `computationalTime[1..n]`.

## Output

Print a single integer — the minimum number of operations.

## Constraints

- \(1 \le n \le 2 \cdot 10^5\)
- \(1 \le \mathrm{computationalTime}[i] \le 10^9\)

## Examples

### Example 1

**Input**
```
4
2 4 8 16
```

**Output**
```
4
```

**Explanation.** One optimal sequence:

1. Choose \(c = 16\) → `[2, 4, 8, 8]`
2. Choose \(c = 8\) → `[2, 4, 4, 4]`
3. Choose \(c = 4\) → `[2, 2, 2, 2]`
4. Choose \(c = 2\) → `[1, 1, 1, 1]`

Four operations are necessary and sufficient.

### Example 2

**Input**
```
10
1 3 5 7 9 11 13 15 17 19
```

**Output**
```
0
```

**Explanation.** Every value is already odd, so no operations are needed.

### Example 3

**Input**
```
5
128 128 128 128 128
```

**Output**
```
7
```

**Explanation.** All five layers share the same even value. Halving \(128\) repeatedly (\(128 \to 64 \to 32 \to 16 \to 8 \to 4 \to 2 \to 1\)) takes 7 operations; duplicates are handled together each time.
