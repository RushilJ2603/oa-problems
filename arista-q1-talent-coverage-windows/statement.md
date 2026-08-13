# Talent Coverage Windows

A campus recruiting drive has lined up `n` students in a queue. Every student has exactly one
talent, numbered from `1` to `talentsCount`. The i-th student in the queue has talent
`talent[i]`.

A recruiter walks down the queue and stops at some student, then keeps taking students **from that
point onwards, in queue order, without skipping anyone**, until the group they have taken covers
**every** talent from `1` to `talentsCount` at least once.

For each starting position, report how many students the recruiter ends up taking.

## Task

Return an array `ans` of length `n`, where:

- `ans[i]` is the **smallest** `L` such that the students at positions `i, i+1, …, i+L-1` together
  contain every talent in `1 … talentsCount`.
- `ans[i]` is `-1` if no such group exists — that is, starting at `i` and taking every remaining
  student still leaves some talent unrepresented.

## Input Format

```
n talentsCount
talent[0] talent[1] … talent[n-1]
```

## Output Format

`n` integers separated by whitespace — `ans[0] … ans[n-1]`.

## Constraints

- \(1 \le n \le 2 \times 10^5\)
- \(1 \le \texttt{talentsCount} \le 2 \times 10^5\)
- \(1 \le \texttt{talent}[i] \le \texttt{talentsCount}\)

## Examples

### Example 1

**Input**
```
4 3
2 3 1 2
```

**Output**
```
3 3 -1 -1
```

**Explanation:**
Starting at 0, the students `[2, 3, 1]` already cover talents 1, 2 and 3 — three students.
Starting at 1, `[3, 1, 2]` covers all three — three students.
Starting at 2, only `[1, 2]` remain and talent 3 never appears again, so the answer is `-1`.
Starting at 3, only `[2]` remains — `-1`.

### Example 2

**Input**
```
4 3
2 2 3 1
```

**Output**
```
4 3 -1 -1
```

**Explanation:**
Starting at 0 the recruiter must go all the way to the last student to pick up talent 1, taking all
four. The duplicate `2` at the front costs a student without covering anything new.

### Example 3

**Input**
```
5 1
1 1 1 1 1
```

**Output**
```
1 1 1 1 1
```

**Explanation:** With one talent in the pool, one student is always enough.
