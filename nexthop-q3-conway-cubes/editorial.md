# Conway Cubes

This is Conway's Game of Life with one dimension added. The rules are three lines long and the
implementation is a triple loop — which is exactly why it is asked. Everything that goes wrong here
goes wrong in the *setup*, not the logic.

## Trap 1: the grid is infinite, and your array is not

The starting slice is `R × C`, but the answer is not confined to it. In example 1 a `3 × 3` slice
grows to 112 active cubes spread over 13 planes. A solution that allocates an `R × C × (2T+1)` box
and clamps at the edges silently loses everything that walks out of the original footprint, and it
still returns a plausible-looking number.

The bound you need is one line of reasoning: **activity spreads by at most one cell per cycle**,
because a cube can only switch on if a *neighbour* is already active. So after `T` cycles nothing
further than `T` from the starting slice can be active, and

```
X = R + 2T      Y = C + 2T      Z = 2T + 1
```

is not a guess — it is exact. With that margin, treating an out-of-range neighbour as inactive is
*correct*, because every cube out there is provably inactive. `edge/08` and `edge/09` (a single row
and a single column) are the shapes where the padding dominates the original grid.

The alternative, and the one worth reaching for under time pressure, is to keep **no grid at all**:

```python
active = {(0, i, j) for ... if slice[i][j] == '#'}
for _ in range(T):
    votes = Counter()
    for cell in active:
        for d in OFFSETS:          # the 26 neighbours
            votes[cell + d] += 1
    active = {p for p, c in votes.items() if c == 3 or (c == 2 and p in active)}
```

Each active cube pours a vote into its 26 neighbours; a cube's neighbour count is its tally. Cubes
with no active neighbour never get a tally and never get represented, so the infinite grid costs
nothing. There is no margin to get wrong. This is what `brute.py` does.

## Trap 2: updating in place

Every cube must decide from the state *before* the cycle. Writing the new value into the same array
you are reading means a cube at `(z, x, y)` sees already-updated neighbours behind it and old ones
ahead of it — the automaton stops being well-defined and the answer depends on your loop order.
Write into a second buffer and swap. In the set formulation this is free: the Counter is built from
the old set and the new set is only assigned at the end.

## Trap 3: counting the cube itself

The `dz == dx == dy == 0` case is not a neighbour. Skipping it inside the innermost loop is the
whole fix, but forgetting it inflates every *active* cube's count by exactly one — so the survival
rule silently becomes "3 or 4" and the answer holds up on small inputs before drifting badly.

## The rule, once the setup is right

```
active   cube -> stays active  iff  neighbours == 2 or neighbours == 3
inactive cube -> turns active  iff  neighbours == 3
```

Note the asymmetry: `2` keeps a cube alive but never wakes one up. Writing `>= 2 && <= 3` for both
branches is a common slip and turns example 1 from `112` into something much larger.

`edge/06` is a bare `###`. In two dimensions that is a blinker and it oscillates forever inside its
own row; in three dimensions the cubes directly above and below the centre each see 3 neighbours and
switch on during the first cycle, so it immediately becomes a genuinely 3-D object. If your answer
for it does not use the `z` axis, the `z` axis is not wired up.

## Complexity

With the padded array, `O(T · (R+2T)(C+2T)(2T+1) · 27)`. At the limits (`R = C = 25`, `T = 12`) that
is about 19 million neighbour reads — comfortably inside the limit. The set-based version is
`O(T · 26 · |active|)` and is faster on sparse inputs, slower only when the grid is nearly solid.
