# Bit Propagation Through a Network

A **producer** computer (node **0**) is connected through one-way links to a network of **consumer**
computers, numbered `1 … n − 1`. The links form a **directed acyclic graph** (there are no cycles —
data can never loop back).

Data flows as follows:

- The producer **sends 2 bits** along every one of its outgoing links.
- Every other node **collects** all the bits arriving on its incoming links, then **forwards that
  total plus one extra bit** along each of its outgoing links.

A node with **no outgoing links** is an **end consumer**; it simply keeps everything that arrives.

Compute the **total number of bits collected by all end consumers**.

Formally, let `recv(v)` be the sum of the amounts carried by all links into `v`. Each link out of a
node `u` carries `send(u)`, where `send(0) = 2` and `send(u) = recv(u) + 1` for `u ≠ 0`. The answer is
`Σ recv(v)` over all sink nodes `v` (nodes with out-degree 0).

## Input Format

- Line 1: two integers **n** and **m** — the number of nodes and the number of directed links.
- Next **m** lines: two integers **u v**, a directed link `u → v`.

## Output Format

- A single integer — the total bits collected by all end consumers. It is guaranteed to fit in a
  signed 64-bit integer.

## Constraints

- `2 ≤ n ≤ 2000`
- `0 ≤ m ≤ 4000`
- The graph is a DAG; node 0 is the producer (it has no incoming links).

## Examples

### Example 1

**Input:**
```
3 2
0 1
1 2
```

**Output:**
```
3
```

Node 0 sends 2 to node 1. Node 1 received 2, so it forwards `2 + 1 = 3` to node 2. Node 2 is the only
end consumer and collected 3.

### Example 2

**Input:**
```
3 2
0 1
0 2
```

**Output:**
```
4
```

Both node 1 and node 2 receive 2 directly from the producer and are end consumers: `2 + 2 = 4`.

### Example 3

**Input:**
```
4 4
0 1
0 2
1 3
2 3
```

**Output:**
```
6
```

Nodes 1 and 2 each receive 2 and forward `2 + 1 = 3`. Node 3 (the only sink) collects `3 + 3 = 6`.
