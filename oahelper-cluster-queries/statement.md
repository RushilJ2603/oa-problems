# Cluster Queries

In a Salesforce global infrastructure, there are customer support clusters numbered from `1` to `clusters`. These clusters are interconnected by `m` communication links, forming a support network. Two clusters belong to the same network if they are directly or indirectly connected through a series of communication links.

Each cluster has a case resolution system. If a cluster's system goes offline, it is permanently unavailable. Any cases assigned to the support network must be resolved by the **active** cluster in that network with the **lowest ID**. If no active clusters remain in the entire network, the case is considered unresolved (and we output `-1`).

You are given `q` queries of two types:
1. `1 cluster_id`: A case is assigned to the support network containing `cluster_id`. You must find the active cluster in that network with the lowest ID and output its ID.
2. `2 cluster_id`: The system at `cluster_id` goes offline.

Return a list of integers containing the results of all type 1 queries in order.

### Input Format
The first line contains an integer `clusters`, the number of clusters.
The second line contains an integer `m`, the number of links.
The next `m` lines each contain two integers `u` and `v`, representing a link between cluster `u` and cluster `v`.
The next line contains an integer `q`, the number of queries.
The next `q` lines each contain two integers `type` and `cluster_id`.

### Output Format
Print the answers to the type 1 queries, separated by space or newline.

### Constraints
- $1 \le clusters \le 10^5$
- $0 \le m \le 10^5$
- $1 \le q \le 10^5$
- $1 \le u, v, cluster\_id \le clusters$

### Example 1
**Input:**
```
3
2
1 2
2 3
5
1 1
2 2
1 3
2 1
1 2
```

**Output:**
```
1
1
3
```

**Explanation:**
- The network connects clusters 1, 2, and 3.
- Query 1: `1 1`. The active clusters in the network are 1, 2, 3. The minimum is 1. Output 1.
- Query 2: `2 2`. Cluster 2 goes offline.
- Query 3: `1 3`. The active clusters in the network are 1, 3. The minimum is 1. Output 1.
- Query 4: `2 1`. Cluster 1 goes offline.
- Query 5: `1 2`. The only active cluster in the network is 3. The minimum is 3. Output 3.

### Example 2
**Input:**
```
6
3
1 2
3 4
5 6
9
1 1
1 3
1 5
2 2
2 1
1 1
2 4
1 4
1 6
```

**Output:**
```
1
3
5
-1
3
5
```
