# Dead Pod Recovery

A cloud computing system contains pods numbered from $1$ to $pods$, distributed across multiple geographical regions. The pods are interconnected by $n$ links, given in a list `connections`. Pods belong to the same region if they are connected directly or indirectly (a region is a connected component of pods).

Each pod continuously writes critical data to a central database. However, sometimes a pod loses its connection to the database. If a pod loses its database connection:
- It forwards its data to the active pod with the **smallest ID** in its same region.
- If no active pods remain in the region, the data cannot be written and an error is logged.

You need to process $q$ queries of two types sequentially:
1. `1 pod_id`: A data-sending query. The given pod needs to send data. If it has lost its database connection, it delegates to the active pod with the lowest ID in its region. You must return the ID of the pod that ultimately writes the data. If no pods in the region are active, return `-1`.
2. `2 pod_id`: A database-connection-failure query. The given pod permanently loses its connection to the database.

Return an array containing the results of all type `1` queries in the order they were processed.

### Input Format

- The first line contains an integer, `pods`.
- The next line contains an integer, `n`, the number of links.
- The next line contains an integer `2` (the number of columns per link).
- The next $n$ lines each contain two integers, representing a connection between two pods.
- The next line contains an integer, `q`, the number of queries.
- The next line contains an integer `2` (the number of columns per query).
- The next $q$ lines each contain two integers, representing a query (`type` and `pod_id`).

### Output Format

Print the result of each type `1` (data-sending) query, one per line. If a message cannot be sent because the entire region is inactive, print `-1`.

### Constraints

- $1 \le pods \le 10^5$
- $0 \le n \le 10^5$
- $1 \le q \le 2 \times 10^5$
- $1 \le connections[i][0], connections[i][1] \le pods$
- $queries[i][0] \in \{1, 2\}$
- $1 \le queries[i][1] \le pods$
- There is at least 1 query of type 1.

### Example 1

**Input:**
```
2
1
2
1 2
1
2
1 2
```

**Output:**
```
2
```

**Explanation:**
- Pods are 1 and 2, and they are connected.
- Query 1: `1 2` (data-sending query from pod 2). Pod 2 is still active, so it writes the data directly. Result is `2`.

### Example 2

**Input:**
```
4
4
2
1 2
2 3
1 4
4 3
4
2
2 3
1 3
2 1
1 1
```

**Output:**
```
1
2
```

**Explanation:**
All 4 pods are in the same region.
- Query 1: `2 3` (pod 3 loses its connection).
- Query 2: `1 3` (data-sending query from pod 3). Pod 3 has lost its connection, so it sends the message via the active pod with the lowest ID in the region, which is pod 1. Result is `1`.
- Query 3: `2 1` (pod 1 loses its connection).
- Query 4: `1 1` (data-sending query from pod 1). Since pod 1 has lost its connection, it sends the message via the lowest ID active pod in the region, which is now pod 2. Result is `2`.
