# Burst Balloons

`nums[i]` is the number on balloon `i`. Bursting balloon `i` yields `nums[i-1]*nums[i]*nums[i+1]` coins (treat out-of-range neighbours as 1); the burst balloon is removed. Print the maximum coins from bursting all balloons.

## Input
- Line 1: `n`.
- Line 2: `n` integers `nums[i]`.

## Output
A single integer: the maximum coins obtainable.

## Constraints
- `1 <= n <= 300`
- `1 <= nums[i] <= 100`

## Examples
```
Input:
4
3 1 5 8
Output:
167
```
