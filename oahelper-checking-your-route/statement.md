# Classify the edges

You are developing a system for a ride-hailing company that needs to identify the shortest routes between cities. The cities and roads are represented as a graph with nodes and edges.

Your task is to determine all paths from the first node (node 1) to the last node (node `g_nodes`), identify those with the shortest length, and classify each road as being part of any shortest path or not. All roads are bi-directional (undirected).

**Function Description**

Complete the function `classifyEdges` in the editor with the following parameter(s):

- `int g_nodes`: the number of nodes
- `int g_from[g_edges]`: one end of each road
- `int g_to[g_edges]`: the other end of each road
- `int g_weight[g_edges]`: the length of each road

**Returns**

`string[g_edges]`: the value at the i^th index is "YES" if the i^th edge is a part of a shortest path from vertex 1 to vertex `g_nodes`. Otherwise, it should contain "NO".

**Constraints**

- 2 <= `g_nodes` <= 3000
- 1 <= `g_edges` <= min(10^5, (g_nodes * (g_nodes - 1)) / 2)
- 1 <= `g_weight[i]` <= 10^5
- 1 <= `g_from[i]`, `g_to[i]` <= `g_nodes`
- There is at most one edge between any pair of `g_nodes`.
- The graph is connected.

**Example 1**

Input:
```
4 5
1 2 1
2 4 1
1 3 1
3 4 2
1 4 2
```
Output:
```
YES
YES
NO
NO
YES
```

**Example 2**

Input:
```
5 7
1 2 1
2 3 1
3 5 1
1 4 1
4 5 2
3 4 2
2 4 4
```
Output:
```
YES
YES
YES
YES
YES
NO
NO
```
