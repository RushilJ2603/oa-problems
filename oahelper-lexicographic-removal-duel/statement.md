# Lexicographic Removal Duel

At an internal developer summit, two engineers — **Alex** and **Charlie** — compete in a coding duel. They are given a string `S` of lowercase English letters.

## Game rules

- Players take turns removing **exactly one** character from the current string; **Alex goes first**.
- The game continues until exactly one character remains.

## Removal strategy

- **Alex** always removes the character that makes the resulting string the *lexicographically smallest* possible.
- **Charlie** always removes the character that makes the resulting string the *lexicographically largest* possible.

Both players always follow their own strategy. Report the single character that remains at the end.

Lexicographic order compares two equal-length strings left to right; the first position where they differ decides which is smaller (e.g. `"abc" < "abd"`).

When several removals produce the same resulting string, any of those removals is acceptable (they leave identical strings).

## Input Format

A single line containing the string `S`.

## Output Format

Print a single character — the last character left in the string.

## Constraints

- \(1 \le |S| \le 200\,000\)
- `S` consists only of lowercase English letters (`a`–`z`).

## Examples

### Example 1

**Input**
```
cat
```

**Output**
```
t
```

**Explanation:** Alex turns `"cat"` into `"at"` (smallest). Charlie turns `"at"` into `"t"` (largest).

### Example 2

**Input**
```
abcde
```

**Output**
```
c
```

### Example 3

**Input**
```
a
```

**Output**
```
a
```
