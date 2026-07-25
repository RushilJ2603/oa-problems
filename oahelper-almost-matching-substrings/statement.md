# Almost Matching Substrings

You are designing a language feature that asks whether two strings are *almost matching*.

Two equal-length strings are **almost matching with respect to a position `k`** when they differ at 0-based offset `k` and agree everywhere else. Both strings must be longer than `k`.

Given a string `s` and an integer `k`, count ordered pairs of substrings of `s` that are almost matching with respect to `k`.

Substrings are identified by their index ranges, so two occurrences of the same text at different places are distinct. The pair `(A, B)` is different from `(B, A)`; both are counted when both qualify.

## Input Format

- The first line contains the string `s`.
- The second line contains the integer `k`.

## Output Format

Print a single integer — the number of ordered pairs.

## Constraints

- `1 ≤ |s| ≤ 1500`
- `s` consists of lowercase English letters only
- `0 ≤ k < |s|`
- The answer always fits in a signed 32-bit integer

## Examples

### Example 1

Input:
```
abacaba
1
```

Output:
```
8
```

### Example 2

Input:
```
abc
0
```

Output:
```
6
```

### Example 3

Input:
```
banana
1
```

Output:
```
0
```
