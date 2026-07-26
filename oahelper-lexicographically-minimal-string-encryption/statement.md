# Lexicographically Minimal String Encryption

A messaging service encrypts a string `originalString` with a temporary buffer as follows.

Initialize two empty strings: `temporaryString` and `encryptedString`. While characters remain to process, repeatedly perform exactly one of these operations:

1. Take the **first** character of `originalString` and append it to the **end** of `temporaryString`.
2. Take the **last** character of `temporaryString` (if it is non-empty) and append it to the **end** of `encryptedString`.

Every character of `originalString` must eventually move through `temporaryString` into `encryptedString`. Among all valid sequences of operations, choose one that produces the **lexicographically minimal** possible `encryptedString`, and return that string.

`temporaryString` behaves as a stack: characters enter at the end and leave from the end.

## Input

- One line containing `originalString`.

## Output

- One line containing the lexicographically minimal `encryptedString`.

## Constraints

- \(1 \le |originalString| \le 2 \times 10^5\)
- `originalString` consists of lowercase English letters `a`–`z`.

## Examples

### Example 1

Input:
```
dby
```

Output:
```
bdy
```

### Example 2

Input:
```
zyxw
```

Output:
```
wxyz
```

### Example 3

Input:
```
ba
```

Output:
```
ab
```
