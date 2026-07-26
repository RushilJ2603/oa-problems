# Highly Influential People

Tom is forming a new political party and needs activists with real sway in their villages. He has built a directed social graph of **N** people (numbered **0** to **N-1**): an entry of `1` at row `i`, column `j` means person `i` knows person `j`.

A person's **reach** is the number of people they know (the number of `1`s in their row). Among everyone, first identify the people with **maximum reach**. Then, among those candidates only, compute a **influence score**: the sum of the reaches of the people they know. The highly influential people are exactly the candidates whose influence score is maximum.

Print their node indices in ascending order on a single line, separated by spaces.

## Input Format

- Line 1: integer `N` — number of people.
- Next `N` lines: `N` integers each (`0` or `1`) — the adjacency matrix. Row `i`, column `j` is `1` if person `i` knows person `j`.

## Output Format

- One line: the indices of all highly influential people, in ascending order, separated by spaces.

## Constraints

- `3 ≤ N ≤ 149`
- `0 ≤ arr[i][j] ≤ 1`
- The matrix need not be symmetric (knowing is directed). Self-loops (`arr[i][i] = 1`) are allowed and count toward reach.

## Examples

### Example 1

**Input**
```
5
0 1 1 1 0
1 0 0 1 1
1 0 0 1 0
1 1 1 0 0
0 1 0 0 0
```

**Output**
```
0 3
```

**Explanation**

Reaches are `[3, 3, 2, 3, 1]`. Maximum reach is `3`, so candidates are `{0, 1, 3}`.

- Score of `0`: reach(1)+reach(2)+reach(3) = `3+2+3 = 8`
- Score of `1`: reach(0)+reach(3)+reach(4) = `3+3+1 = 7`
- Score of `3`: reach(0)+reach(1)+reach(2) = `3+3+2 = 8`

Maximum score is `8`, so nodes `0` and `3` are printed.

### Example 2

**Input**
```
8
0 1 1 1 1 0 0 0
1 0 1 1 1 0 1 1
1 1 0 1 0 0 1 0
1 1 1 0 1 1 1 0
1 1 0 1 0 0 0 0
0 0 0 1 0 0 0 0
0 1 1 1 0 0 0 0
0 1 0 0 0 0 0 0
```

**Output**
```
1 3
```

### Example 3

**Input**
```
3
0 1 0
1 0 1
0 1 0
```

**Output**
```
1
```

**Explanation**

Reaches `[1, 2, 1]`. Only node `1` has maximum reach; it is the sole answer (score equals reach(0)+reach(2) = `2`).
