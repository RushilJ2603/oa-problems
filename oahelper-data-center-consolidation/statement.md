A ride-hailing company is rearranging its server systems to reduce latency. Resources are currently distributed across `n` data centers and must be consolidated into **at most `k`** data centers. The cost of migrating all services from data center `i` to data center `j` is `migrationCost[i][j]`.

Determine the minimum total migration cost required to achieve this consolidation.

**Rules**

- Data centers are numbered from `0` to `n − 1`.
- Services may be migrated **indirectly** through intermediate data centers; the cost of emptying `i` into `j` is the cheapest multi-hop route from `i` to `j` (sum of edge costs along a directed path). The given matrix need not satisfy the triangle inequality and need not be symmetric.
- Choose a non-empty set `S` of keepers with `|S| ≤ k`. Every data center not in `S` migrates (possibly via intermediates) to its cheapest keeper in `S`. The total cost is the sum of those migration costs. Keepers pay nothing.
- After consolidation, at most `k` data centers contain services.

### Input Format

The first line contains two integers `n` and `k`. Each of the next `n` lines contains `n` space-separated integers; the `j`-th value on the `i`-th line is `migrationCost[i][j]`.

### Output Format

Print a single integer — the minimum possible total cost.

### Constraints

- \(1 \le n \le 18\)
- \(1 \le k \le n\)
- \(0 \le \mathrm{migrationCost}[i][j] \le 10^5\)
- \(\mathrm{migrationCost}[i][i] = 0\)

### Example 1

Input:
```
4 3
0 9 5 3
7 0 7 8
6 4 0 5
8 6 4 0
```

Output:
```
3
```

Explanation: Migrate data center 0 to data center 3 at cost 3. Services remain in centers 1, 2, and 3 (`k = 3`).

### Example 2

Input:
```
4 2
0 2 2 2
2 0 2 2
2 2 0 2
2 2 2 0
```

Output:
```
4
```

Explanation: Migrate center 1 to 3 (cost 2) and center 2 to 0 (cost 2). Only centers 0 and 3 remain active; total cost 4.
