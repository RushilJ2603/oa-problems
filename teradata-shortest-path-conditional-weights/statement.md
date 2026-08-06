> **Statement only.** Transcribed from the Teradata OA (2 hours, 3 questions, 100 points). There is
> no auto-judge for this one — read it, solve it on paper or in the Compiler tab.

# Shortest Path with Conditional Edge Weights

Given an undirected graph where all edges normally have weight 1, you need to find the shortest path
from a source node to all other nodes. However, there's a special constraint: **any edge that
connects to a designated "special node" `V` has its weight reduced to 0 instead of 1.**

**Function Description:** You need to implement the function `findShortestPathsWithConstraints` that
takes a graph and a source node and returns the shortest distances from the source node to all other
nodes, considering the given constraints.

**Parameters:**
- `N`: Number of nodes in the graph (nodes are numbered 1 to N)
- `M`: Number of edges in the graph
- `edges`: A 2D array where each `edges[i]` contains `[u, v]` representing an undirected edge between
  nodes `u` and `v`
- `V`: The special node that triggers weight reduction (any edge touching this node has weight 0)
- `source`: The starting node for shortest path calculation

**Return:** An array of size `N` where `result[i]` represents the shortest distance from the source
node to node `(i+1)`. If a node is unreachable, return `-1` for that position.

**Input Format:**
- The first line contains a single integer `N`, the number of nodes in the graph.
- The second line contains a single integer `M`, the number of edges.
- The next `M` lines each contain two space-separated integers `u` and `v` (1-indexed). All edges
  have an initial weight of 1. The graph is undirected.
- The next line contains a single integer `V`, representing the special node through which connected
  edges have their weight reduced to 0.
- The last line contains a single integer `source`, the source node.

**Output Format:** Return a single line containing a space-separated list of integers, where each
integer at index `i` represents the shortest distance from the source node to node `i+1`
(1-indexed). If a node is unreachable, return `-1` for that node.

**Constraints:**
- `1 <= N <= 10^5`
- `0 <= M <= N * (N - 1) / 2`
- `1 <= source <= N`
- `1 <= V <= N`

**Sample Input 1:**
```
5
5
0 1
1 2
2 3
3 4
1 3
2
0
```
**Sample Output 1:**
```
0 1 1 1 2
```
**Explanation:** Graph with weights: since `V = 2`, any edge connected to node 2 has weight 0, all
others have weight 1:

- Edge (0,1): weight = 1 (neither endpoint is 2)
- Edge (1,2): weight = 0 (node 2 is V)
- Edge (2,3): weight = 0 (node 2 is V)
- Edge (3,4): weight = 1 (neither endpoint is 2)
- Edge (1,3): weight = 1 (neither endpoint is 2)

Shortest paths from node 0:

- Node 0 → Node 0: distance = 0 (starting point)
- Node 0 → Node 1: 0→1, distance = 1
- Node 0 → Node 2: 0→1→2, distance = 1+0 = 1
- Node 0 → Node 3: 0→1→2→3, distance = 1+0+0 = 1 (not 3!)
- Node 0 → Node 4: 0→1→2→3→4, distance = 1+0+0+1 = 2 (not 4!)

Output: `0 1 1 1 2`

> **Note on the indexing, as it appeared in the OA:** the input format says nodes are 1-indexed, but
> the sample input and its explanation use nodes `0`–`4` with `source = 0`. The statement is
> transcribed as shown; treat the sample as the authority on what the judge actually feeds you.

---

**Given signature (C++17):**
```cpp
vector<int> findShortestPathsWithConstraints(int N, int M, vector<vector<int>> edges, int V, int source) {
    // Write your code here
}
```

**OA limits as shown:** Time 5.0 sec/input file · Memory 256 MB · Source 1024 KB.
Scoring: score is assigned if any testcase passes. Worth 100.00 points.
