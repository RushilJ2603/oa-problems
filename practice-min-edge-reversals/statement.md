# Minimum Edge Reversals to Reach Destination

You are given a **directed** graph with `n` nodes (numbered `1..n`) and `m` directed edges. You start
at node `s` and want to reach node `t`.

You may travel along a directed edge `u → v` in its given direction for free. You may also travel a
directed edge **against** its direction (from `v` to `u`), but doing so **reverses** that edge and
costs `1`.

Find the **minimum total number of edge reversals** needed to get from `s` to `t`. If `t` cannot be
reached even by reversing edges, output `-1`.

## Input

```
n m
u_1 v_1
...
u_m v_m
s t
```

- The first line has two integers `n` and `m`.
- Each of the next `m` lines has a directed edge `u_i → v_i`.
- The last line has the start node `s` and the target node `t` (`s != t`).

## Output

A single integer: the minimum number of edge reversals to go from `s` to `t`, or `-1` if it is
impossible.

## Constraints

- `2 ≤ n ≤ 200000`
- `0 ≤ m ≤ 400000`
- `1 ≤ u_i, v_i, s, t ≤ n`, `u_i != v_i`, `s != t`
- Multiple edges and cycles may appear.

## Example 1

**Input**
```
4 3
1 2
2 3
3 4
1 4
```
**Output**
```
0
```
The path `1 → 2 → 3 → 4` follows every edge forward, so no reversals are needed.

## Example 2

**Input**
```
4 3
2 1
3 2
4 3
1 4
```
**Output**
```
3
```
Every edge points backwards along the path `1 … 4`, so all three must be reversed.
