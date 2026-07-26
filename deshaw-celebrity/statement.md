# Find the Celebrity

At a party of **n** people (numbered `0 … n − 1`) there may be a **celebrity** — a person who **is
known by everyone else** but **knows nobody**.

You are given the acquaintance matrix `knows`, where `knows[i][j] = 1` means person **i** knows person
**j**, and `0` means they do not. A person never knows themselves, so `knows[i][i] = 0`.

There is **at most one** celebrity. Output the celebrity's index, or **−1** if there is none.

## Input Format

- Line 1: integer **n**.
- Next **n** lines: **n** integers each (`0` or `1`) — row `i` is `knows[i][0..n-1]`.

## Output Format

- A single integer — the index of the celebrity, or `-1` if there is no celebrity.

## Constraints

- $1 \le n \le 700$
- `knows[i][j]` ∈ {0, 1}, and `knows[i][i] = 0`.

## Examples

### Example 1

**Input:**
```
3
0 1 0
0 0 0
0 1 0
```

**Output:**
```
1
```

Person 1 knows nobody, and both person 0 and person 2 know person 1 — so person 1 is the celebrity.

### Example 2

**Input:**
```
2
0 1
0 0
```

**Output:**
```
1
```

Person 0 knows person 1; person 1 knows nobody and is known by person 0.

### Example 3

**Input:**
```
3
0 1 0
1 0 0
0 0 0
```

**Output:**
```
-1
```

Person 2 knows nobody but nobody knows person 2, so person 2 is not a celebrity; no one qualifies.
