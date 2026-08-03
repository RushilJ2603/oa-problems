A super virus is spreading, and researchers believe the best countermeasure is to carefully destroy cells in a dependency order that maximises the body's immune boost.

There are `X` cells labelled `1` to `X`. Destroying cell `i` yields an integer boost `b_i` (positive for virus cells, negative for human cells). Some cells have **prerequisites**: before cell `i` can be destroyed, every listed prerequisite cell must also be destroyed.

A set of cells `C` is **feasible** if whenever `i` is in `C`, every prerequisite of `i` is also in `C`. The boost of `C` is the sum of boosts of cells in `C`. The empty set is feasible and has boost `0`, so the answer is never negative.

The prerequisite structure is a DAG (no cycles). Find the maximum boost over all feasible sets.

## Input Format

- First line: integer `X` — number of cells.
- Next `X` lines (for cells `1..X`): first an integer boost, then an integer `m` (number of prerequisites), then `m` cell labels (the prerequisites).

## Output Format

Print a single integer — the maximum immune boost achievable.

## Constraints

- `1 ≤ X ≤ 10000`
- Total number of prerequisites across all cells `≤ 5000`
- `|boost| ≤ 10^6`

## Examples

### Example 1

**Input**
```
3
2 1 2
3 1 3
-1 0
```

**Output**
```
4
```

**Explanation:** Prerequisites force the chain `1 → 2 → 3`. Destroying all three cells yields `2 + 3 + (-1) = 4`.

### Example 2

**Input**
```
5
4 2 2 3
-3 0
2 1 5
-4 2 3 5
-5 1 2
```

**Output**
```
0
```

**Explanation:** Every non-empty feasible set has negative total boost, so the empty set is best.

### Example 3

**Input**
```
6
2 0
4 1 3
-5 2 4 5
-1 1 6
4 1 6
-2 1 1
```

**Output**
```
4
```

**Explanation:** Destroying cells `{1, 6, 5}` is feasible and yields `2 + (-2) + 4 = 4`.
