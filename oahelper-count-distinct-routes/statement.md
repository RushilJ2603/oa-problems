Picture a city split into zones numbered `0` through `n`. A rideshare driver follows a fixed sequence of navigation instructions, where

- `'l'` = move one zone left (toward a lower-numbered zone),
- `'r'` = move one zone right (toward a higher-numbered zone).

How many **distinct subsequences** of the driver's navigation plan let the driver start at zone `start_zone` and end at zone `end_zone`? Report the count modulo \(10^9 + 7\).

**Rules**

- A subsequence is formed by deleting zero or more steps without changing the order of the remaining steps.
- Two subsequences count as the **same** if they are the same string of instructions, even when taken from different index sets. Example: in `"rrl"`, both ways of forming `"rl"` count once.
- From position `j`, `'l'` goes to `j - 1` and `'r'` goes to `j + 1`.
- Every intermediate position of a valid subsequence must stay inside `0 .. n` (inclusive). Leaving the city at any step invalidates that subsequence.
- The empty subsequence is valid precisely when `start_zone == end_zone`.

### Input Format

- Line 1: the string `plan` (characters `l` and `r` only).
- Line 2: the integer `n` (upper bound of the number line).
- Line 3: the integer `start_zone`.
- Line 4: the integer `end_zone`.

### Output Format

Print a single integer: the number of distinct valid subsequences modulo \(10^9 + 7\).

### Constraints

- \(1 \le |plan| \le 10^3\)
- \(0 \le start\_zone, end\_zone \le n \le 2500\)

### Example 1

Input:
```
rrlrlr
6
1
2
```

Output:
```
7
```

Explanation: The seven distinct subsequences are `"r"`, `"rrl"`, `"rlr"`, `"lrr"`, `"rrlrl"`, `"rlrlr"`, and `"rrllr"`.

### Example 2

Input:
```
rrlrlr
6
1
3
```

Output:
```
5
```

Explanation: The five distinct subsequences are `"rr"`, `"rrlr"`, `"rlrr"`, `"rrrl"`, and `"rrlrlr"`.

### Example 3

Input:
```
rrrlrr
7
0
0
```

Output:
```
2
```

Explanation: The empty subsequence and `"rl"` (path `0 → 1 → 0`). Note `"lr"` is invalid from zone 0 because the first `'l'` would leave the city.
