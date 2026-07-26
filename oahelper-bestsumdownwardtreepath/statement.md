# Best Sum Downward Tree Path

A company org-chart is a tree of `n` people numbered `0 .. n-1`, rooted at node `0`. Person `i` has an associated score `values[i]` (scores may be negative).

A **downward path** is a sequence of nodes `u_1, u_2, ..., u_k` (`k ≥ 1`) where each `u_i` is a child of `u_{i-1}` in the rooted tree. In other words, you may only walk from a person to one of their direct reports, never sideways or upward.

Find the maximum sum of scores over all downward paths. A path of a single node is allowed, so the answer is always at least the largest single-node score.

## Input Format

- Line 1: integer `n`
- Next `n` lines: `parent[i]` for `i = 0 .. n-1`. `parent[0] = -1` marks the root; for every other node, `0 ≤ parent[i] ≤ n-1`.
- Next `n` lines: `values[i]` for `i = 0 .. n-1`.

## Output Format

Print a single integer — the maximum downward-path sum.

## Constraints

- `1 ≤ n ≤ 10^5`
- `parent[0] = -1`
- `0 ≤ parent[i] ≤ n-1` for `1 ≤ i ≤ n-1`
- `-1000 ≤ values[i] ≤ 1000`
- The parent array describes a valid tree rooted at 0

## Examples

### Example 1

**Input**
```
5
-1
0
1
2
0
-2
10
10
-3
10
```

**Output**
```
20
```

**Explanation**

The tree edges are `0→1→2→3` and `0→4`. The best downward path is `1 → 2` with sum `10 + 10 = 20`. Note that a path that goes "across" siblings is not allowed.

### Example 2

**Input**
```
5
-1
0
1
2
0
5
7
-10
4
15
```

**Output**
```
20
```

**Explanation**

Path `0 → 4` sums to `5 + 15 = 20`, which is best. Path `0 → 1 → 2 → 3` sums only to 6.
