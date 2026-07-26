# Ascending Path in a Grid

Epam's on-campus sensor network lays antivirus threat scores on an **m × n** floor plan. Each cell holds a non-negative integer reading. An inspector may start at any cell and walk to an orthogonally adjacent cell (up, down, left, or right) — never diagonally and never off the floor. To keep the trail trustworthy, every step must land on a **strictly larger** reading than the previous cell.

Your task is to find the length of the longest such ascending walk (number of cells visited).

## Rules

- You may start at any cell.
- From a cell you may move to any of its four orthogonal neighbours that lie inside the grid.
- A move from cell A to cell B is allowed only when `matrix[B] > matrix[A]` (strictly increasing).
- Equal values cannot be chained; a grid of identical readings has longest path length **1**.
- The path length is the number of cells on the path (a single cell counts as length 1).

## Input Format

- Line 1: integer **m** — number of rows.
- Line 2: integer **n** — number of columns.
- Next **m** lines: each contains **n** integers — the matrix row.

## Output Format

Print a single integer — the length of the longest strictly ascending path.

## Constraints

- \(1 \le m, n \le 200\)
- \(0 \le \texttt{matrix}[i][j] \le 2^{31}-1\)

## Examples

### Example 1

**Input**
```
3
3
9 9 4
6 6 8
2 1 1
```

**Output**
```
4
```

**Explanation:** One longest path is `1 → 2 → 6 → 9` (length 4).

### Example 2

**Input**
```
3
3
3 4 5
3 2 6
2 2 1
```

**Output**
```
4
```

**Explanation:** One longest path is `3 → 4 → 5 → 6` (length 4).
