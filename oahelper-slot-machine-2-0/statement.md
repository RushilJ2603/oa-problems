# Slot Machine 2.0

A slot machine has several **wheels**. Over \(n\) spins you recorded the digits shown on the dashboard. Spin \(i\) is given as a string `history[i]` of equal length \(m\) (one digit per wheel position on that spin). Digits are characters `'0'`–`'9'`.

You may **reassign** which digit on a given spin belongs to which wheel — that is, for each spin independently, the multiset of digits must be produced by the wheels, but column order within a spin does not matter for construction. Each wheel \(j\) has some number of stops \(s_j\) (an integer from \(0\) to \(9\)); it can display any digit \(d\) only if \(d \le s_j\).

Find the **minimum total number of stops** \(\sum s_j\) across all wheels that can explain every recorded spin.

Equivalently: for each spin, sort its digits ascending; then for each column (wheel), take the maximum digit seen in that column across all spins; sum those maxima.

## Input

- The first line contains an integer \(n\) — the number of spins.
- Each of the next \(n\) lines contains a string `history[i]` of equal length \(m\), consisting of digits `'0'`–`'9'`.

## Output

Print a single integer — the minimum total stops.

## Constraints

- \(1 \le n \le 50\)
- \(1 \le m = |\text{history}[i]| \le 50\)
- All `history[i]` have the same length
- Each character is in `'0'`–`'9'`

## Examples

### Example 1

**Input**
```
4
137
364
115
724
```

**Output**
```
14
```

**Explanation.** After sorting each spin's digits, column maxima are \(7\), \(4\), and \(3\), totaling \(14\).

### Example 2

**Input**
```
4
1112
1211
1111
1111
```

**Output**
```
5
```

**Explanation.** Column maxima are \(2,1,1,1\), totaling \(5\).
