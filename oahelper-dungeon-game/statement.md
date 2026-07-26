# Dungeon Game

The wicked witch has captured the prince and locked him in the bottom-right room of an `m × n` dungeon. A knight starts in the top-left room and must reach the prince. She begins with some positive integer health; if her health ever drops to `0` or below, she dies immediately.

Each room contains an integer:

- a **negative** value means the knight loses that much health on entering;
- `0` means the room is empty;
- a **positive** value means a potion that restores that much health.

The knight may move only **right** or **down**. Any room may contain demons or potions, including the start and the prince's cell.

Determine the **minimum initial health** the knight needs to reach the prince alive along some path of only right/down moves. Health must stay at least `1` after entering every room on the path (including the first and last).

## Input Format

- First line: two integers `m` and `n` — the number of rows and columns.
- Next: `m × n` integers in row-major order — the dungeon values `dungeon[i][j]`.

(Alternatively, all values may appear on a single line: `m n` followed by the `m·n` cell values.)

## Output Format

Print a single integer — the minimum initial health required.

## Constraints

- `1 ≤ m, n ≤ 100`
- `-1000 ≤ dungeon[i][j] ≤ 1000`

## Examples

### Example 1

**Input**
```
3 3
-2 -3 4
-6 -15 0
10 25 -6
```

**Output**
```
8
```

**Explanation:** One optimal path is RIGHT → RIGHT → DOWN → DOWN. The knight needs initial health `8`.

### Example 2

**Input**
```
1 1
-5
```

**Output**
```
6
```

**Explanation:** Entering the only room costs `5` health; she must still have `1` left, so she needs `6` at the start.

### Example 3

**Input**
```
1 1
100
```

**Output**
```
1
```

**Explanation:** A potion cannot reduce the needed start below `1`.
