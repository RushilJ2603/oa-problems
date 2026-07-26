# Drone Delivery with Battery Swap Stations

An autonomous delivery drone must fly from a depot to a customer over a dense urban grid. Its compact battery cannot always last the full trip. Automated battery-swap kiosks sit on rooftops: landing on a kiosk lets the drone instantly install a fully charged battery, but only if it still has an unused swap voucher. Vouchers are scarce and shared for the whole delivery.

Find the **minimum number of moves** to fly from the depot `(sr, sc)` to the customer `(er, ec)`, given battery capacity `B`, a list of swap-kiosk cells, and a budget of `K` swap vouchers. Report `-1` if no feasible delivery exists.

## Rules

- The grid is `rows × cols`. Cell value `0` is open airspace; `1` is a no-fly building.
- Each move is one step to an adjacent open cell (up, down, left, right). Every move costs exactly one unit of battery.
- The drone starts at `(sr, sc)` with a **full** battery of `B` units (being at the start costs nothing).
- The drone may only move when its remaining battery is at least `1`. After a move, battery decreases by `1`.
- If the drone is currently on a kiosk cell, has at least one unused voucher, and battery is strictly less than `B`, it may **swap**: battery becomes `B` and one voucher is consumed. A swap costs **zero** moves.
- Reaching `(er, ec)` with any non-negative battery is success (including battery `0` after the arrival move).
- If start and end are the same cell, the answer is `0`.

## Input Format

```
rows cols
grid_row_0
grid_row_1
...
grid_row_{rows-1}
sr sc
er ec
B
M
station_0_r station_0_c
...
station_{M-1}_r station_{M-1}_c
K
```

- Line 1: `rows cols`
- Next `rows` lines: `cols` integers each (`0` or `1`)
- Next line: start coordinates `sr sc` (0-indexed)
- Next line: end coordinates `er ec` (0-indexed)
- Next line: battery capacity `B`
- Next line: number of kiosks `M`
- Next `M` lines: kiosk coordinates
- Last line: voucher budget `K`

## Output Format

A single integer: the minimum number of moves, or `-1` if impossible.

## Constraints

- `1 ≤ rows, cols ≤ 50`
- `1 ≤ B ≤ 50`
- `0 ≤ K ≤ 10`
- `0 ≤ M ≤ rows × cols`
- `grid[i][j] ∈ {0, 1}`
- Start and end cells are open; every kiosk is on an open cell; kiosks are pairwise distinct

## Examples

### Example 1

**Input**
```
3 4
0 0 0 0
0 1 1 0
0 0 0 0
0 0
2 3
4
2
1 0
0 3
1
```

**Output**
```
5
```

**Explanation**

One optimal route swaps at `(1,0)`: `(0,0) → (1,0)` [swap] `→ (2,0) → (2,1) → (2,2) → (2,3)` — 5 moves.

### Example 2

**Input**
```
1 11
0 0 0 0 0 0 0 0 0 0 0
0 0
0 10
4
2
0 4
0 8
2
```

**Output**
```
10
```

**Explanation**

Distance 10 with `B = 4` needs both vouchers at the two kiosks along the corridor.

### Example 3

**Input**
```
3 3
0 0 0
1 1 1
0 0 0
0 0
2 0
5
0
0
```

**Output**
```
-1
```

**Explanation**

A solid wall of buildings blocks every path from start to end.
