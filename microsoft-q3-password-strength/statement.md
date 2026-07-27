# Password Strength Classifier

You are given a list of `passwords` and a list of `common words`. For every password, decide whether
it is **weak** or **strong**.

A password is **weak** if **any** of the following holds:

1. It consists **only of digits** (`0`–`9`).
2. It consists **only of uppercase letters** (`A`–`Z`), **or only of lowercase letters** (`a`–`z`).
3. Its length is **less than 6**.
4. Some common word occurs in it as a **substring** (case-sensitive).

Otherwise the password is **strong**.

## Input

```
n
password_1
...
password_n
c
word_1
...
word_c
```

- Line 1: `n`, the number of passwords.
- The next `n` lines: the passwords (one per line, no spaces).
- The next line: `c`, the number of common words (may be `0`).
- The next `c` lines: the common words (one per line, no spaces).

## Output

`n` lines. For each password print `weak` or `strong`, in input order.

## Constraints

- `1 ≤ n ≤ 1000`
- `0 ≤ c ≤ 1000`
- `1 ≤ |password_i| ≤ 20`
- `1 ≤ |word_j| ≤ 20`
- All strings consist of visible ASCII characters and contain no spaces.
- Substring matching is case-sensitive.

## Example 1

**Input**
```
5
12345678
Abcdef1
hello
PASSWORD
Str0ng#Pass
2
word
admin
```
**Output**
```
weak
strong
weak
weak
strong
```

- `12345678` — only digits → weak.
- `Abcdef1` — length 7, mixed types, no common word inside → strong.
- `hello` — length 5 (< 6) → weak.
- `PASSWORD` — only uppercase letters → weak.
- `Str0ng#Pass` — length 11, mixed, no common word inside → strong.
