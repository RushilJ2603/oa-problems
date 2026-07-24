# Beautiful Arrangement

Count the number of permutations `p` of the integers `1, 2, …, n` (using **1-based** indexing)
such that for **every** position `i`, at least one of the following holds:

- `p[i] % i == 0`  (the value is divisible by its position), or
- `i % p[i] == 0`  (the position is divisible by the value).

## Input
A single integer `n`.

## Output
A single integer — the number of such permutations.

## Constraints
- `1 ≤ n ≤ 15`

## Example 1
Input:
```
2
```
Output:
```
2
```
Both permutations qualify: `[1,2]` (1%1=0, 2%2=0) and `[2,1]` (2%1=0, 1 divides 2).

## Example 2
Input:
```
3
```
Output:
```
3
```
