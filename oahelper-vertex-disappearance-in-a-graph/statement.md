# Vertex Disappearance in a Graph

A research lab is studying how a fragile communication network collapses. The network is an undirected graph with **N** vertices numbered from **0** to **N − 1**, and **M** edges. Edge **k** connects vertices **A[k]** and **B[k]**.

Every second, **every** vertex that currently has at most one incident edge disappears at the same time. All edges incident to a disappearing vertex disappear with it.

How many seconds pass until no further vertices can disappear? If no vertex ever disappears, the answer is **0**.

## Input Format

- The first line contains two integers **N** and **M**.
- The second line contains **M** integers: array **A**.
- The third line contains **M** integers: array **B**.
- Edge **k** connects **A[k]** and **B[k]**.

## Output Format

Print a single integer: the number of seconds until vertices stop disappearing.

## Constraints

- \(2 \le N \le 10^5\)
- \(1 \le M \le 10^5\)
- \(0 \le A[k], B[k] \le N - 1\)
- No self-loops and no multiple edges

## Examples

### Example 1

**Input**
```
7 6
0 1 2 1 4 4
1 2 0 4 5 6
```

**Output**
```
2
```

After the first second, vertices 3, 5, and 6 disappear. After the next second, vertex 4 disappears. Vertices 0, 1, and 2 form a triangle and never disappear, so the answer is 2.

### Example 2

**Input**
```
7 5
0 1 2 4 5
1 2 3 5 6
```

**Output**
```
2
```

### Example 3

**Input**
```
4 4
0 1 2 3
1 2 3 0
```

**Output**
```
0
```

Every vertex has degree 2, so nothing disappears.

### Example 4

**Input**
```
4 3
0 1 2
1 2 0
```

**Output**
```
1
```
