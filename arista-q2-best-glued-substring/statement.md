# Best Glued Substring

You are given three lowercase strings: a main string `s`, a **prefix string** `p`, and a **suffix
string** `q`.

Take any non-empty substring `t` of `s` (a contiguous run of characters). Imagine gluing the three
together in order — `p`, then `t`, then `q` — and pushing them into each other as far as they will
go. Characters that coincide at a join **fuse**.

- **prefixScore(t)** is how many characters fuse at the left join: the largest `k` such that the
  **last `k`** characters of `p` are exactly the **first `k`** characters of `t`.
- **suffixScore(t)** is how many characters fuse at the right join: the largest `k` such that the
  **last `k`** characters of `t` are exactly the **first `k`** characters of `q`.

Both are `0` when nothing fuses, and neither can exceed `|t|`. The two joins are **independent** —
when `t` is short, the same characters of `t` may be counted at both ends.

**score(t) = prefixScore(t) + suffixScore(t)**

Find the substring of `s` with the largest score. If several substrings tie, report the
**lexicographically smallest** of them.

## Input Format

```
s
p
q
```

## Output Format

The winning substring, on one line.

## Constraints

- \(1 \le |s|, |p|, |q| \le 2000\)
- All three strings consist only of lowercase English letters (`a`–`z`).

## Examples

### Example 1

**Input**
```
engine
eaten
inebrious
```

**Output**
```
engine
```

**Explanation:**

```
   eat[en]
      [en]gine          prefixScore = 2
        eng[ine]
           [ine]brious  suffixScore = 3
                        score       = 5
```

No other substring of `engine` reaches 5. `engin` fuses `en` on the left but only `in` on the
right, for 4.

### Example 2

**Input**
```
ab
b
a
```

**Output**
```
a
```

**Explanation:** `a` scores `0 + 1 = 1` (nothing fuses with `b` on the left; its own `a` fuses with
`q`). `b` scores `1 + 0 = 1`. `ab` scores `0 + 0 = 0`. Two substrings tie at 1, so the
lexicographically smaller one, `a`, wins.

### Example 3

**Input**
```
cbdcaec
ea
ca
```

**Output**
```
aec
```

**Explanation:** `aec` fuses `a` on the left (`p = ea` ends with `a`) and `c` on the right
(`q = ca` starts with `c`), scoring `1 + 1 = 2`.

The single character `a` scores only `1 + 0 = 1`. On its right join, the last 1 character of `a` is
`a`, while `q` starts with `c` — no fuse. Note that the text `cbdca` **ending at the same place**
does fuse two characters there (`ca` with `ca`), but that fuse needs two characters of the
substring, and `a` only has one. A fuse of length 2 being available says nothing about a fuse of
length 1 being available: they compare different characters.
