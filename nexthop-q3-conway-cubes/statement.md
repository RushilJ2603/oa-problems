# Conway Cubes

Space is an **infinite three-dimensional grid**. Every integer coordinate `(x, y, z)` holds one cube,
and each cube is either **active** (`#`) or **inactive** (`.`). All but a finite number of cubes are
inactive.

Two cubes are **neighbours** if their coordinates differ by at most `1` in each of `x`, `y` and `z`
and they are not the same cube — so every cube has exactly **26** neighbours.

During a **cycle**, *all* cubes update **simultaneously**, each one deciding from the state its
neighbours had *before* the cycle began:

- an **active** cube stays active if **exactly 2 or exactly 3** of its 26 neighbours are active;
  otherwise it becomes inactive;
- an **inactive** cube becomes active if **exactly 3** of its 26 neighbours are active; otherwise it
  stays inactive.

You are given a two-dimensional starting slice: the state of the plane `z = 0`. Every cube outside
that slice — including every cube at `z != 0` — starts inactive. The slice is only the *starting*
region; cubes anywhere in the infinite grid may become active later.

Run exactly `T` cycles and report how many cubes are active.

## Input

- The first line contains two integers `R` and `T` — the number of rows in the starting slice, and
  the number of cycles to run.
- Each of the next `R` lines contains `C` characters, each `#` (active) or `.` (inactive),
  describing the plane `z = 0`. Every row has the same length `C`.

## Output

A single integer — the number of active cubes after `T` cycles.

## Constraints

- `1 <= R, C <= 25`
- `0 <= T <= 12`

## Example 1

**Input**
```
3 6
.#.
..#
###
```

**Output**
```
112
```

**Explanation:** the starting slice has 5 active cubes, all at `z = 0`. After the first cycle the
active region already occupies the planes `z = -1`, `z = 0` and `z = 1`; after six cycles it spans
`z = -6 .. 6` and contains 112 active cubes in total.

## Example 2

**Input**
```
3 0
.#.
..#
###
```

**Output**
```
5
```

**Explanation:** with `T = 0` no cycle runs, so the answer is simply the number of `#` in the
starting slice.

## Example 3

**Input**
```
1 1
#
```

**Output**
```
0
```

**Explanation:** a lone active cube has `0` active neighbours, which is neither `2` nor `3`, so it
becomes inactive. No inactive cube has `3` active neighbours, so nothing switches on.
