# Cutting Edges

A logistics warehouse receives cargo labeled with a long digit string **S**. The manager may place cuts between adjacent digits to break **S** into contiguous pieces. Each piece is a container ID and is valid only when:

1. It forms an integer divisible by **3** (equivalently, the sum of its digits is divisible by 3), and
2. It has **no leading zeros**, except for the single-digit ID `0`.

Every digit of **S** must belong to exactly one piece — the pieces must form a complete partition of **S**. Among all complete partitions into valid IDs, find the **maximum** number of pieces. If no complete valid partition exists, the answer is **0**.

## Input Format

A single line containing the digit string **S**.

## Output Format

Print one integer: the maximum number of valid container IDs in a complete partition, or `0` if impossible.

## Constraints

- \(1 \le |S| \le 10^5\)
- **S** consists only of digits `0`–`9`

## Examples

### Example 1

**Input:**
```
369
```

**Output:**
```
3
```

**Explanation:** Split as `3|6|9` — three IDs, each divisible by 3.

### Example 2

**Input:**
```
120
```

**Output:**
```
2
```

**Explanation:** Split as `12|0`. Using the whole string `120` yields only one piece.

### Example 3

**Input:**
```
10
```

**Output:**
```
0
```

**Explanation:** Neither `1`, `0` alone (leaving a leftover), nor `10` is a complete valid partition of all digits into valid IDs.
