# Cycle Detection in a Graph

Given $n$ nodes, numbered from $1$ to $n$, and $m$ directed edges. The edges are provided as a list of pairs of integers, where each pair $(u,v)$ in the `edges` list represents a directed edge from node $u$ to node $v$.

Find the total number of nodes out of $n$ that can be chosen such that none of them have a cyclic dependency on each other within the chosen subset. In other words, find the size of the largest subset of nodes such that the induced subgraph on this subset contains no directed cycles.

### Input Format
The first line contains two integers $n$ and $m$, the number of nodes and edges respectively.
The next $m$ lines each contain two integers $u$ and $v$ representing a directed edge from $u$ to $v$.

### Output Format
Print a single integer: the size of the largest acyclic subset of nodes.

### Constraints
- $1 \le n \le 20$
- $0 \le m \le n(n-1)$
- $1 \le u, v \le n$

### Example 1
**Input:**
```
2 2
1 2
2 1
```
**Output:**
```
1
```
**Explanation:** 
Nodes 1 and 2 form a cycle (1 -> 2 -> 1). If we choose both nodes {1, 2}, they have a cyclic dependency. However, we can choose a single node, for example, {1}, which forms an acyclic set. Similarly, we can choose {2}, which also forms an acyclic set. The maximum number of nodes we can choose such that none of them have a cyclic dependency on each other is 1.
