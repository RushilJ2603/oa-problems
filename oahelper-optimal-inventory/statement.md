The manager of a large warehouse wants to reorganize inventory. There are `n` products in a line; the quality of the `i`-th product is `quality[i]`.

An inventory is **optimal** when every quality value that still appears forms a single contiguous block (all occurrences of each remaining quality are consecutive).

To reach an optimal inventory, the manager may repeatedly:

1. Choose two quality values `x` and `y`.
2. Replace **every** product of quality `x` with quality `y`.
3. Pay a cost equal to the number of products whose quality changed.

Find the minimum total cost to make the inventory optimal.

**Notes**

- Quality values may be negative (poor quality).
- Replacing `x` with `y` changes all occurrences of `x` globally, not just a contiguous segment.
- Qualities that never need to merge across gaps may stay as they are at cost 0.

### Input Format

- The first line contains an integer `n`.
- The next `n` lines each contain one integer `quality[i]`.

### Output Format

Print a single integer — the minimum cost.

### Constraints

- \(1 \le n \le 2 \cdot 10^5\)
- \(-10^9 \le quality[i] \le 10^9\)

### Example 1

Input:
```
5
1
2
1
2
1
```

Output:
```
2
```

Explanation: Replace every `2` with `1` to get `[1,1,1,1,1]` at cost 2.

### Example 2

Input:
```
11
10
6
10
-3
1
1
4
-4
-1
1
-7
```

Output:
```
4
```

Explanation: One optimal sequence of replacements costs \(1+1+1+1 = 4\) and yields contiguous blocks for each remaining quality.
