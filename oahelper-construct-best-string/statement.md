# Construct Best String

You are given `n` building blocks — strings `LIST[0..n-1]` with integer scores `POINTS[0..n-1]` — and an integer length budget `limit`.

You may construct a string `ANS` of length **at most** `limit` by writing lowercase letters. Every time a block string appears in `ANS` as a contiguous substring, you score its points. The same block may contribute multiple times (including through overlapping occurrences), and different blocks may overlap in `ANS`.

Return the **maximum total score** achievable by any string of length at most `limit`. If `n = 0` or `limit = 0`, the answer is `0`.

## Input Format

- Line 1: integer `n`.
- If `n > 0`:
  - Line 2: `n` strings — the list `LIST`.
  - Line 3: `n` integers — the list `POINTS`.
  - Line 4: integer `limit`.
- If `n = 0`:
  - Line 2: integer `limit`.

## Output Format

Print a single integer — the maximum score.

## Constraints

- \(0 \le n \le 50\)
- \(0 \le limit \le 10^6\)
- Each string in `LIST` has length between \(1\) and \(50\) and consists of lowercase English letters.
- The total length of all strings in `LIST` is at most \(200\).
- \(1 \le POINTS[i] \le 10^4\) when `n > 0`.
- The answer fits in a signed 64-bit integer.

## Examples

### Example 1

**Input**
```
2
abc pqrs
3 5
6
```

**Output**
```
6
```

**Explanation:** `abcabc` scores \(3+3=6\). Using `pqrs` alone scores only `5`.

### Example 2

**Input**
```
2
energy green
5 2
10
```

**Output**
```
7
```

### Example 3

**Input**
```
3
pack acknowledge edged
2 3 4
15
```

**Output**
```
16
```

**Explanation:** Overlaps are allowed — e.g. fragments of `pack`, `acknowledge`, and `edged` can share letters inside one constructed string.
