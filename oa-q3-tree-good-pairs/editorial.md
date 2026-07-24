# Editorial — Tree Good Pairs

Root the tree at 0 and let `ds[x]` be the sum of edge weights from the root to `x`. For a strict
ancestor `u` of `v`, the path weight is `ds[v] − ds[u]`, so the pair is good when

```
ds[v] − ds[u] ≤ nodeWeight[v]   ⇔   ds[u] ≥ ds[v] − nodeWeight[v].
```

DFS from the root, keeping the `ds` values of the current root-to-node path on a stack. Because edge
weights are non-negative, that stack is **non-decreasing**, so the number of ancestors with
`ds[u] ≥ threshold` is found with a single binary search (`lower_bound`) — `O(log n)` per node,
`O(n log n)` overall.

Use an **iterative** DFS (explicit stack with enter/leave phases): a path-shaped tree has depth `n`,
which would overflow a recursive call stack at `n = 10^5`. With negative edge weights the stack
wouldn't stay sorted and you'd instead keep a Fenwick tree over compressed `ds` values.
