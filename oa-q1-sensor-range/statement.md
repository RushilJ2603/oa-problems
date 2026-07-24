# Sensor Range Overlap

There are `n` sensors on a number line. Sensor `i` sits at position `p[i]` and has range `r[i]`, so
it covers the interval `[p[i] − r[i], p[i] + r[i]]`. Two sensors **overlap** if their intervals
share at least one point; equivalently, sensors `i` and `j` overlap when

```
r[i] + r[j] ≥ |p[i] − p[j]|.
```

For **each** sensor, output the **minimum amount you must add to its range** so that it overlaps at
least one other sensor.

> **Interpretation (important).** Each sensor's required increment is computed **independently**,
> against the other sensors at their **original** ranges. That is, for sensor `i` the answer is the
> smallest `d ≥ 0` such that `(r[i] + d) + r[j] ≥ |p[i] − p[j]|` for some `j ≠ i`. This yields
> `d[i] = max(0, min_{j ≠ i} (|p[i] − p[j]| − r[i] − r[j]))`. (Because every sensor only ever grows,
> applying all these increments together still leaves every sensor overlapping at least one other.)

## Input
```
n
p[0] p[1] … p[n-1]        (positions)
r[0] r[1] … r[n-1]        (ranges)
```

## Output
`n` integers (space-separated): the minimum range increment for each sensor, in the original order.

## Constraints
- `2 ≤ n ≤ 100000`
- `-10^9 ≤ p[i] ≤ 10^9`
- `0 ≤ r[i] ≤ 10^9`

## Example 1
Input:
```
3
0 10 25
1 1 1
```
Output:
```
8 8 13
```
Sensor 0 needs `+8` to reach sensor 1; sensor 1's nearest is sensor 0, also `+8`; sensor 2 needs
`+13` to reach sensor 1.

## Example 2
Input:
```
2
0 3
2 2
```
Output:
```
0 0
```
They already overlap (`2 + 2 ≥ 3`), so no increment is needed.
