# Hiking Cost

John wants to hike a set of trails whose difficulty levels are given in an array **A** of length **N**. He must start at trail index `0` (whose difficulty is always `0`), visit **every** trail exactly once, and finally return to trail `0`.

The cost of moving between two trails is the absolute difference of their difficulty levels. For any order of visiting the trails, define the **trip cost** as the **maximum** single-move cost along that route (including the final return to the start).

Find the minimum possible trip cost over all valid visiting orders.

## Input Format

- Line 1: integer `N` — number of trails.
- Line 2: `N` integers `A[0] A[1] … A[N-1]` — difficulty levels. It is guaranteed that `A[0] = 0`.

## Output Format

- A single integer — the minimum achievable trip cost.

## Constraints

- `1 ≤ N ≤ 100000`
- `0 ≤ A[i] ≤ 1000000000`
- `A[0] = 0`

## Examples

### Example 1

**Input**
```
5
0 3 6 7 8
```

**Output**
```
6
```

**Explanation**

One optimal order of difficulties is `0 → 6 → 7 → 8 → 3 → 0`. The move costs are `6, 1, 1, 5, 3`; the maximum is `6`. No route has a smaller maximum.

### Example 2

**Input**
```
3
0 5 10
```

**Output**
```
10
```

**Explanation**

Every route that visits all trails must eventually jump between `10` and `0` (or an equivalent-sized gap), so the minimum trip cost is `10`.

### Example 3

**Input**
```
2
0 5
```

**Output**
```
5
```
