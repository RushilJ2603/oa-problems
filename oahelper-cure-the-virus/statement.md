# Cure the Virus

A super virus is spreading, and researchers believe the best path to a cure is to carefully destroy selected cells so the immune system gains as much strength as possible.

Destroying a cell requires first destroying every cell it depends on (its **prerequisites**). Some cells are viral: destroying them gives a positive boost. Others are human: destroying them gives a negative boost. You would only destroy a costly human cell when it unlocks enough viral boost to compensate.

The dependency structure is acyclic: it is impossible for a cell to indirectly require itself.

A set of cells `C` is **feasible** if whenever `i` belongs to `C`, every prerequisite of `i` also belongs to `C`. The boost of `C` is the sum of the boost values of its members. The empty set is feasible, so the answer is never negative.

Find a feasible set with maximum total boost.

## Input Format

- The first line contains an integer `X` — the number of cells (labelled `1` to `X`).
- Each of the next `X` lines describes one cell in order from `1` to `X`: the first number is its boost, the second is the number of prerequisites `k`, followed by `k` prerequisite labels.

## Output Format

Print a single integer — the maximum boost of any feasible set.

## Constraints

- `1 ≤ X ≤ 10000`
- The total number of prerequisite edges across all cells is at most `5000`
- `|boost| ≤ 10^6` for every cell

## Examples

### Example 1

Input:
```
3
2 1 2
3 1 3
-1 0
```

Output:
```
4
```

Explanation: Cell 1 requires 2, and 2 requires 3. Destroying all three cells yields `2 + 3 − 1 = 4`.

### Example 2

Input:
```
5
4 2 2 3
-3 0
2 1 5
-4 2 3 5
-5 1 2
```

Output:
```
0
```

Explanation: Every non-empty feasible set has negative boost, so the empty set is best.

### Example 3

Input:
```
6
2 0
4 1 3
-5 2 4 5
-1 1 6
4 1 6
-2 1 1
```

Output:
```
4
```

Explanation: Destroying cells `{1, 5, 6}` gives boost `2 + 4 + (−2) = 4`. Taking cell 2 is not worth paying for cell 3.
