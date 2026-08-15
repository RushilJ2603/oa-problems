## Minimize Path Value

You have a weighted undirected graph with `graph_nodes` nodes and `m` edges. The stress level of a path between two nodes is defined as the weight of the heaviest edge in that path.

Given a source node `source` and a destination node `destination`, find the minimum possible stress level of a path. If no such path exists, return -1.

### Input Format

The first line contains two integers `graph_nodes` and `m` — the number of nodes and edges.
Each of the next `m` lines contains three integers `u`, `v`, and `w` — an edge between nodes `u` and `v` with weight `w`.
The next line contains a single integer `source` — the source node.
The last line contains a single integer `destination` — the destination node.

### Output Format

Print a single integer — the value of the least stressful path, or -1 if no path exists.

### Constraints

- `1 <= graph_nodes <= 10^5`
- `1 <= m <= 10^5`
- `1 <= u, v, source, destination <= graph_nodes`
- `0 <= w <= 10^9`

### Examples

**Example 1**

Input:
```
5 6
1 2 10
2 3 5
1 4 3
4 3 2
1 5 4
5 3 6
1
3
```

Output:
```
3
```

Explanation:
There are three paths, from node 1 to node 3:
1. 1 -> 2 -> 3. Edges have weights 10 and 5, the maximum weighted edge, and the stress level is 10.
2. 1 -> 4 -> 3. Edges have weights 3 and 2, and the stress level = 3.
3. 1 -> 5 -> 3. Edges have weights 4 and 6, and the stress level = 6.
Return 3, the lower stress level from the second path.

**Example 2**

Input:
```
3 1
1 2 10
1
3
```

Output:
```
-1
```

Explanation:
There is no path, from node 1 to node 3.
