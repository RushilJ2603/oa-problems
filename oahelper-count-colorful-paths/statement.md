# Count Colorful Paths

A fitness studio maps its floor as an $N \times M$ grid. Every tile is painted with a color coded by an integer. Instructors must walk from the top-left tile $(0,0)$ to the bottom-right tile $(N-1,M-1)$, moving only **right** or **down** on each step.

A route is called *colorful* if **no color repeats** anywhere along that route: every tile on the path must carry a distinct color value.

Count how many colorful routes exist from start to finish.

## Input

- First line: two integers $N$ and $M$ — the number of rows and columns.
- Next $N$ lines: $M$ integers each — the color of cell $(i,j)$.

## Output

A single integer — the number of colorful paths from $(0,0)$ to $(N-1,M-1)$.

## Constraints

- $1 \le N, M \le 10$
- $0 \le \mathrm{grid}[i][j] \le 100$

## Examples

### Example 1

**Input**
```
3 3
1 2 3
4 5 6
7 8 9
```

**Output**
```
6
```

**Explanation**

All nine colors are distinct, so every lattice path is colorful. A $3 \times 3$ grid has $\binom{4}{2} = 6$ right/down paths.

### Example 2

**Input**
```
3 3
1 1 1
1 1 1
1 1 1
```

**Output**
```
0
```

**Explanation**

Every path longer than one cell reuses color $1$, so no colorful path exists. (A single-cell grid would still count as $1$.)

### Example 3

**Input**
```
3 3
1 2 3
2 4 2
3 5 6
```

**Output**
```
3
```

**Explanation**

Some right/down routes reuse a color (for example any path that visits both cells colored $2$); exactly three routes keep all colors unique.
