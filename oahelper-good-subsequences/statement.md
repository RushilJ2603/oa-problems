# Good Subsequences

A **subsequence** of a string is obtained by deleting zero or more characters and concatenating what remains, keeping left-to-right order. Two subsequences are different whenever the *set of positions* they use differs, even if the resulting strings look identical.

A non-empty subsequence is **good** if every character that appears in it appears the same number of times. For example, `ab`, `aabb`, and `xyz` are good, while `aab` is not (`a` appears twice and `b` once).

Given a string `word` of lowercase Latin letters, count how many good subsequences it has. Print the answer modulo \(10^9+7\).

The empty subsequence is **not** counted.

## Input Format

A single line containing the string `word`.

## Output Format

Print one integer — the number of good subsequences modulo \(10^9+7\).

## Constraints

- \(1 \le |word| \le 10^5\)
- `word` consists only of lowercase letters `a`–`z`.

## Examples

### Example 1

**Input**
```
abca
```

**Output**
```
12
```

**Explanation:** There are \(2^4-1=15\) non-empty subsequences. Exactly three are not good (`aba`, `aca`, `abca`), leaving \(12\).

### Example 2

**Input**
```
abcd
```

**Output**
```
15
```

**Explanation:** All letters are distinct, so every non-empty subsequence is good: \(2^4-1=15\).

### Example 3

**Input**
```
baab
```

**Output**
```
11
```
