# Count Ways to Transform a String

A messaging service stores every payload as a circular buffer of lowercase letters. Engineers discovered that a single repair step on a buffer `s` of length `n` works as follows:

- Choose a non-empty **suffix** of `s` whose length `l` satisfies `1 ≤ l < n`.
- Cut that suffix off and **prepend** it to the front of `s`.

For example, applying the step with `l = 2` to `"abcd"` yields `"cdab"`.

You are given the current buffer `s`, a target buffer `t` of the same length, and an integer `k`. Count how many sequences of **exactly `k`** such steps transform `s` into `t`. Two sequences are different whenever the chosen suffix lengths differ in at least one position, even if intermediate buffers look identical.

Because the answer can be huge, return it modulo `10^9 + 7`.

When `n = 1` there is no legal suffix length, so no step can ever be performed and the answer is `0`.

## Input Format

- Line 1: the string `s` of length `n`.
- Line 2: the string `t` of length `n`.
- Line 3: the integer `k`.

## Output Format

A single integer — the number of distinct length-`k` sequences that turn `s` into `t`, modulo `10^9 + 7`.

## Constraints

- `1 ≤ n ≤ 1000`
- `1 ≤ k ≤ 10^9`
- `s` and `t` consist of lowercase English letters and have the same length.

## Examples

### Example 1

```
Input
abcd
cdab
2

Output
2
```

First sequence: suffix length 1 then suffix length 1 (`"abcd"` → `"dabc"` → `"cdab"`).  
Second sequence: suffix length 3 then suffix length 3 (`"abcd"` → `"bcda"` → `"cdab"`).

### Example 2

```
Input
ababab
ababab
1

Output
2
```

With one step, only the suffix lengths 2 and 4 leave the buffer unchanged (its period is 2). A full-length rotation is forbidden, so the answer is 2, not 1.
