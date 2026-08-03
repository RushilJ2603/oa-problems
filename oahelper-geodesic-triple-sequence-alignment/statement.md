# Geodesic Triple Sequence Alignment

A navigation team records three trajectories on a one-dimensional manifold as integer sequences:

- `X = (X[0], …, X[n-1])`
- `Y = (Y[0], …, Y[m-1])`
- `Z = (Z[0], …, Z[k-1])`

You must align all three sequences into a single timeline by a sequence of **moves**. From state `(i, j, l)` (how many elements already consumed from `X`, `Y`, `Z`), exactly one move is chosen:

| Move | New state | Warp | Alignment cost |
|------|-----------|------|----------------|
| Triple | `(i+1,j+1,l+1)` | `0` | `\|X[i]-Y[j]\| + \|Y[j]-Z[l]\| + \|X[i]-Z[l]\|` |
| Double XY | `(i+1,j+1,l)` | `1` | `\|X[i]-Y[j]\|` |
| Double XZ | `(i+1,j,l+1)` | `1` | `\|X[i]-Z[l]\|` |
| Double YZ | `(i,j+1,l+1)` | `1` | `\|Y[j]-Z[l]\|` |
| Single X | `(i+1,j,l)` | `1` | `0` |
| Single Y | `(i,j+1,l)` | `1` | `0` |
| Single Z | `(i,j,l+1)` | `1` | `0` |

Empty moves are forbidden. The alignment must finish exactly at `(n, m, k)`. The cost of a move is **warp + alignment cost**. Find the **minimum total cost**.

## Input Format

- First line: three integers `n m k`.
- Second line: `n` integers `X[0] … X[n-1]` (omitted if `n = 0`).
- Third line: `m` integers `Y[0] … Y[m-1]` (omitted if `m = 0`).
- Fourth line: `k` integers `Z[0] … Z[k-1]` (omitted if `k = 0`).

When a length is zero, that sequence’s line may be empty (or absent); tokens are read whitespace-separated.

## Output Format

Print a single integer — the minimum alignment cost.

## Constraints

- `0 ≤ n, m, k ≤ 80`
- `-10^9 ≤ X[i], Y[j], Z[l] ≤ 10^9`

## Examples

### Example 1

**Input**

```
1 1 1
10
10
10
```

**Output**

```
0
```

**Explanation:** One triple move aligns three equal points at cost `0`.

### Example 2

**Input**

```
1 1 1
1
1
100
```

**Output**

```
2
```

**Explanation:** A triple move costs `|1-1|+|1-100|+|1-100| = 200`. Taking a double on `X,Y` (cost `0+1`) then a single on `Z` (cost `1`) totals `2`, which is optimal.

### Example 3

**Input**

```
2 2 1
10 20
10 100
10
```

**Output**

```
2
```
