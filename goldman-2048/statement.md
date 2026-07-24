# 2048

In the game **2048**, a `4×4` grid holds cells that are either empty (`0`) or a value `2^k`
(`1 ≤ k ≤ 11`). Pressing a direction — **U**p, **D**own, **L**eft, **R**ight — slides every cell as
far as possible that way. During the slide, if two cells **adjacent in the direction of movement**
have the same value, they **merge** into their sum (each cell participates in at most one merge per
press). For example, in a row `[4, 4, 0, 0]` pressing **R** gives `[0, 0, 0, 8]`; `[16, 16, 0, 32]`
pressing R gives `[0, 0, 32, 32]`; `[2, 4, ...]` stays `2 4` since the values differ.

The **score** gained on a press is the sum of all the merged values produced by that press. The
reported score is **cumulative** across all presses so far.

Given the initial grid and a sequence of `N` presses, print the cumulative score after **each**
press.

## Input
```
4 lines, each with 4 space-separated values   (the grid; 0 or a power of two)
N                                             (number of presses)
N lines, each a single key: one of U u D d L l R r
```

## Output
`N` lines: the cumulative score after each press, in order.

## Constraints
- Grid is always `4×4`; cell values are `0` or `2^k` with `1 ≤ k ≤ 11`.
- A key is `U/u`, `D/d`, `L/l`, or `R/r`.

## Example 1
Input:
```
16 256 256 512
4 0 0 32
64 0 0 8
2 2 1024 2
2
R
d
```
Output:
```
516
516
```
Pressing **R** merges `256+256=512` (row 0) and `2+2=4` (row 3) → score `516`. Pressing **d** causes
no merges, so the cumulative score stays `516`.

## Example 2
Input:
```
2 4 8 16
2 4 2 2
2 2 4 4
8 64 32 0
3
L
U
U
```
Output:
```
16
28
52
```
