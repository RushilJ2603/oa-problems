# Zone Traffic Clusters

A city dispatch system partitions *n* zones by traffic signature. Two zones belong to the same cluster when the GCD of their signatures is greater than 1. Membership is transitive: if A shares a factor with B and B shares a factor with C, then A, B, and C are one cluster (even if gcd(A, C) = 1).

Given the list of signatures, output for every zone the size of the cluster that contains it.

## Input Format

- Line 1: integer *n* — number of zones
- Next *n* lines: integers `signature[0]`, …, `signature[n-1]`

## Output Format

*n* lines — for each zone *i* (0-based order), the size of its cluster.

## Constraints

- \(1 \le n \le 10^5\)
- \(1 \le signature[i] \le 10^5\)

## Examples

### Example 1

**Input:**
```
3
1
2
4
```

**Output:**
```
1
2
2
```

Zone 0 has signature 1 (isolated). Zones 1 and 2 share factor 2, so they form a cluster of size 2.

### Example 2

**Input:**
```
3
3
3
3
```

**Output:**
```
3
3
3
```

Every pair has GCD 3, so all three zones are one cluster.

### Example 3

**Input:**
```
5
2
3
6
1
5
```

**Output:**
```
3
3
3
1
1
```

Zones 0–2 connect through shared factors of 6; zones 3 and 4 (signatures 1 and 5) are alone.
