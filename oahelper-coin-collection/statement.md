# Coin Collection

Agoda's new mobile game is built on a narrow board: exactly **2 rows** and **n columns**. Every cell `(r, c)` starts with a base coin value `coins[r][c]`. Coins grow with time — when a player steps onto a cell at time `t`, they collect `t * coins[r][c]` coins from that cell.

A valid playthrough must:

- start at cell `(0, 0)` at time `t = 0`
- move to an adjacent cell (sharing an edge) in one unit of time per move
- visit **every** cell of the board **exactly once**

Find the maximum total coins a player can collect over any valid playthrough.

## Input Format

- Line 1: an integer `n` — the number of columns.
- Line 2: `n` integers `coins[0][0] … coins[0][n-1]` — the top row.
- Line 3: `n` integers `coins[1][0] … coins[1][n-1]` — the bottom row.

## Output Format

A single integer — the maximum number of coins collectible on a valid path.

## Constraints

- `1 <= n <= 10^5`
- `1 <= coins[r][c] <= 10^5`

## Examples

### Example 1

**Input**
```
4
1 4 3 2
2 1 3 2
```

**Output**
```
77
```

**Explanation**

One optimal path is
`(0,0) → (1,0) → (1,1) → (1,2) → (1,3) → (0,3) → (0,2) → (0,1)`.
Coins collected at times `0…7` are `0 + 2 + 2 + 9 + 8 + 10 + 18 + 28 = 77`.

### Example 2

**Input**
```
2
1 3
4 2
```

**Output**
```
19
```

**Explanation**

Path `(0,0) → (0,1) → (1,1) → (1,0)` yields
`(0·1) + (1·3) + (2·2) + (3·4) = 19`.

### Example 3

**Input**
```
1
1
11
```

**Output**
```
11
```

**Explanation**

The only path is `(0,0) → (1,0)`, collecting `0·1 + 1·11 = 11`.
