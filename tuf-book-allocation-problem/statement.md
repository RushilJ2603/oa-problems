# Book Allocation Problem

`nums[i]` is the number of pages in book `i`. Allocate all books to `m` students so each student gets a contiguous block of at least one book. Minimise the maximum number of pages any student reads; print that minimum. If `m > n`, print `-1`.

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
