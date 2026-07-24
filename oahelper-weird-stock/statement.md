# Weird Stock

Suppandi will buy a share of company X once its price reaches exactly **m**. The price starts at
**n** on day 0. At the end of **each** day the price either **decreases by 1** or **doubles**.
Print the minimum number of days after which the price can be exactly `m`.

## Input
- Line 1: integer `n` (initial price).
- Line 2: integer `m` (target price).

## Output
A single integer: the minimum number of days to reach exactly `m`.

## Constraints
- `1 <= n <= 10^4`, `1 <= m <= 10^4`

## Example
```
Input:
3
4
Output:
2
```
`3 -> 2 (-1) -> 4 (double)` takes 2 days.
