# Minimum Refueling Stops

A car starts at position `0` and must reach a destination `target` units away. It begins with
`startFuel` units of fuel, and each unit of distance travelled uses exactly one unit of fuel.

Along the way there are `n` fuel stations. Station `i` is at position `pos_i` and, if you stop
there, adds `fuel_i` units to your tank (there is no cap on tank size). You may drive past a station
without stopping.

Return the **minimum number of stops** needed to reach `target`. If it cannot be reached no matter
how you stop, return `-1`. (Reaching a point with exactly `0` fuel still counts as reaching it.)

## Input

```
target startFuel
n
pos_1 fuel_1
pos_2 fuel_2
...
pos_n fuel_n
```

- Line 1: `target` and `startFuel`.
- Line 2: `n`, the number of stations.
- Each of the next `n` lines: a station `pos_i fuel_i`.

## Output

A single integer — the minimum number of refueling stops, or `-1` if the destination is unreachable.

## Constraints

- `1 ≤ target ≤ 10^9`
- `0 ≤ startFuel ≤ 10^9`
- `0 ≤ n ≤ 10^5`
- `1 ≤ pos_i < target`, and the positions are strictly increasing.
- `1 ≤ fuel_i ≤ 10^9`

## Example 1

**Input**
```
100 10
4
10 60
20 30
30 30
60 40
```
**Output**
```
2
```

Start with `10` fuel — enough to reach the station at `10`. Stop there (`+60` → `70` fuel), drive to
`60` and stop (`+40` → distance `110 ≥ 100`). Two stops reach the target; no single stop does.

## Example 2

**Input**
```
10 10
0
```
**Output**
```
0
```

The starting fuel already covers the whole distance, so no stops are needed.

## Example 3

**Input**
```
100 1
1
10 100
```
**Output**
```
-1
```

With only `1` fuel you cannot even reach the first station at position `10`, so the target is
unreachable.
