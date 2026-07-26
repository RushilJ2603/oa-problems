# Domino Coloring in Warehouse Automation

In a warehouse automation system, robotic movement paths are modeled with domino-like tiles on a $2 \times n$ grid.

You are given two strings of equal length $n$. Treat the first string as the top row and the second as the bottom row. Each character appears exactly twice and marks one domino. The strings always describe a complete tiling:

- A **vertical** domino sits in column $i$ when the two characters in that column are equal.
- A pair of **horizontal** dominoes covers columns $i$ and $i+1$ when the top characters in those columns match each other and the bottom characters match each other.

Two dominoes are adjacent if they share a side (up, down, left, or right). Diagonal contact does not count.

Each domino may be painted with one of three colors: Red, Green, or Blue. Both halves of a domino must share the same color, and adjacent dominoes must use different colors.

Count the number of valid colorings modulo $10^9+7$.

## Input Format

- Line 1: string `top` (length $n$)
- Line 2: string `bottom` (length $n$)

## Output Format

Print a single integer — the number of valid colorings modulo $10^9+7$.

## Constraints

- $1 \le n \le 10^5$
- Both strings contain only English letters (`a`–`z`, `A`–`Z`)
- The input always describes a valid complete tiling

## Examples

### Example 1

Input:
```
xy
xy
```

Output:
```
6
```

Explanation: Two vertical dominoes side by side. The first has 3 color choices; the second has 2. Total $3 \times 2 = 6$.

### Example 2

Input:
```
aacx
ddcx
```

Output:
```
12
```

Explanation: Horizontal pair on columns 0–1, then two verticals. Valid colorings: 12.

### Example 3

Input:
```
a
a
```

Output:
```
3
```
