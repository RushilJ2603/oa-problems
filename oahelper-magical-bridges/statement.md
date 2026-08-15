In the kingdom of Algorithmia, there are **N** cities numbered from 1 to **N**, connected by **M** bidirectional roads. Each road has a certain travel time associated with it.

The kingdom also has **K** magical bridges. Each magical bridge connects two cities and has zero travel time.

You are a traveler starting from city 1 and want to reach city N. Find the minimum time required to travel from city 1 to city N. You can use any combination of regular roads and magical bridges.

### Input Format
- First line contains three space-separated integers **N**, **M**, and **K**.
- Next **M** lines each contain three integers **u**, **v**, **w** representing a road between cities **u** and **v** with travel time **w**.
- Next **K** lines each contain two integers **a**, **b** representing a magical bridge between cities **a** and **b**.

### Constraints
- 2 <= N <= 10^4
- 1 <= M <= 5 * 10^4
- 0 <= K <= 10
- 1 <= u, v, a, b <= N
- 1 <= w <= 10^6

### Output Format
- Print a single integer - the minimum time to reach city N from city 1.
- If it is impossible to reach city N, print -1.

### Examples

**Example 1**
**Input:**
```
4 4 1
1 2 10
2 4 10
1 3 5
3 4 20
1 4
```
**Output:**
```
0
```

**Example 2**
**Input:**
```
4 4 1
1 2 10
2 4 10
1 3 5
3 4 20
2 3
```
**Output:**
```
15
```

**Example 3**
**Input:**
```
3 1 0
1 2 10
```
**Output:**
```
-1
```
