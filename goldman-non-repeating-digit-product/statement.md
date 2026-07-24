# Non-repeating Digit in Product

Given a number `x` and a range `[y, z]`, count how many numbers `n` in that range (inclusive) have
the property that the product `n * x` contains **none** of the digits that appear in `n`.

## Input
```
x
y
z
```
(three integers, one per line)

## Output
A single integer — the count of valid `n` in `[y, z]`.

## Constraints
- All inputs are integers below `10^5`.
- `y ≤ z`.

## Example
Input:
```
2
10
15
```
Output:
```
4
```
For `x = 2`: `n = 11` → `22` (no shared digit, valid), `13 → 26` (valid), `14 → 28` (valid),
`15 → 30` (valid). `10 → 20` (shares `0`) and `12 → 24` (shares `2`) are invalid. Count = 4.
