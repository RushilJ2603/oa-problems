# Valid Parentheses with Limited Replacements

You are given a string `s` consisting only of the characters `(` and `)`, and an
integer `k` — a maximum replacement budget.

In one **replacement** you may pick any single `)` in the string and replace it with the
two characters `()`. You may perform **at most `k`** such replacements (using fewer, including
zero, is allowed).

A string is **valid** if it is a correctly balanced parenthesis string: every `(` has a
matching `)` that comes after it, and every prefix has at least as many `(` as `)`.

Return `1` if `s` can be made valid using at most `k` replacements (whether or not the full
budget is used), and `0` otherwise.

## Input

```
s
k
```

- Line 1: the string `s` (only `(` and `)`).
- Line 2: the integer `k`.

## Output

A single integer: `1` if `s` can be made valid using at most `k` replacements, else `0`.

## Constraints

- `1 ≤ |s| ≤ 200000`
- `0 ≤ k ≤ 200000`
- `s` contains only the characters `(` and `)`.

## Example 1

**Input**
```
())
1
```
**Output**
```
1
```
Replacing the middle `)` with `()` gives `(())`, which is valid. One replacement, within budget.

## Example 2

**Input**
```
)(
5
```
**Output**
```
0
```
No number of `)` → `()` replacements can fix a leading `)`; each replacement only adds an opening
parenthesis and can never move or remove the stray `)` at the front.

## Example 3

**Input**
```
))
2
```
**Output**
```
1
```
Replace both `)` to get `()()`, which is valid. Exactly two replacements are needed, and the budget
allows it.
