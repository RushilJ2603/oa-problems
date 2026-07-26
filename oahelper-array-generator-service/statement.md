# Array Generator Service

A QA team needs a deterministic array generator for load testing. You are given:

- an array `values` of `n` integers,
- a binary string `state` of length `n` (`'1'` = available, `'0'` = blocked),
- an integer `m` — the number of append operations to perform.

Start with an empty sequence `S`. Perform the following operation exactly `m` times:

1. Choose any currently available index `i` (`state[i] == '1'`). The same index may be chosen in many operations.
2. Append `values[i]` to `S`.
3. Simultaneously unlock every blocked index that is adjacent to at least one currently available index: for every `i` with `state[i] == '0'`, if `state[i-1] == '1'` or `state[i+1] == '1'` (when those neighbours exist), set `state[i]` to `'1'`. Availability only ever expands; once unlocked, an index stays available forever.

Return the **lexicographically largest** sequence `S` of length `m` obtainable this way.

A sequence `x` is lexicographically larger than `y` if at the first position where they differ, `x` has the greater value.

It is guaranteed that `state` contains at least one `'1'` initially.

## Input Format

- Line 1: integer `n`
- Next `n` lines: the elements of `values` (one per line)
- Next line: the string `state` of length `n`
- Next line: integer `m`

## Output Format

Print `m` lines — the elements of the lexicographically largest sequence `S`, one per line.

## Constraints

- `1 ≤ n, m ≤ 10^5`
- `0 ≤ values[i] ≤ 10^9`
- `|state| = n`, each character is `'0'` or `'1'`
- `state` contains at least one `'1'`

## Examples

### Example 1

**Input**
```
4
5
4
3
6
1100
5
```

**Output**
```
5
5
6
6
6
```

**Explanation**

| step | state | available values | choice |
|------|-------|------------------|--------|
| 1 | 1100 | 5, 4 | 5 |
| 2 | 1110 | 5, 4, 3 | 5 |
| 3 | 1111 | 5, 4, 3, 6 | 6 |
| 4 | 1111 | 5, 4, 3, 6 | 6 |
| 5 | 1111 | 5, 4, 3, 6 | 6 |

### Example 2

**Input**
```
4
10
5
7
6
0101
2
```

**Output**
```
6
10
```

**Explanation**

Initially indices 1 and 3 are available (`values` 5 and 6). Pick 6. After the unlock wave the state becomes `0111`, so 10 becomes available and is picked next.
