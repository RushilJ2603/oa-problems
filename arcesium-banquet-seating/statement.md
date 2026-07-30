# Banquet Seating

Somyak is arranging a banquet with `m` chairs placed in a **circle** (chairs `0, 1, …, m-1`, with
chair `m-1` next to chair `0`). There are `n` guests; guest `i` has a personal-space demand
`demand[i]`.

Each guest sits on a distinct chair. Guest `i` insists that, looking **clockwise** to the nearest
other guest and **counter-clockwise** to the nearest other guest, there are at least `demand[i]`
**empty chairs** in each of those two directions. In other words, on both sides of guest `i` there
must be a run of at least `demand[i]` empty chairs before the next occupied chair.

Determine whether all `n` guests can be seated. Print `YES` if a valid seating exists, otherwise `NO`.

## Input

```
m n
demand_1 demand_2 … demand_n
```

- Line 1: `m` (number of chairs) and `n` (number of guests).
- Line 2: the `n` demands. (If `n = 0`, this line is empty or absent.)

## Output

`YES` if everyone can be seated respecting all demands, otherwise `NO`.

## Constraints

- `1 ≤ m ≤ 10^9`
- `0 ≤ n ≤ 10^5`
- `1 ≤ demand[i] ≤ 10^9`

## Example 1

**Input**
```
16 3
2 3 5
```
**Output**
```
YES
```

Seat the guests in demand order around the circle. Between the guest with demand `2` and the one with
demand `3` we need `3` empty chairs; between `3` and `5` we need `5`; and between `5` and `2` (wrapping
around) we need `5`. That is `3 + 5 + 5 = 13` empty chairs plus the `3` occupied chairs = `16`, which
fits exactly.

## Example 2

**Input**
```
15 3
2 3 5
```
**Output**
```
NO
```

The same demands need at least `16` chairs (from Example 1), but only `15` are available.

## Example 3

**Input**
```
10 1
9
```
**Output**
```
YES
```

A single guest needs `9` empty chairs on each side — but both sides wrap around to the same run of
`m - 1 = 9` empty chairs, which is exactly enough.
