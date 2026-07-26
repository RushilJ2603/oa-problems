# Lexicographically Smallest Balanced String

You are given a lowercase English string `s` of length `n` and a positive integer `k`.

A string is **balanced** if the frequency of every character in it is a multiple of `k` (zero is allowed).

Find the **lexicographically smallest balanced string of length `n`** that is **lexicographically greater than or equal to `s`**. If no such string exists, output `-1`.

## Input Format

- Line 1: two integers `n` and `k` (\(1 \le k \le n \le 10^5\)).
- Line 2: the string `s` consisting of `n` lowercase English letters.

It is guaranteed that across a single input stream the total length of all strings does not exceed \(10^5\) when multiple cases appear; this package uses one test case per file.

## Output Format

Print the answer string, or `-1`.

## Constraints

- \(1 \le k \le n \le 10^5\)
- `s` contains only lowercase English letters `a`–`z`.
- If `n` is not divisible by `k`, the answer is always `-1` (a balanced length-`n` string cannot exist).

## Examples

### Example 1

**Input**
```
4 2
abcd
```

**Output**
```
acac
```

**Explanation:** `acac` is \(\ge\) `abcd` and every letter frequency is a multiple of `2`.

### Example 2

**Input**
```
9 3
abaabaaaa
```

**Output**
```
abaabaaab
```

### Example 3

**Input**
```
10 3
abcdefghij
```

**Output**
```
-1
```
