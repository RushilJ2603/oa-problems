# Maximum Campaign Score

You are given the demand for a product over `n` consecutive days: `a[0], a[1], …, a[n-1]`, where
`a[i]` is the demand on day `i`.

The marketing team wants to launch exactly `k` promotional **campaigns**. A campaign runs over a
contiguous range of days `[i, j]` with `0 ≤ i ≤ j ≤ n-1` (both endpoints included), and its **score**
is the spread of demand during that window:

```
score(i, j) = max(a[i..j]) − min(a[i..j])
```

The **total score** is the sum of the scores of all `k` campaigns. Campaigns may overlap or be nested,
but **no two campaigns may cover the exact same range** `[i, j]` — each campaign must be a distinct
window.

Return the **maximum total score** achievable with `k` campaigns.

## Input

```
n k
a_1 a_2 … a_n
```

- Line 1: `n` (number of days) and `k` (number of campaigns to launch).
- Line 2: the `n` demand values.

## Output

A single integer — the maximum total score. (It can exceed the range of a 32-bit integer, so use a
64-bit type.)

## Constraints

- `1 ≤ n ≤ 2000`
- `1 ≤ k ≤ n·(n+1)/2` (there are exactly `n·(n+1)/2` distinct windows, so `k` never exceeds that)
- `0 ≤ a[i] ≤ 10^9`

## Example 1

**Input**
```
5 4
1 2 5 3 4
```
**Output**
```
15
```

The three windows `[0,2]`, `[0,3]`, `[0,4]` each contain both the maximum demand `5` and the minimum
`1`, so each scores `5 − 1 = 4`. The best remaining window (e.g. `[1,2]` = `{2,5}`) scores `5 − 2 = 3`.
Together: `4 + 4 + 4 + 3 = 15`. No choice of four distinct windows beats this.

## Example 2

**Input**
```
4 1
7 7 7 7
```
**Output**
```
0
```

Every window has equal demand, so every score is `0`.

## Example 3

**Input**
```
3 6
1 3 2
```
**Output**
```
5
```

With `k = 6` we must take **all** six distinct windows. Their scores are `[0,0]=0`, `[1,1]=0`,
`[2,2]=0`, `[0,1]={1,3}→2`, `[1,2]={3,2}→1`, `[0,2]={1,3,2}→2`. The total is `0+0+0+2+1+2 = 5`.
