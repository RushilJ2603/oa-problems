# Array Generator

Your project team needs to work closely with a group of software testers. They have requested an **array generator** service to help exercise product behavior under controlled sequences.

The service receives:

- an array `values` of `n` positive integers
- a string `state` of length `n` whose characters are `'0'` or `'1'`
  - `state[i] = '1'` means `values[i]` is **available**
  - `state[i] = '0'` means `values[i]` is **blocked**
- an integer `m` — the number of operations to perform

You build a sequence `S` (initially empty) by repeating the following operation exactly `m` times:

1. Choose any available value (any index `i` with `state[i] = '1'`). The same index may be chosen in many operations.
2. Append that chosen value to `S`.
3. Simultaneously unlock every blocked position whose **left neighbor was already available before this unlock step**: for every `i` with `state[i] = '0'` and `state[i - 1] = '1'`, set `state[i]` to `'1'`.

For example, if `state = "010010"` before an operation, it becomes `"011011"` after the unlock step.

Find the **lexicographically largest** sequence `S` of length `m` that can be obtained this way.

A sequence `x` of length `m` is lexicographically larger than `y` of length `m` if there exists an index `i` (`0 ≤ i < m`) such that `x[i] > y[i]`, and `x[j] = y[j]` for all `j < i`.

If it is impossible to complete `m` operations (because at some step no value is available), output an empty line.

## Input Format

- The first line contains an integer `n`.
- The second line contains `n` integers `values[1] … values[n]`.
- The third line contains the string `state` of length `n`.
- The fourth line contains an integer `m`.

## Output Format

- If a sequence of length `m` exists, print `m` space-separated integers — the lexicographically largest such sequence.
- Otherwise (including when `m = 0`), print an empty line.

## Constraints

- \(1 \le n \le 10^5\)
- \(1 \le values[i] \le 10^{12}\)
- `state` has length `n` and consists only of characters `'0'` and `'1'`
- \(0 \le m \le 10^5\)

## Examples

### Example 1

**Input**
```
4
10 5 7 6
0101
2
```

**Output**
```
6 7
```

**Explanation**

Initially available values are `5` (index 1) and `6` (index 3). Taking `6` first is best. After the unlock, state becomes `"0111"`, so available values include `5`, `7`, and `6`. Taking `7` next yields `6 7`, which is lexicographically largest.

### Example 2

**Input**
```
1
42
1
1
```

**Output**
```
42
```

**Explanation**

The only available value is `42`, and one operation produces the sequence `42`.
