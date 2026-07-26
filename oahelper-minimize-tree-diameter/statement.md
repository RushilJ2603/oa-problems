# Minimize Tree Diameter

A logistics network is an undirected tree on \(n\) vertices (numbered \(1 \dots n\)). You may perform at most \(k\) pruning operations. In one operation you choose a current leaf (a vertex of degree \(1\)) and delete it together with its incident edge. After a deletion, other vertices may become leaves and can be pruned in later operations.

The distance between two vertices is the number of edges on the unique path between them. The diameter of a tree is the maximum distance over all pairs of remaining vertices.

Find the smallest diameter you can achieve after at most \(k\) operations. If at most one vertex remains, the diameter is \(0\).

## Input

- First line: two integers \(n\) and \(k\) (\(1 \le n \le 2000\), \(0 \le k \le n\)).
- Then \(n-1\) lines follow, each with two integers \(u\) \(v\) describing an edge of the tree.

## Output

Print a single integer — the minimum achievable diameter.

## Examples

### Example 1

**Input**
```
1 0
```

**Output**
```
0
```

### Example 2

**Input**
```
2 1
1 2
```

**Output**
```
0
```

### Example 3

**Input**
```
5 2
1 2
1 4
2 3
2 5
```

**Output**
```
2
```

Deleting leaves \(3\) and \(5\) leaves the path \(4-1-2\) with diameter \(2\).

### Example 4

**Input**
```
8 3
1 2
2 3
3 4
4 5
5 6
6 7
7 8
```

**Output**
```
4
```

## Constraints

- \(1 \le n \le 2000\)
- \(0 \le k \le n\)
- The input edges form a tree on \(n\) vertices
