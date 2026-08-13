# Office Placement

A campus is laid out as a grid of `h` rows by `w` columns. Every cell is a **plot**, and you must
build exactly `n` offices, each on its own plot — no two offices share a plot.

The **travel cost** from a plot to an office is the Manhattan distance between them: a plot at
`(r1, c1)` and an office at `(r2, c2)` are `|r1 - r2| + |c1 - c2|` apart. Every plot is served by
its **nearest** office, and a plot that holds an office is 0 away from itself.

Place the offices so that the **worst-served plot is as well served as possible**, and report that
worst distance.

Formally, over all ways to choose `n` distinct plots as offices, minimise

> max over all plots `P` of ( min over all offices `O` of distance(`P`, `O`) )

and output that minimum.

## Input Format

A single line:

```
h w n
```

## Output Format

One integer — the smallest achievable worst-case distance.

## Constraints

- \(1 \le h,\ w\)
- \(h \times w \le 27\)
- \(1 \le n \le \min(5,\ h \times w)\)

## Examples

### Example 1

**Input**
```
2 3 2
```

**Output**
```
1
```

**Explanation:** Put the offices in opposite corners. Writing each plot's distance to its nearest
office:

```
0 1 1
1 1 0
```

Every plot is within 1, and no placement of two offices does better on a 2×3 grid.

### Example 2

**Input**
```
1 1 1
```

**Output**
```
0
```

**Explanation:** The only plot holds the only office.

### Example 3

**Input**
```
3 3 1
```

**Output**
```
2
```

**Explanation:** One office is best placed at the centre, which leaves the four corners 2 away:

```
2 1 2
1 0 1
2 1 2
```
