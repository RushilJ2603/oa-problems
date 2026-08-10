# Minimum Flips to Make a OR b Equal to c

You are given three non-negative integers `a`, `b` and `c`.

In one **operation** you pick a single bit of `a` **or** a single bit of `b` and flip it — a `0`
becomes a `1`, or a `1` becomes a `0`. `c` is never modified.

Return the **minimum number of operations** needed so that afterwards

```
(a | b) == c
```

where `|` is the bitwise OR.

## Input

A single line with three space-separated integers `a`, `b` and `c`.

## Output

A single integer — the minimum number of flips.

## Constraints

- `0 <= a, b, c < 2^60`

Note that `2^60 - 1 = 1152921504606846975`, so the inputs do **not** fit in a 32-bit integer.

## Example 1

**Input**
```
2 6 5
```

**Output**
```
3
```

**Explanation:** in binary `a = 010`, `b = 110`, `c = 101`.

| bit | `a` | `b` | `c` | what is needed | flips |
|---|---|---|---|---|---|
| 0 | 0 | 0 | 1 | the OR must be 1, but neither is set — turn one of them on | 1 |
| 1 | 1 | 1 | 0 | the OR must be 0, so **both** bits have to be cleared | 2 |
| 2 | 0 | 1 | 1 | the OR is already 1 | 0 |

Total: `1 + 2 + 0 = 3`.

## Example 2

**Input**
```
4 2 7
```

**Output**
```
1
```

**Explanation:** `a = 100`, `b = 010`, so `a | b = 110`. Only bit `0` is missing, and turning it on
in either `a` or `b` costs one flip.

## Example 3

**Input**
```
1152921504606846975 1152921504606846975 0
```

**Output**
```
120
```

**Explanation:** all 60 bits are set in both `a` and `b`, and `c` needs every one of them cleared —
two flips per bit.
