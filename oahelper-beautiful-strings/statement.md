# Beautiful Strings Count

A language lab is cataloguing lowercase English strings. A string **S** of length **N** is called **beautiful** when both of the following hold:

1. There is **no** index *i* where both *S_i* and *S_{i+1}* are vowels.
2. The number of indices *i* with *S_i = S_{i+1}* is **exactly** **K**.

Vowels are `{a, e, i, o, u}` (consonants are the other 21 letters).

Count the beautiful strings of length **N**. Because the answer can be huge, return it modulo \(10^9+7\).

## Input Format

Two integers **N** and **K** (on one line, or on two successive lines).

## Output Format

A single integer — the number of beautiful strings modulo \(10^9+7\).

## Constraints

- \(1 \le N \le 10^9\)
- \(0 \le K \le 100\)

## Examples

### Example 1

**Input**
```
2 0
```

**Output**
```
630
```

**Explanation**

Length-2 strings with no equal consecutive letters and no adjacent vowels. There are 630 such strings.

### Example 2

**Input**
```
3 1
```

**Output**
```
1050
```

**Explanation**

Exactly one pair of equal consecutive letters, no adjacent vowels, length 3.
