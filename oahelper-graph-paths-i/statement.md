# Counting Walks of Fixed Length

A courier network is modeled as a **directed** graph with `n` hubs (nodes numbered `1` … `n`) and `m` one-way routes (edges). Multiple routes between the same pair of hubs are allowed and count as distinct choices when building a walk.

You need the number of walks that start at hub `1`, end at hub `n`, and use **exactly** `k` edges. Because the count can be enormous, report it modulo `10^9 + 7`.

A walk may revisit hubs and edges freely. Self-loops are allowed and each use of a self-loop counts as one edge.

## Input Format

- The first line contains three integers `n`, `m`, and `k` — the number of nodes, the number of edges, and the required walk length.
- Each of the next `m` lines contains two integers `a` and `b` describing a directed edge from `a` to `b`.

## Output Format

Print a single integer — the number of walks of length `k` from node `1` to node `n`, modulo `10^9 + 7`.

## Constraints

- `1 ≤ n ≤ 100`
- `1 ≤ m ≤ n(n − 1)` (parallel edges may still appear in input; treat each listed edge separately)
- `1 ≤ k ≤ 10^9`
- `1 ≤ a, b ≤ n`

## Examples

### Example 1

Input:
```
5 3 17
5 2
5 5
3 3
```

Output:
```
0
```

Explanation: There is no edge leaving node `1`, so no walk of any positive length from `1` to `5` exists.

### Example 2

Input:
```
2 1 1
1 2
```

Output:
```
1
```

Explanation: The single edge `1 → 2` is itself a walk of length `1` from `1` to `2`.

### Example 3

Input:
```
5 8 3
1 2
1 3
1 4
1 5
2 1
3 1
4 1
5 1
```

Output:
```
4
```

Explanation: Every length-`3` walk from `1` to `5` goes out to a neighbor, back to `1`, then directly to `5`. There are four choices for the neighbor (`2`, `3`, `4`, or `5` via the direct edge used as the middle hop pattern), yielding `4` walks.
