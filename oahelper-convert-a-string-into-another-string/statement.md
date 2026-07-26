# Convert a String Into Another String

At IBM's text-processing lab, an engineer is building a spell-correction prototype. Given a source word `word1` and a target word `word2`, compute the **minimum** number of single-character edits needed to turn `word1` into `word2`.

The three allowed edits are:

- **Insert** one character anywhere.
- **Delete** one character anywhere.
- **Replace** one character with a different character.

Each edit costs exactly 1. Characters are case-sensitive and compared exactly (digits and letters are ordinary characters).

## Input Format

A single line with two whitespace-separated non-empty strings `word1` and `word2`.

## Output Format

Print a single integer — the minimum number of edits.

## Constraints

- \(1 \le |word1|, |word2| \le 500\)
- Each string consists of printable non-whitespace ASCII characters (letters, digits).

## Examples

### Example 1

**Input**
```
horse ros
```

**Output**
```
3
```

**Explanation:** One optimal sequence is `horse` → `rorse` (replace `h`→`r`) → `rose` (delete `r`) → `ros` (delete `e`).

### Example 2

**Input**
```
intention execution
```

**Output**
```
5
```

### Example 3

**Input**
```
abc abc
```

**Output**
```
0
```

**Explanation:** Identical strings need zero edits.
