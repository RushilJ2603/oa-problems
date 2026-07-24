# Calculate Amount

Priya is buying a set of items at a stall. The stall owner discounts every item **after the
first** by the **lowest marked price seen among the items purchased before it**. No item's price
can be discounted below `0`, and the order of items may not be changed. The first item is never
discounted. Calculate the total amount Priya must pay.

Formally, for item `i` (0-indexed): `cost[0] = prices[0]`, and for `i >= 1`,
`cost[i] = max(0, prices[i] - min(prices[0..i-1]))`. Return the sum of all `cost[i]`.

## Input
- Line 1: integer `n` — the number of items.
- Next `n` lines: one integer per line, `prices[i]`.

## Output
A single integer: the total cost.

## Constraints
- `1 <= n <= 10^5`
- `0 <= prices[i] <= 10^9`

## Examples
```
Input:
4
2
5
1
4
Output:
8
```
```
Input:
4
4
9
2
3
Output:
10
```
