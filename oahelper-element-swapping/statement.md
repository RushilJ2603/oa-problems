# Element Swapping

A logistics team scores packing lanes by a weighted sum. Lane `i` (0-based) contributes `arr[i] * (i + 1)` to the total strength.

You may rearrange the array by swapping adjacent elements, with one hard rule: **each element may participate in at most one swap**. So you choose a set of **non-overlapping** adjacent pairs `(i, i+1)` and swap each pair; since the pairs share no position, no element moves more than one step from its start.

(Equivalently: if you label each swap by its left position, then two chosen swaps `i` and `j` must satisfy `|i - j| ≥ 2` — because a single swap already occupies positions `i` and `i+1`. This is a rule about *different* swaps not overlapping; the two elements inside one swap are, of course, adjacent.)

Find the maximum total strength achievable after an optimal (possibly empty) set of swaps.

## Input Format

The first line contains a single integer `n` — the length of the array.

The second line contains `n` space-separated integers `arr[0], arr[1], …, arr[n-1]`.

## Output Format

Print a single integer — the maximum possible total strength.

## Constraints

- `1 ≤ n ≤ 10^5`
- `1 ≤ arr[i] ≤ 10^9`
- The answer fits in a signed 64-bit integer.

## Examples

### Example 1

Input:
```
4
2 1 4 3
```

Output:
```
30
```

Explanation: Swap indices `(0,1)` and `(2,3)` to obtain `[1, 2, 3, 4]`. Strength = `1·1 + 2·2 + 3·3 + 4·4 = 30`.

### Example 2

Input:
```
5
1 9 7 3 2
```

Output:
```
66
```

Explanation: Swap indices `(2,3)` to obtain `[1, 9, 3, 7, 2]`. Strength = `66`.

### Example 3

Input:
```
3
1 2 5
```

Output:
```
20
```

Explanation: No swap helps. Strength = `1·1 + 2·2 + 5·3 = 20`.

### Example 4

Input:
```
1
7
```

Output:
```
7
```
