# K-th Binary Subsequence Number

You are given three integers **L**, **R**, and **K**.

Consider the integers in the closed range `[L, R]`. Call an integer **special** if its binary representation (no leading zeros) contains the bit pattern `101` as a **subsequence** — there exist indices `i < j < k` whose bits are `1`, `0`, and `1` respectively (they need not be adjacent).

Find the **K-th smallest** special integer in `[L, R]`. If fewer than K special integers exist in the range, output `-1`.

## Input Format

A single line with three space-separated integers `L R K`.

## Output Format

A single integer: the K-th smallest special number in `[L, R]`, or `-1`.

## Constraints

- \(1 \le L \le R \le 10^{18}\)
- \(1 \le K \le 10^{18}\)

## Examples

### Example 1

**Input:**
```
1 5 1
```

**Output:**
```
5
```

Numbers 1..4 have binary `1`, `10`, `11`, `100` — none contain subsequence `101`. Number 5 is `101`, so it is the 1st special value.

### Example 2

**Input:**
```
1 4 1
```

**Output:**
```
-1
```

No special numbers exist in `[1, 4]`.

### Example 3

**Input:**
```
1 20 3
```

**Output:**
```
10
```

Special numbers in the range include 5 (`101`), 10 (`1010`), 11 (`1011`), … — the 3rd is 10.
