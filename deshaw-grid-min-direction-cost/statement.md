# Minimum Cost Path in a Direction Grid

You are given a grid of size **m × n**. Every cell holds one of four direction characters — `U`, `D`, `L`, `R` — which points to the single neighbouring cell you may step into **for free** from that cell:

- `U` → the cell **above** (row − 1)
- `D` → the cell **below** (row + 1)
- `L` → the cell to the **left** (column − 1)
- `R` → the cell to the **right** (column + 1)

You start at the top-left cell **(0, 0)** and want to reach the bottom-right cell **(m − 1, n − 1)**.

At any cell you may **change its direction** to any of the four directions. Changing a cell costs **1** (and lets you then move to any of its four in-grid neighbours); following a cell's existing arrow costs **0**. A move can never leave the grid.

Return the **minimum total cost** to travel from (0, 0) to (m − 1, n − 1).

## Input Format

- Line 1: two integers **m** and **n**.
- Next **m** lines: each a string of exactly **n** characters, each one of `U`, `D`, `L`, `R`.

## Output Format

- A single integer — the minimum cost.

## Constraints

- `1 ≤ m, n ≤ 500`
- `m · n ≤ 2.5 × 10^5`
- Every character is one of `U`, `D`, `L`, `R`.

## Examples

### Example 1

**Input:**
```
1 1
R
```

**Output:**
```
0
```

You already start on the destination, so the cost is 0.

### Example 2

**Input:**
```
1 4
RRRR
```

The single row is `RRRR`. Every arrow already points right, so you reach the end for free.

**Output:**
```
0
```

### Example 3

**Input:**
```
2 2
LL
LL
```

**Output:**
```
2
```

Every arrow points left. To get from (0,0) to (1,1) you must repoint two cells (for example (0,0)→`D` then (1,0)→`R`), each costing 1, for a total of 2.
