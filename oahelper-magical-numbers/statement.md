# Magical Numbers

A non-negative integer `d` is **magical** if it is either a power of two or a factorial — that is, if
`d = 2^a` for some `a >= 0`, or `d = a!` for some `a >= 0` (with `0! = 1`).

For example `1`, `4` and `6` are magical (`1 = 1!`, `4 = 2^2`, `6 = 3!`), while `10` and `18` are not.

Given a positive integer `n`, find the smallest `k` such that `n` can be written as a sum of `k`
**distinct** magical numbers. If `n` cannot be written that way at all, report `-1`.

Two magical numbers are distinct when their **values** differ. Note that `1` and `2` each qualify as
magical for two separate reasons (`1 = 2^0 = 1!`, `2 = 2^1 = 2!`), but each is still just one number
and may be used at most once.

## Input

- The first line contains an integer `t` — the number of test cases.
- Each of the next `t` lines contains a single integer `n`.

## Output

For each test case print one line: the minimum `k`, or `-1` if no representation exists.

## Constraints

- `1 <= t <= 100`
- `1 <= n <= 10^9`

## Example

**Input**
```
5
1
4
7
23
127
```

**Output**
```
1
1
2
3
3
```

**Explanation**

- `1` is already magical (`1 = 1!`), so `k = 1`.
- `4` is already magical (`4 = 2^2`), so `k = 1`.
- `7 = 1 + 6`, two distinct magical numbers (`1 = 1!` and `6 = 3!`), so `k = 2`. No single magical
  number equals 7.
- `23 = 1 + 6 + 16`, so `k = 3`.
- `127 = 1 + 6 + 120`, so `k = 3`. Writing it only with powers of two would need seven of them
  (`127 = 1 + 2 + 4 + 8 + 16 + 32 + 64`).
