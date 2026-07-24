# Tree Good Pairs

You are given a tree with `n` nodes (numbered `0 … n-1`), **rooted at node 0**. Every node has a
weight, and every edge has a (non-negative) weight.

For an ordered pair of distinct nodes `(u, v)` where `u` is a **strict ancestor** of `v`, let
`pathWeight(u, v)` be the sum of the edge weights on the path from `u` down to `v`.

The pair `(u, v)` is **good** if:

```
pathWeight(u, v) ≤ nodeWeight[v]
```

Count the number of good pairs.

## Input
```
n
w_0 w_1 … w_{n-1}          (node weights)
a_1 b_1 c_1               ) n-1 lines: an undirected edge between a_i and b_i
…                          ) with weight c_i
a_{n-1} b_{n-1} c_{n-1}
```
Nodes are 0-indexed and the tree is rooted at node 0.

## Output
A single integer — the number of good `(ancestor, descendant)` pairs.

## Constraints
- `1 ≤ n ≤ 100000`
- `0 ≤ node weight ≤ 10^9`
- `0 ≤ edge weight ≤ 10^6`

## Example
Input:
```
4
5 3 10 2
0 1 4
1 2 3
0 3 10
```
Output:
```
2
```
Distances from the root: `ds = [0, 4, 7, 10]`. Checking each descendant `v` against its strict
ancestors: node 2 (weight 10) is good with both ancestor 0 (`7 ≤ 10`) and ancestor 1 (`3 ≤ 10`);
node 1 (`4 ≤ 3`? no) and node 3 (`10 ≤ 2`? no) contribute nothing. Total = 2.
