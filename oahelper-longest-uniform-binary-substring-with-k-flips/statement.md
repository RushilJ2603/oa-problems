# Longest Uniform Binary Substring with K Flips

A telemetry pipeline stores a binary status log as a string `str` of length `n` (only characters `0` and `1`). In one repair you may flip any single character (`0` ↔ `1`).

You may perform **at most `k` flips**. After those flips, find the length of the **longest contiguous substring** that consists of identical characters.

Flips may be applied anywhere in the string; only the chosen contiguous window needs to become uniform.

## Input Format

- The first line contains an integer `n` — the length of the string.
- The second line contains the binary string `str` of length `n`.
- The third line contains an integer `k` — the maximum number of flips allowed.

## Output Format

Print a single integer — the maximum achievable length of a uniform contiguous substring using at most `k` flips.

## Constraints

- \(1 \le n \le 10^5\)
- \(0 \le k \le n\)
- `str` consists only of the characters `0` and `1`

## Examples

### Example 1

**Input**
```
10
0111110010
2
```

**Output**
```
8
```

**Explanation**

Flip indices 6 and 7 (0-based) to obtain `0111111110`. The longest uniform substring then has length 8.

### Example 2

**Input**
```
12
010101010101
3
```

**Output**
```
7
```

**Explanation**

The string alternates. The window of length 7 starting at index 0 has 4 zeros and 3 ones; flipping the 3 ones yields seven zeros. Any length-8 alternating window needs 4 flips, which exceeds `k = 3`.
