# Game of Book Cricket

In Book Cricket you repeatedly open a book to a random page and score the **last digit of the page
number**. With a 10-page book the possible last digits on even pages are `2, 4, 6, 8, 0`. Scoring a
`2`, `4`, or `6` adds to your total; opening a page ending in `0` or `8` means you are **out** and
your turn ends.

Given a target total `totalScore = N`, count the number of ways to reach **exactly** `N` while
staying **not out** — i.e. the number of ordered sequences of scores from `{2, 4, 6}` that sum to `N`.

## Input
A single integer `N` (the total score).

## Output
A single integer — the number of ways to reach `N` using an ordered sequence of `{2, 4, 6}`.

## Constraints
- `0 ≤ N`, and `N` is small enough that the answer fits in a 64-bit integer.

## Example
Input:
```
6
```
Output:
```
4
```
`6` can be made as `[2,2,2]`, `[2,4]`, `[4,2]`, `[6]` — 4 ordered ways.
