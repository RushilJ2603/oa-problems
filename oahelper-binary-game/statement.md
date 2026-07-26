# Binary Game

AT&T's network lab is running a **Binary Game**: engineers assemble signal strings using only the digits `0` and `1`. A string is *good* when every run of ones has length exactly `one_group` (if any ones appear) and every run of zeros has length exactly `zero_group` (if any zeros appear).

In other words, good strings are concatenations of blocks of `one_group` ones and blocks of `zero_group` zeros — nothing else.

Given four integers `min_length`, `max_length`, `one_group`, and `zero_group`, count how many good binary strings have length in the closed range `[min_length, max_length]`. Return the answer modulo \(10^9 + 7\).

For example, with `one_group = 2` and `zero_group = 1`, the strings `"011"` and `"000"` are good, while `"001"` and `"111"` are not.

## Input Format

Four integers (whitespace-separated, possibly on separate lines):

- `min_length`
- `max_length`
- `one_group`
- `zero_group`

## Output Format

Print a single integer: the number of good binary strings with length in `[min_length, max_length]`, modulo \(10^9 + 7\).

## Constraints

- \(1 \le \textit{min\_length} \le \textit{max\_length} \le 10^5\)
- \(1 \le \textit{one\_group}, \textit{zero\_group} \le 2000\)

## Examples

### Example 1

**Input**
```
2
5
3
2
```

**Output**
```
5
```

**Explanation**

Good strings with length in `[2, 5]`:

- length 2: `"00"`
- length 3: `"111"`
- length 4: `"0000"`
- length 5: `"00111"`, `"11100"`

Total: 5.

### Example 2

**Input**
```
1
5
2000
2000
```

**Output**
```
0
```

**Explanation**

Both block sizes are larger than every length in `[1, 5]`, so no good string exists.
