# Encryptable Subsequences

A security team encrypts messages by keeping only certain subsequences of a password string `S`.

A non-empty subsequence of `S` is **encryptable** if and only if the difference between the largest and smallest character codes (ASCII / Unicode ordinals) among the characters it uses is at most `17`.

Characters may repeat in `S`. Two subsequences that pick different index sets are counted as distinct, even if they form the same string.

Count the number of non-empty encryptable subsequences of `S`. Since the answer can be large, return it modulo `998244353`.

## Input

- One line containing the string `S`.

## Output

- A single integer: the count of non-empty encryptable subsequences of `S`, modulo `998244353`.

## Constraints

- \(1 \le |S| \le 1000\)
- `S` consists of printable ASCII characters (letters, digits, underscore, etc.)

## Examples

### Example 1

Input:
```
code
```

Output:
```
15
```

Explanation: Every non-empty subsequence of `"code"` has max−min code ≤ 17, and there are \(2^4 - 1 = 15\) of them.

### Example 2

Input:
```
vode
```

Output:
```
11
```

Explanation: Characters `'v'` and `'d'` differ by 18, so any subsequence that contains both is not encryptable. The encryptable ones are `{v, o, d, e, vo, ve, od, oe, de, voe, ode}` — 11 total.

### Example 3

Input:
```
ajs
```

Output:
```
5
```

Explanation: `'s' - 'a' = 18 > 17`, so subsequences that mix `a` with `s` are invalid. The five valid ones are `{a, j, s, aj, js}`.
