Saiki is grinding a mobile game between work meetings. Each calendar day lasts exactly `k` minutes (absolute times wrap every `k` minutes). Within each day he has `n` non-overlapping breaks `[l_i, r_i)` during which he may play. Every level takes exactly `t` consecutive minutes and must fit entirely inside a single break. He must finish `m` levels in order (he may wait between levels).

The duration of a play session is `end - start`, where `start` is the absolute minute when the first level begins and `end` is the absolute minute when the last level finishes. Find the minimum possible duration, or `-1` if it is impossible to finish all `m` levels (for example when no break is long enough to hold even one level).

Breaks do not wrap across midnight: `0 ≤ l_i < r_i ≤ k`, and `r_i < l_{i+1}`.

## Input Format

- First line: `T` — number of test cases.
- For each test case:
  - One line with four integers `n m t k`.
  - `n` lines each with two integers `l_i r_i`.

The sum of `n` over all test cases is at most `10^6`.

## Output Format

For each test case print one line: the minimum duration in minutes, or `-1`.

## Constraints

- `1 ≤ T ≤ 2 · 10^5`
- `1 ≤ n ≤ 10^5`
- `1 ≤ m, k, t ≤ 10^9`
- `0 ≤ l_i < r_i ≤ k`
- `r_i < l_{i+1}`
- Sum of `n` over all tests `≤ 10^6`

## Examples

### Example 1

**Input**
```
1
1 5 3 9
3 7
```

**Output**
```
38
```

**Explanation:** The only break has length 4, so one level fits per day. Starting at minute 5 of day 1 and finishing at minute 7 of day 5 gives duration 38.

### Example 2

**Input**
```
1
1 5 5 9
3 7
```

**Output**
```
-1
```

**Explanation:** The break length is 4 but each level needs 5 minutes.

### Example 3

**Input**
```
1
1 1 3 10
0 5
```

**Output**
```
1
```
