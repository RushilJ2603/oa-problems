# Max K XOR Sum

You are given an array \(A\) of \(N\) non-negative integers, an integer \(K\), and an integer \(X\).

In one operation you choose an index \(i\) and replace \(A[i]\) with \(A[i] \oplus X\) (bitwise XOR). You may perform this operation **at most \(K\) times**. Applying the operation twice on the same index cancels out, so each index is worth operating on **at most once**.

Maximize the sum of all array elements after at most \(K\) operations.

## Input

- Line 1: integer \(N\)
- Line 2: integer \(K\)
- Line 3: integer \(X\)
- Each of the next \(N\) lines: integer \(A[i]\)

## Output

Print a single integer — the maximum achievable sum.

## Constraints

- \(1 \le N \le 10^5\)
- \(0 \le K \le 10^5\)
- \(0 \le X \le 10^5\)
- \(0 \le A[i] \le 10^9\)

## Examples

### Example 1

**Input**
```
3
1
3
1
2
3
```

**Output**
```
7
```

**Explanation.** \(1 \oplus 3 = 2\) (gain \(+1\)). With \(K=1\), sum becomes \(7\).

### Example 2

**Input**
```
3
5
5
10
20
30
```

**Output**
```
65
```

**Explanation.** Only \(10 \oplus 5 = 15\) helps. Sum becomes \(65\).

### Example 3

**Input**
```
3
2
1
5
6
7
```

**Output**
```
19
```

**Explanation.** Only \(6 \oplus 1 = 7\) helps. Sum becomes \(19\).
