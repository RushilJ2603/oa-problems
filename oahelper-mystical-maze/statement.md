# Mystical Maze

In Eldoria, a maze is an \(M \times N\) grid. Cell \((i, j)\) has a non-negative energy cost. You start at the top-left cell \((0, 0)\) and must reach the bottom-right cell \((M-1, N-1)\). From any cell you may move only **right** or **down**, and you may never leave the grid.

Your energy budget is \(E\). Every cell you visit (including start and finish) adds its cost to your total. Determine whether there exists a legal path whose **total cost is at most \(E\)**.

Print `1` if such a path exists, otherwise `0`.

## Input Format

- Line 1: integer \(M\) (number of rows)
- Line 2: integer \(N\) (number of columns)
- Line 3: integer \(E\) (energy budget)
- Next \(M\) lines: each with \(N\) space-separated integers — the cell costs

## Output Format

Print a single integer: `1` or `0`.

## Constraints

- \(1 \le M, N \le 10^5\)
- \(1 \le M \cdot N \le 10^5\)
- \(0 \le E \le 10^9\)
- \(0 \le cost[i][j] \le 10^9\)

## Examples

### Example 1

**Input**
```
3
3
10
5 9 1
1 3 2
4 2 1
```

**Output**
```
0
```

**Explanation:** Every right/down path from the top-left to the bottom-right costs more than 10.

### Example 2

**Input**
```
4
4
50
1 3 1 5
2 8 2 1
4 3 1 2
7 1 2 3
```

**Output**
```
1
```

**Explanation:** There exists a path with total cost 13, which is within budget 50.

### Example 3

**Input**
```
1
1
100
10
```

**Output**
```
1
```

**Explanation:** A single cell is a valid path of cost 10.
