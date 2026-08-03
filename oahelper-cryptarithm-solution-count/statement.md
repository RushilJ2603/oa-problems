# Cryptarithm Solution Count

A cryptarithm replaces each letter with a digit so that an arithmetic sentence becomes true. You are given three words `word1`, `word2`, and `word3` standing for the equation

```
word1 + word2 = word3
```

Count how many **valid solutions** exist.

A mapping is valid when:

- every distinct letter maps to a **different** digit (0–9), and
- no **multi-digit** number has leading digit zero.

A single-letter word is a one-digit number, so that letter may map to 0.

## Input

- Line 1: `word1`
- Line 2: `word2`
- Line 3: `word3`

Each word is non-empty and contains only uppercase English letters `A`–`Z`.

## Output

Print a single integer: the number of valid solutions (or `0`).

## Constraints

- `1 ≤ length of each word ≤ 35`
- Every character is an uppercase English letter

## Examples

### Example 1

Input:
```
SEND
MORE
MONEY
```

Output:
```
1
```

Explanation: one mapping is `9567 + 1085 = 10652`.

### Example 2

Input:
```
GREEN
BLUE
BLACK
```

Output:
```
12
```
