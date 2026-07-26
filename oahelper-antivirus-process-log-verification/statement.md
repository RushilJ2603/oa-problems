# Antivirus Process Log Verification

An antivirus product records every process that starts on a machine. Processes form a hierarchy: each process may launch child processes, and a child can appear in the log only after its parent has already been logged. There are no cycles. Process **1** is the bootstrap process — it always starts first.

## How a valid log is built

1. Enqueue process 1 into a FIFO queue.
2. While the queue is not empty:
   - Dequeue the front process and append it to the log.
   - Enqueue **all** of its still-unlogged children (in any order).

Because children may be enqueued in any order, one hierarchy can produce many different valid logs. A log is valid if and only if it could arise from this procedure for some choice of child-enqueue orders at every step.

## Task

You are given `n` processes (numbered `1..n`) and `n-1` undirected edges describing the parent–child tree (root is always process 1 after orienting edges away from 1). Then you are given `q` candidate log orders. For each candidate, decide whether it is a valid log of the hierarchy.

Build a string of length `q` where the `i`-th character is `1` if the `i`-th candidate is valid, and `0` otherwise.

A candidate is **not** guaranteed to be a permutation of `1..n` — duplicates and missing process IDs must be rejected.

## Input Format

- Line 1: integer `n` — number of processes.
- Next `n-1` lines: two integers `u v` — an undirected edge of the tree.
- Next line: integer `q` — number of queries.
- Next `q` lines: each contains `n` integers — one candidate log order.

When `n = 1` there are no edge lines.

## Output Format

Print a single string of length `q` consisting of characters `0` and `1`.

## Constraints

- `1 ≤ n ≤ 2·10^5`
- `1 ≤ u, v ≤ n`
- `1 ≤ q ≤ 10^4`
- `1 ≤` each entry of a query `≤ n`
- `q · n ≤ 10^6`
- The edges form a tree on `n` nodes.

## Examples

### Example 1

**Input**
```
4
1 2
1 3
4 3
4
1 3 2 4
1 2 4 3
1 2 2 3
4 2 1 3
```

**Output**
```
1000
```

**Explanation**

Hierarchy: `1 → 2`, `1 → 3`, `3 → 4`.

- `1 3 2 4` is a valid BFS-style log (children of 1 enqueued as 3 then 2).
- `1 2 4 3` is invalid — process 4 cannot appear before its parent 3.
- `1 2 2 3` is not a permutation.
- `4 2 1 3` does not start with bootstrap process 1.

### Example 2

**Input**
```
3
1 2
2 3
3
1 2 3
1 3 2
2 1 3
```

**Output**
```
100
```

**Explanation**

The only valid order is the chain `1 → 2 → 3`. Putting 3 before 2, or not starting at 1, is invalid.
