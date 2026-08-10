# Calibration Values

You are given a list of `n` **queries**. Each query is a string made of lowercase English letters
and digits, such as `two1nine`, `1362` or `7sixfive`.

Inside a query, a **digit** is either

- a digit **character** `0`–`9`, or
- a digit **spelled out** as one of the nine words

  `one`, `two`, `three`, `four`, `five`, `six`, `seven`, `eight`, `nine`

  (there is no spelled form of zero — `0` only ever appears as the character `0`).

The **calibration value** of a query is the two-digit number formed by its **first** digit and its
**last** digit, reading left to right:

```
value = 10 * (first digit) + (last digit)
```

If a query contains exactly one digit, that digit is both the first and the last, so `abc4def` has
value `44`.

Report the **sum** of the calibration values of all `n` queries.

## Digits are found by position, not consumed

A spelled digit is any of the nine words occurring as a substring. Two spelled digits may **share
letters** — finding one does not remove its letters from the string. In `eightwothree` the digits
are `eight` at index 0, `two` at index 4 and `three` at index 7 (the `t` at index 4 belongs to both
`eight` and `two`), so its digits are `8, 2, 3` and its value is `83`.

## Input

- The first line contains a single integer `n` — the number of queries.
- Each of the next `n` lines contains one query.

## Output

A single integer — the sum of the `n` calibration values.

## Constraints

- `1 <= n <= 2 * 10^5`
- Each query is `1` to `50` characters, each a lowercase English letter (`a`–`z`) or a digit (`0`–`9`).
- The total length of all queries is at most `10^6`.
- Every query contains at least one digit.

## Example 1

**Input**
```
3
two1nine
1362
7sixfive
```

**Output**
```
116
```

**Explanation:**

| query | digits, in order | value |
|---|---|---|
| `two1nine` | `2`, `1`, `9` | `29` |
| `1362` | `1`, `3`, `6`, `2` | `12` |
| `7sixfive` | `7`, `6`, `5` | `75` |

`29 + 12 + 75 = 116`.

## Example 2

**Input**
```
2
eightwothree
oneight
```

**Output**
```
101
```

**Explanation:** `eightwothree` gives `8, 2, 3` → `83`, and `oneight` gives `1, 8` → `18`
(the `e` at index 2 ends `one` and starts `eight`). `83 + 18 = 101`.

## Example 3

**Input**
```
1
abc4def
```

**Output**
```
44
```

**Explanation:** the only digit is `4`, so it is both the first and the last.
