# Unstable Tasks

You are given three arrays of the same length `n`: `task` (names), `timestamp`, and `limit`. Each
index `i` records that task `task[i]` had limit value `limit[i]` at time `timestamp[i]`.

For each task, order its records by **increasing timestamp** and read off the resulting sequence
of limit values. A task is **unstable** if that sequence contains **at least one strict increase
and at least one strict decrease** (in any order). Return the number of unstable tasks.

All timestamps are distinct.

## Input
- Line 1: integer `n`.
- Line 2: `n` task names (lowercase tokens, space-separated).
- Line 3: `n` integers — `timestamp[i]`.
- Line 4: `n` integers — `limit[i]`.

## Output
A single integer: the number of unstable tasks.

## Constraints
- `1 <= n <= 10^5`
- timestamps are distinct; `0 <= timestamp[i], limit[i] <= 10^9`

## Examples
```
Input:
3
a a a
1 2 3
10 50 20
Output:
1
```
Task `a` in time order is [10, 50, 20]: a rise (10->50) and a drop (50->20) -> unstable.
```
Input:
4
webapp cache webapp cache
10 20 5 40
10 20 50 20
Output:
0
```
