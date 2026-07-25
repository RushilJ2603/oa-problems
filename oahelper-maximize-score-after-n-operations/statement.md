# Maximize Score After N Operations

The trading desk at **UBS** is running a short calibration drill on a list of `2 * n` positive integers called `nums`. Analysts must perform exactly **n** pairing operations on this list.

In the **i-th** operation (1-indexed), an analyst:

- Chooses two remaining elements `x` and `y`.
- Adds `i * gcd(x, y)` to the team score.
- Removes `x` and `y` from the list.

Your task is to choose the sequence of pairings that **maximizes** the final score after all `n` operations. Here `gcd(x, y)` denotes the greatest common divisor of `x` and `y`.

## Input Format

- Line 1: integer **M** (`M = 2 * n`) — the length of the array.
- Line 2: **M** space-separated integers — the elements of `nums`.

## Output Format

Print a single integer — the maximum achievable score.

## Constraints

- \(1 \le n \le 7\)
- `nums.length == 2 * n`
- \(1 \le nums[i] \le 10^6\)

## Examples

### Example 1

**Input:**
```
2
1 2
```

**Output:**
```
1
```

Only one operation is possible: `1 * gcd(1, 2) = 1`.

### Example 2

**Input:**
```
4
3 4 6 8
```

**Output:**
```
11
```

One optimal plan: `1 * gcd(3, 6) + 2 * gcd(4, 8) = 3 + 8 = 11`.

### Example 3

**Input:**
```
6
1 2 3 4 5 6
```

**Output:**
```
14
```

One optimal plan: `1 * gcd(1, 5) + 2 * gcd(2, 4) + 3 * gcd(3, 6) = 1 + 4 + 9 = 14`.
