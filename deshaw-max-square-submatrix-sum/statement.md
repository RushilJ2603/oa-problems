# Largest Square Submatrix With Sum At Most K

You are given an **m × n** grid of non-negative integers and a value **k**.

Consider every **square** contiguous submatrix of the grid (an L × L block of cells). Find the
**largest side length L** for which at least one L × L square has a sum **≤ k**.

If not even a single cell (a 1 × 1 square) has value ≤ k, the answer is **0**.

## Input Format

- Line 1: three integers **m**, **n**, **k**.
- Next **m** lines: **n** non-negative integers each — the grid.

## Output Format

- A single integer — the largest side length L of a square submatrix whose sum is ≤ k (0 if none).

## Constraints

- $1 \le m, n \le 300$
- $0 \le \text{grid}[i][j] \le 10^9$
- $0 \le k \le 10^{18}$

## Examples

### Example 1

**Input:**
```
3 3 4
1 1 1
1 1 1
1 1 1
```

**Output:**
```
2
```

A 2 × 2 block sums to 4 ≤ 4, but the whole 3 × 3 sums to 9 > 4, so the largest valid side is 2.

### Example 2

**Input:**
```
2 2 0
1 2
3 4
```

**Output:**
```
0
```

Every cell is greater than 0, so no square (not even 1 × 1) has sum ≤ 0.

### Example 3

**Input:**
```
2 3 100
1 2 3
4 5 6
```

**Output:**
```
2
```

The whole grid is not square. The best square is 2 × 2 (e.g. the left block `1 2 / 4 5` sums to 12 ≤ 100).
