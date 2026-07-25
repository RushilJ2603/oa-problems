# Book Allocation Problem

`nums[i]` is the number of pages in book `i`, given in a fixed row. Allocate the books to `m`
students so that **each student receives a _contiguous_ block of books** — i.e. student 1 gets
`nums[0..a]`, student 2 gets `nums[a+1..b]`, and so on, with **no gaps and no reordering**. Every
student must get at least one book. Among all such contiguous allocations, minimise the **maximum**
number of pages assigned to any single student, and print that minimum. If `m > n`, print `-1`.

> The blocks must be contiguous: you may only choose *where to cut* the row into `m` consecutive
> pieces. You may **not** hand-pick arbitrary books for a student. (For `[12, 34, 67, 90]` with
> `m = 2`, the split `[12, 34, 67] | [90]` gives max `113`; picking `{12, 90}` and `{34, 67}` is
> **not** allowed even though it would balance better.)

## Input
- Line 1: `n` `m`.
- Line 2: `n` integers `nums[i]`.

## Output
A single integer: the minimised maximum pages, or `-1` if impossible.

## Constraints
- `1 <= n, m <= 10^4`
- `1 <= nums[i] <= 10^5`

## Examples
```
Input:
4 2
12 34 67 90
Output:
113
```
Best cut into 2 consecutive blocks: `[12, 34, 67]` (113 pages) and `[90]` (90 pages); the maximum
is `113`, which is the smallest achievable.

```
Input:
5 3
25 46 48 90 34
Output:
119
```
Best cut into 3 consecutive blocks: `[25, 46, 48]` (119) | `[90]` (90) | `[34]` (34); the maximum is
`119`. No other set of cuts does better. (A non-contiguous grouping could reach 90, but that is not
permitted.)
