# Final Price

A resale marketplace lists `n` items for sale in a fixed row. Scanning from the left, every item
is sold at its listed price **reduced by the price of the nearest item to its right whose price
is less than or equal to its own**; if no such item exists, the item is sold at its listed price
(it receives no discount).

Print the **total** of all final prices, and then the **0-indexed positions** of the items that
received **no discount**, in increasing order.

## Input
- Line 1: integer `n`.
- Next `n` lines: one integer per line, `price[i]`.

## Output
- Line 1: the sum of all final prices.
- Line 2: the 0-indexed positions (space-separated, increasing) of items sold with no discount.

## Constraints
- `1 <= n <= 10^5`
- `1 <= price[i] <= 10^9`

## Examples
```
Input:
6
5
1
3
4
6
2
Output:
14
1 5
```
```
Input:
5
1
3
3
2
5
Output:
9
0 3 4
```
