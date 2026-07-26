# Cost of Groups

A logistics firm models its warehouses as an undirected **tree** with **N** nodes. Each warehouse **i** holds a stock value **A_i**. Management wants to partition the warehouses into **as few groups as possible** so that no two warehouses that share a direct road belong to the same group.

For any group **G**, consider pairing warehouses inside **G**. The value of a pair *(u, v)* is **|A_u − A_v|**. The **cost** of group **G** is the maximum sum you can obtain by pairing nodes of **G**, where each node is used in at most one pair (some nodes may remain unpaired).

Compute the sum of the costs of all groups in the partition.

## Input Format

- The first line contains an integer **T** — the number of test cases.
- For each test case:
  - The first line contains an integer **N** — the number of nodes.
  - The second line contains **N** space-separated integers **A_1, A_2, …, A_N**.
  - The next **N − 1** lines each contain two integers **U** and **V** describing an edge.

## Output Format

For each test case, print a single integer — the sum of group costs — on its own line.

## Constraints

- 1 ≤ T ≤ 10
- 1 ≤ N ≤ 10^5
- 1 ≤ A_i ≤ 10^9
- 1 ≤ U, V ≤ N
- The given edges always form a tree.
- The answer may exceed the range of a 32-bit signed integer; use 64-bit integers.

## Examples

### Example 1

**Input**
```
1
5
12 17 14 13 16
1 2
1 3
1 5
2 4
```

**Output**
```
4
```

**Explanation**

A tree is bipartite, so two groups suffice and the split is forced: nodes 1 and 4 in one group, nodes 2, 3 and 5 in the other.

- Group {1, 4} has values {12, 13}. Pairing them gives |13 − 12| = 1.
- Group {2, 3, 5} has values {17, 14, 16}. The best single pair is (17, 14), giving 3, and one node stays unpaired.

The sum of the costs is 1 + 3 = 4.

### Example 2

**Input**
```
1
1
7
```

**Output**
```
0
```

**Explanation**

A single node forms one group of size 1. No pair is possible, so the cost is 0.

### Example 3

**Input**
```
1
3
1 2 3
1 2
2 3
```

**Output**
```
2
```

**Explanation**

The path forces groups {1, 3} with values {1, 3} and {2} with value {2}. The first group contributes |3 − 1| = 2; the second contributes 0. Total = 2.
