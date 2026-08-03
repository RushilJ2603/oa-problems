# Island Safe Zone Navigation

You are given an \(M \times N\) grid. Cells in the grid can be one of two types:

- **Islands:** There are islands denoted by positive integers (their health cost).
- **Water:** Denoted by `0`.

A few cells are designated **safe cells**; together they form the Safe Zone.

You begin at a given island cell. Your objective is to reach an island cell that is part of the Safe Zone.

**Movement rules (commit to this reading):**

1. You may only travel through water. From your starting island you must first step onto an orthogonally adjacent water cell.
2. From a water cell you may move to an orthogonally adjacent water cell, or step onto an orthogonally adjacent island cell **only if that island cell is in the Safe Zone**.
3. Non-safe island cells block travel — you cannot step onto them or pass through them.

You start with health \(Z\). Stepping onto a cell with value \(i\) decreases health by \(i\) (water costs `0`). The starting island's value is **not** charged when you leave it; only the destination Safe Zone island is charged (water cells cost nothing along the way).

Print the maximum remaining health on arrival at a Safe Zone island. If health would drop to `0` or below, print `Died x` where `x` is the minimum extra starting health needed so that remaining health would be exactly `1`. If no Safe Zone island is reachable through water, print `Impossible`.

If your starting cell is itself a Safe Zone island, print \(Z\) immediately (no travel needed).

## Input Format

- First line: two integers \(M\) \(N\) — rows and columns.
- Next \(M\) lines: \(N\) integers each — the grid.
- Next line: two integers \(sr\) \(sc\) — 0-based starting coordinates.
- Next line: integer \(Z\) — initial health.
- Next line: integer \(S\) — number of safe cells.
- Next \(S\) lines: two integers \(r\) \(c\) each — 0-based safe-cell coordinates.

## Output Format

A single line: either a positive integer (remaining health), `Died x`, or `Impossible`.

## Constraints

- \(1 \le M, N \le 500\)
- \(0 \le\) grid values \(\le 10^9\)
- \(1 \le Z \le 10^{18}\)
- \(1 \le S \le M \cdot N\)
- Start cell is always an island (value \(> 0\)).
- Coordinates are 0-based and lie inside the grid.

## Examples

### Example 1

**Input**
```
3 3
1 0 0
0 0 2
0 0 0
0 0
10
1
1 2
```

**Output**
```
8
```

Path through water to the safe island of cost 2: remaining health \(10 - 2 = 8\).

### Example 2

**Input**
```
3 3
1 0 0
0 0 5
0 0 0
0 0
3
1
1 2
```

**Output**
```
Died 3
```

Cost 5 exceeds health 3; extra needed is \(5 - 3 + 1 = 3\).

### Example 3

**Input**
```
2 2
1 0
0 0
0 0
5
1
0 0
```

**Output**
```
5
```

Start is already safe.

### Example 4

**Input**
```
3 3
1 0 0
0 0 2
0 0 3
0 0
10
2
1 2
2 2
```

**Output**
```
8
```

Choose the cheaper reachable safe island (cost 2).

### Example 5

**Input**
```
1 6
1 0 10 0 0 2
0 0
5
2
0 2
0 5
```

**Output**
```
Died 6
```

Island 10 blocks the water channel, so only the cost-10 safe cell is reachable; extra health needed is 6.

### Example 6

**Input**
```
5 5
1 0 0 0 0
0 0 1 1 0
0 1 1 1 0
0 1 1 50 0
0 0 0 0 2
0 0
10
2
3 3
4 4
```

**Output**
```
8
```
