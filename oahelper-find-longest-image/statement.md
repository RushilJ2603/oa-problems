# Find Longest Image

An imaging pipeline stores a photo as an `n × m` grid of pixel color intensities. You may crop the photo by keeping a **contiguous block of columns** and discarding the rest.

A row inside a crop is **consistent** when the difference between its brightest and darkest pixel in the kept columns is at most `k`. A crop is **good** when every row is consistent.

Find the largest number of columns that any good crop can keep.

## Input

- Line 1: integer `k`
- Line 2: two integers `n` `m` — rows and columns
- Next `n` lines: `m` integers each — the color values of that row

## Output

A single integer: the maximum width (number of columns) of a good crop. A single-column crop is always good, so the answer is at least `1`.

## Constraints

- `1 ≤ n ≤ 20`
- `1 ≤ m ≤ 10^5`
- `0 ≤ k ≤ 10^9`
- `1 ≤ colors[i][j] ≤ 10^9`

## Examples

### Example 1

**Input**
```
10
3 3
2 1 2
2 2 2
1 9 1
```

**Output**
```
3
```

**Explanation**

Every row already satisfies `max − min ≤ 10` over all three columns, so the full image is good.

### Example 2

**Input**
```
1
3 2
3 6
5 7
100 95
```

**Output**
```
1
```

**Explanation**

Both columns together violate the limit in every row, so only width-1 crops work.

### Example 3

**Input**
```
2
2 5
10 5 6 7 20
1 2 3 4 5
```

**Output**
```
3
```

**Explanation**

Columns `[5, 6, 7]` / `[2, 3, 4]` form a good crop of width 3; no wider crop works.
