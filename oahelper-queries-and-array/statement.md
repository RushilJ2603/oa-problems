# Balance the Workloads

Your team maintains **N** servers. Each server *i* currently handles **A[i]** request units per second, but it must never drop below a contractual floor of **B[i]** units. Moving load is done with a special rebalance operation:

- Choose any two servers *i* and *j*.
- Increase **A[i]** by 1 and decrease **A[j]** by 1.
- The operation is allowed only if **A[j] > B[j]** before the move.
- Each unit removed from server *j* costs **C[j]** (billing for that machine).

You may apply the operation any number of times (including zero). The total sum of all **A[i]** never changes.

After rebalancing, define the **throughput** of the fleet as the **minimum** value among all **A[i]**. Your goals are:

1. Maximize this throughput (the largest possible minimum you can achieve).
2. Among all ways to reach that maximum, minimize the total cost spent on operations. Print the cost modulo **1 000 000 007**.

## Input

- The first line contains an integer **T** — the number of test cases.
- For each test case:
  - One line with **N**.
  - One line with **N** integers **A[1..N]**.
  - One line with **N** integers **B[1..N]**.
  - One line with **N** integers **C[1..N]**.

## Output

For each test case, print two integers separated by a space: the maximum achievable minimum throughput, and the minimum total cost to achieve it (modulo 10^9 + 7).

## Constraints

- 1 ≤ T ≤ 10^5
- 1 ≤ N ≤ 10^5
- 1 ≤ A[i], B[i], C[i] ≤ 10^9
- B[i] ≤ A[i] for every *i*
- The sum of **N** over all test cases ≤ 2 × 10^5

Only the **cost** is taken modulo 10^9 + 7; the maximum minimum is printed as an ordinary integer.

## Example 1

**Input**

```
1
5
1 2 2 3 3
1 2 1 2 1
1 2 1 4 3
```

**Output**

```
2 3
```

**Explanation:** Move one unit from server 5 to server 1 (cost **C[5] = 3**). Every server ends at least at 2, and no arrangement can push the fleet minimum above 2 while respecting all floors.

## Example 2

**Input**

```
1
4
1 99 2 99
1 97 2 98
1 5 2 2
```

**Output**

```
3 12
```

**Explanation:** Two units leave server 2 (cost 5 each) and one unit leaves server 4 (cost 2). The final loads are `[3, 97, 3, 98]`, so the minimum is 3. Total cost is 10 + 2 = 12.

## Example 3

**Input**

```
1
1
7
3
5
```

**Output**

```
7 0
```

**Explanation:** With a single server, nothing can be moved; the minimum stays 7 and no cost is paid.
