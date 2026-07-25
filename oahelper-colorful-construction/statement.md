# Colorful Construction

You have **r** red blocks and **b** blue blocks for building a colorful monument.

Rules:

- A monument of height **h** has floors of sizes **h, h−1, …, 1** (top floor has 1 block).
- Each floor must be entirely one color (all red or all blue).
- Unused blocks may remain.

Let **h** be the maximum height achievable with the available blocks (i.e. the largest **h** with \(h(h+1)/2 \le r+b\)).

Count the number of distinct colorings of the floors of a height-**h** monument that do not exceed the red/blue budgets. Two monuments differ if some floor has different colors. Output the count modulo \(10^9+7\).

## Input Format

A single line with two integers **r** and **b**.

## Output Format

A single integer: the number of valid height-**h** monuments modulo \(10^9+7\).

## Constraints

- \(0 \le r, b \le 2 \cdot 10^5\)
- \(r + b \ge 1\)

## Examples

### Example 1

**Input**
```
4 6
```

**Output**
```
2
```

Maximum height is 4 (needs 10 blocks). Exactly two valid colorings exist.

### Example 2

**Input**
```
9 7
```

**Output**
```
6
```
