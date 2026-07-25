# Almost Matching

You are building a new programming language whose standard library can tell whether two strings are **almost matching**: they have the same length, and all corresponding characters agree except for exactly one position. For example, `cat` and `bat` are almost matching, but `cat` and `dog` are not.

To stress-test the feature efficiently, you work with one host string `s` and compare **substrings** of `s` (each substring is identified by its starting index and length). Two substrings are considered a valid pair when:

1. They have the same length **strictly greater than** `k` (so index `k` exists in both).
2. They agree on every position except one, and that single mismatch is exactly at position `k` (0-based within the substring).
3. The first substring starts at a smaller index than the second (unordered pairs counted once).

Given a lowercase string `s` and an integer `k`, count how many such substring pairs exist.

## Input

The first line contains the string `s`.  
The second line contains the integer `k`.

## Output

Print one integer: the number of valid pairs.

## Constraints

- `1 ≤ |s| ≤ 2000`
- `0 ≤ k < |s|`
- `s` consists of lowercase English letters

## Examples

### Example 1

**Input**

```
a
0
```

**Output**

```
0
```

Only one substring starts at index `0`; no pair of distinct starts exists.

### Example 2

**Input**

```
ab
0
```

**Output**

```
1
```

The substrings starting at `0` and `1`, each of length `1`, differ at position `0`: `"a"` vs `"b"`.

### Example 3

**Input**

```
ababa
0
```

**Output**

```
6
```

Several length-1 and longer pairs differ only at their first character while matching afterward.
