# Maximum XOR Elimination Score

A logistics team at Rippling maintains a list of `n` non-negative integer node IDs. They repeatedly merge pairs until a single ID remains, and they want the merge process that scores as high as possible.

You are given an array `arr` of `n` non-negative integers.

Repeat the following operation until only **one** element is left:

- Choose any two **different** positions holding the values `x` and `y`.
- Add `x XOR y` (bitwise exclusive OR) to your score.
- Remove **either** `x` or `y` from the array (you choose which one).

Exactly `n - 1` operations are performed. Print the **maximum** total score that can be obtained.

## Input

The first line contains a single integer `n`, the number of elements.

The second line contains `n` space-separated integers `arr[0], arr[1], …, arr[n-1]`.

## Output

Print a single integer — the maximum achievable score.

## Constraints

- `2 ≤ n ≤ 2000`
- `0 ≤ arr[i] ≤ 10^9`

## Examples

### Example 1

```
Input:
5
1 2 3 4 5

Output:
25
```

One optimal sequence:

- Pick 2 and 5, score += 7, remove 5 → `[1, 2, 3, 4]`
- Pick 3 and 4, score += 7, remove 3 → `[1, 2, 4]`
- Pick 2 and 4, score += 6, remove 2 → `[1, 4]`
- Pick 1 and 4, score += 5, remove 1 → `[4]`

Total: `7 + 7 + 6 + 5 = 25`.

### Example 2

```
Input:
2
0 0

Output:
0
```

### Example 3

```
Input:
6
8 4 2 1 16 32

Output:
191
```
