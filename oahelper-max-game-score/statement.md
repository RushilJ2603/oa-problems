# Max Game Score

A player starts at cell `0` (value `0`) of a row of `n` cells `0..n-1`. Each move goes either **+1
cell** to the right, or **+p cells** to the right where `p` is a prime ending in the digit 3 (3,
13, 23, 43, ...). Moving past the last cell is not allowed. Landing on a cell adds its value to the
score; the game ends on cell `n-1`. Print the maximum achievable score.

## Input
- Line 1: integer `n`.
- Line 2: `n` space-separated integers (cell values; `cell[0] = 0`).

## Output
A single integer: the maximum score on reaching cell `n-1`.

## Constraints
- `1 <= n <= 2*10^4`
- `-10^9 <= cell[i] <= 10^9`

## Example
```
Input:
4
0 -10 100 -20
Output:
70
```
0 -> 2 (+1,+1, score 90) -> 3 (+? use +3 from cell 0 skips 90; best is +1 to 3): 100 + (-20) = 70.
