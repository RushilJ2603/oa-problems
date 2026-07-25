# Maximum Array Sum with Subarray Flips

Your trading desk receives a signed scoreboard of `n` positions. You may reverse the sign of every entry in a contiguous window of the board. You are allowed to perform this window-negation operation at most `k` times. Overlapping windows are allowed, and each position's final sign is the result of stacking every negation that covered it (two flips cancel).

Compute the maximum possible sum of the board after at most `k` such operations.

## Input Format

- The first line contains an integer `n` — the length of the array.
- The second line contains an integer `k` — the maximum number of flip operations.
- Each of the next `n` lines contains one integer `a[i]` (0-indexed).

## Output Format

Print a single integer — the maximum achievable array sum.

## Constraints

- \(1 \le n \le 10^5\)
- \(1 \le k \le 10^5\)
- \(-10^9 \le a[i] \le 10^9\)

## Examples

### Example 1

**Input:**
```
5
2
-10
20
-30
40
-50
```

**Output:**
```
130
```

**Explanation:** With two flips, negate the single-element windows at indices 2 and 4: result `[-10, 20, 30, 40, 50]`, sum `130`.

### Example 2

**Input:**
```
3
1
10
20
30
```

**Output:**
```
60
```

**Explanation:** All values are already positive. Any flip reduces the sum, so leave the array unchanged.

### Example 3

**Input:**
```
4
3
-5
-3
2
-8
```

**Output:**
```
18
```

**Explanation:** Flip each of the three negative entries individually: `[5, 3, 2, 8]`, sum `18`.
