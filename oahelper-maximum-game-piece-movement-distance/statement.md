# Maximum Game Piece Movement Distance

You are designing the scoring system for a one-dimensional board game. The board is a row of `N` cells. Each cell is either empty (`0`) or holds exactly one game piece (`1`).

Each piece may be moved **at most once**. A move shifts a piece one or more cells left or right onto an empty cell. Pieces **cannot occupy the same cell** and **cannot jump over** each other. Moving a piece by `X` cells contributes `X` to the total travel distance. Pieces may be moved in any order, one at a time.

Because pieces cannot cross, their left-to-right order is preserved. Your task is to choose (legal) moves so that the **sum of travel distances** over all pieces is maximized.

## Input Format

The input describes the board as a sequence of `0`/`1` values. It may appear either as:

- a bracketed list, e.g. `[1, 1, 0, 0, 1]`, or
- an integer `N` followed by `N` integers `board_1 … board_N` each equal to `0` or `1`.

## Output Format

Print a single integer — the maximum total travel distance.

## Constraints

- `1 ≤ N ≤ 40000`
- `board_i ∈ {0, 1}`

## Examples

### Example 1

**Input**
```
5
1 1 0 0 1
```

**Output**
```
4
```

**Explanation:** Move the piece at index `1` to index `3` (distance `2`), then the piece at index `0` to index `2` (distance `2`). Final layout `[0, 0, 1, 1, 1]`. Total `4`.

### Example 2

**Input**
```
2
0 1
```

**Output**
```
1
```

**Explanation:** The only piece moves one cell left.

### Example 3

**Input**
```
3
0 0 0
```

**Output**
```
0
```

**Explanation:** No pieces exist, so the total is `0`.
