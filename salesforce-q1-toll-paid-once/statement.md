# The Toll You Only Pay Once

A road network has `n` junctions and `m` two-way roads. Road `i` joins junctions `u` and `v` and
charges a toll of `w`.

You must drive from junction `a` to junction `c`, and then from junction `c` to junction `b`.

The tolls work like a season ticket bought per road: **you pay a road's toll the first time you drive
along it, and every later drive along that same road is free** — in either direction, any number of
times.

Return the minimum total toll you can pay to complete both legs of the journey.

## Input

- The first line contains two integers `n` and `m` — the number of junctions and the number of roads.
- Each of the next `m` lines contains three integers `u`, `v`, `w` — a two-way road between `u` and
  `v` with toll `w`.
- The last line contains three integers `a`, `b`, `c` — the start, the final destination, and the
  junction that must be visited in between.

Junctions are numbered `1` to `n`. There may be more than one road between the same pair of
junctions.

## Output

A single integer — the minimum total toll. Print `-1` if the journey is impossible.

## Constraints

- `1 <= n <= 10^5`
- `0 <= m <= 2 * 10^5`
- `1 <= u, v <= n`, `u != v`
- `1 <= w <= 10^9`
- `1 <= a, b, c <= n` (they are not required to be distinct)

The answer can exceed the range of a 32-bit integer.

## Example 1

**Input**
```
4 3
1 2 1
2 3 1
2 4 1
1 4 3
```

**Output**
```
3
```

**Explanation:** `a = 1`, `b = 4`, `c = 3`. Drive `1 → 2` (pay 1) and `2 → 3` (pay 1); you have
reached `c` having paid 2. Now drive back `3 → 2` — that road is already paid for, so it costs
nothing — and then `2 → 4` (pay 1). Total **3**.

Paying for two separate journeys would cost `(1 + 1) + (1 + 1) = 4`. The saving is the road `2 → 3`,
which the return leg rides for free.

## Example 2

**Input**
```
5 2
1 2 4
4 5 6
1 5 2
```

**Output**
```
-1
```

**Explanation:** `a = 1`, `b = 5`, `c = 2`. You can reach `c = 2` from `a = 1`, but junction `5` is
in a different part of the network, so the second leg can never be completed.
