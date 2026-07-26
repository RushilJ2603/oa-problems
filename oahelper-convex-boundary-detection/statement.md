# Convex Boundary Detection

Nokia's field team planted sensor nodes across a flat survey area. Each node is a point $(x, y)$ on the plane. You must design a protective fence that tightly encloses every node and runs along the outermost ones.

Return every node that lies on the boundary of that fence.

**Rules**

- The fence is the convex enclosure of all nodes.
- Include every node that lies on the perimeter — if several nodes are collinear on a boundary edge, include all of them.
- Report each distinct node once, sorted in lexicographical order (smaller $x$ first; if tied, smaller $y$ first).

## Input Format

- Line 1: integer $N$ — the number of nodes
- Next $N$ lines: two integers $x_i$ $y_i$ — coordinates of node $i$

## Output Format

Print the boundary nodes, one per line as `x y`, in lexicographical order.

## Constraints

- $1 \le N \le 3000$
- $0 \le x_i, y_i \le 10^4$

## Examples

### Example 1

Input:
```
6
1 1
2 2
2 0
2 4
3 3
4 2
```

Output:
```
1 1
2 0
2 4
3 3
4 2
```

Explanation: Node $(2, 2)$ is strictly inside the enclosure and is omitted. Nodes on the outer edges are kept.

### Example 2

Input:
```
1
5 5
```

Output:
```
5 5
```

Explanation: A single node is its own boundary.

### Example 3

Input:
```
9
0 0
0 2
2 0
2 2
1 0
0 1
2 1
1 2
1 1
```

Output:
```
0 0
0 1
0 2
1 0
1 2
2 0
2 1
2 2
```

Explanation: Midpoints of the square's sides lie on the perimeter and must be included; the center $(1, 1)$ does not.
