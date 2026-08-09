# Balance the Two Baskets

You are given two arrays `a` and `b`, both of length `n`, holding positive integers, and an integer
`k`.

Choose **exactly `k` distinct indices**. The same set of indices is used for both arrays:

- `totA` = the sum of `a[i]` over the chosen indices,
- `totB` = the sum of `b[i]` over the chosen indices.

The value of a choice is `min(totA, totB)`.

Return the **largest** value achievable over all ways of choosing `k` indices.

## Input

- The first line contains two integers `n` and `k`.
- The second line contains `n` integers `a[0] … a[n-1]`.
- The third line contains `n` integers `b[0] … b[n-1]`.

## Output

A single integer — the maximum possible `min(totA, totB)`.

## Constraints

- `1 <= n <= 50`
- `1 <= k <= n`
- `1 <= a[i], b[i] <= 100`

## Example 1

**Input**
```
4 2
10 1 6 5
1 10 6 5
```

**Output**
```
11
```

**Explanation:** choosing indices `2` and `3` gives `totA = 6 + 5 = 11` and `totB = 6 + 5 = 11`, so
the value is `11`.

Choosing indices `0` and `1` gives the larger *total* (`totA = 11`, `totB = 11` as well — also 11),
but choosing indices `0` and `2` gives `totA = 16`, `totB = 7`, worth only `7`. The biggest pile is
not the answer; the **balanced** one is.

## Example 2

**Input**
```
5 3
5 1 1 1 1
1 5 5 5 5
```

**Output**
```
7
```

**Explanation:** taking index `0` plus any two others gives `totA = 5 + 1 + 1 = 7` and
`totB = 1 + 5 + 5 = 11`, worth `7`. Taking three of the indices `1..4` gives `totA = 3`,
`totB = 15`, worth only `3`. Index `0` is the only large contributor to `a`, so it has to be in the
set even though it is the weakest contributor to `b`.
