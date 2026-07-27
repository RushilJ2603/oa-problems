# Dynamic Network Strength

A network has `n` nodes labelled `1..n`. Initially there are **no edges**, so every node is its own
connected component.

Edges are added one at a time. At the `i`-th second an undirected edge is added between nodes
`u_i` and `v_i`.

The **strength** of a connected component is the largest node label in that component. The
**network strength** is the sum of the strengths of all connected components currently present.

After each edge is added, report the network strength. If an edge joins two nodes already in the same
component, the network is unchanged (but you still report the strength for that second).

## Input

```
n m
u_1 v_1
u_2 v_2
...
u_m v_m
```

- Line 1: `n` (number of nodes) and `m` (number of edges).
- Each of the next `m` lines: an edge `u_i v_i`.

## Output

`m` integers separated by spaces: the network strength after each edge is added, in order.

## Constraints

- `1 ≤ n ≤ 200000`
- `1 ≤ m ≤ 200000`
- `1 ≤ u_i, v_i ≤ n`
- Self-loops (`u_i = v_i`) and duplicate/redundant edges may appear.

> The initial strength before any edge (`1 + 2 + ... + n`) is **not** part of the output.

## Example 1

**Input**
```
5 4
1 2
2 3
3 1
4 5
```
**Output**
```
14 12 12 8
```

Initially the components are `{1},{2},{3},{4},{5}` with total strength `15` (not printed).

- After `(1,2)`: `{1,2},{3},{4},{5}` → `2+3+4+5 = 14`.
- After `(2,3)`: `{1,2,3},{4},{5}` → `3+4+5 = 12`.
- After `(3,1)`: same component, unchanged → `12`.
- After `(4,5)`: `{1,2,3},{4,5}` → `3+5 = 8`.
