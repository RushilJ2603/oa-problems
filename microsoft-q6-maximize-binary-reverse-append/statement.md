# Maximize the Final Binary String

You are given a binary string `S`. You may first **rearrange** its characters into any permutation
(the number of `0`s and `1`s must stay the same).

Then a new string `R` is built from the chosen permutation:

1. Start with `R` empty.
2. Process the permutation left to right. For each character:
   - **Reverse** the current `R`.
   - **Append** the current character to the end of `R`.

After all characters are processed, `R` is the final string. Since every final string has the same
length, maximizing its binary value is the same as making it the lexicographically largest string.

Output a permutation of `S` that produces the **maximum** possible final string `R`.

> For a given `S` this optimal permutation is **unique**, so there is exactly one correct answer per
> test case.

## Input

```
T
S_1
S_2
...
S_T
```

- Line 1: the number of test cases `T`.
- Each of the next `T` lines: a binary string `S_i`.

## Output

For each test case, print the permutation of `S_i` that maximizes the final string.

## Constraints

- `1 ≤ T`
- `1 ≤ |S_i|`
- The sum of `|S_i|` over all test cases does not exceed `2 × 10^5`.

## Example 1

**Input**
```
2
00001
1100
```
**Output**
```
00010
1010
```

For `1100`, choosing the permutation `1010` builds `R` as:

| Step | Operation | R |
|------|-----------|----|
| start | | `` |
| read `1` | reverse `` → ``, append `1` | `1` |
| read `0` | reverse `1` → `1`, append `0` | `10` |
| read `1` | reverse `10` → `01`, append `1` | `011` |
| read `0` | reverse `011` → `110`, append `0` | `1100` |

giving the maximum `1100`.

For `00001` (one `1`, four `0`s), the best final string places the single `1` at the very front —
`10000` — which requires the input permutation `00010`.
