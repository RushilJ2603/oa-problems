# Buy Concert Tickets

Louie wants to buy exactly `m` tickets for an upcoming concert. Ticket prices change every day. On day `n` (days are numbered from `0`), buying `T` tickets costs

\[
\mathrm{Cost} = k^{n} \times T^{2}
\]

where `k` is a given positive constant. Louie may buy any non-negative number of tickets on any day and may use as many days as he likes. Help him find the **minimum total cost** of purchasing exactly `m` tickets.

## Input Format

- Line 1: integer `m` — the number of tickets to buy.
- Line 2: integer `k` — the constant in the cost formula.

## Output Format

Print a single integer — the minimum total cost.

## Constraints

- \(0 \le m \le 10^6\)
- \(1 \le k \le 10^4\)
- The answer always fits in a signed 64-bit integer.

## Examples

### Example 1

**Input**
```
6
2
```

**Output**
```
21
```

**Explanation:** Buy 3 tickets on day 0, 2 on day 1, and 1 on day 2:
\(2^0\cdot 3^2 + 2^1\cdot 2^2 + 2^2\cdot 1^2 = 9 + 8 + 4 = 21\).

### Example 2

**Input**
```
1
5
```

**Output**
```
1
```

**Explanation:** One ticket on day 0 costs \(5^0\cdot 1^2 = 1\).

### Example 3

**Input**
```
3
1
```

**Output**
```
3
```

**Explanation:** When `k = 1` every day multiplier is `1`, so buying one ticket on each of three days costs `3`. Buying all three on one day would cost `9`.
