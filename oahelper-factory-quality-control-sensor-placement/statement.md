# Factory Quality Control Sensor Placement

A manufacturing facility has a production line with **N** stations arranged in sequence, indexed from `0` to `N-1`. Each station has a quality sensor reporting a non-negative score `A[i]`.

You must place monitoring segments along the line. Segments are **not** formed by enumerating every pair of stations. Instead, they are produced by the following left-to-right process for a chosen quality-drop threshold **D**.

## Segment formation process (for a fixed D)

Maintain a double-ended queue of candidate left-endpoint indices. The queue always stores indices in **strictly decreasing** order of score.

Scan stations `j = 0, 1, ..., N-1`. At each station `j`:

1. **Eviction.** While the queue is non-empty and the score at the back index is `≤ A[j]`, permanently discard that back index.
2. **Registration.** Push `j` onto the back of the queue.
3. **Matching.** While the queue is non-empty and `A[front] − A[j] ≥ D`, form one segment by matching the front index with `j`, permanently remove the front, and count `+1`. Repeat until the condition fails or the queue is empty.

Important consequences of this process:

- Each left endpoint is used at most once (removed when matched or evicted).
- Matching always prefers the oldest remaining candidate (the front).
- Eviction enforces that any formed segment `(i, j)` satisfies `A[i] > A[k]` for every `k` in `(i, j)`.

## Objective

Find the **maximum** integer **D** such that the process above forms **at least K** segments.

It is guaranteed that if some value of `D` yields at least `K` segments, every smaller non-negative value also does. Search over `D` in `[0, 10^9]`. If even `D = 0` cannot form `K` segments, the answer is `0`.

## Input format

- Line 1: two integers `N` and `K`
- Line 2: `N` integers `A[0] A[1] ... A[N-1]`

## Output format

Print a single integer: the maximum achievable `D`.

## Constraints

- `1 ≤ N ≤ 10^5`
- `1 ≤ K ≤ N·(N−1)/2`
- `0 ≤ A[i] ≤ 10^9`

## Examples

### Example 1

**Input**
```
6 3
50 45 55 30 40 20
```

**Output**
```
5
```

**Explanation**

For `D = 5` the process forms segments `(0,1)`, `(2,3)`, and `(4,5)` — three segments, which meets `K = 3`.

For `D = 6` only two segments form, so `6` is too large. The maximum valid `D` is therefore `5`.

### Example 2

**Input**
```
2 1
20 10
```

**Output**
```
10
```

**Explanation**

The only possible match is indices `(0,1)` with drop `20 − 10 = 10`. That is the largest `D` that still forms one segment.
