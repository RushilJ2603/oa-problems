# Node Disconnection

A compromised communication network is a line of nodes, each labelled with a lowercase English letter. In one operation you may disconnect **any contiguous group of nodes that share the same letter** (one or more adjacent identical letters). After a group is removed, the nodes on either side become adjacent and may form new groups later.

Find the **minimum** number of operations needed to disconnect every node.

Clarifying rule: removals may create new adjacencies. For example, in `aabbaa`, removing the middle `bb` leaves `aaaa`, which can then be removed in one more operation — total **2**, not 3.

## Input Format

- A single line containing the string `series` of lowercase English letters.

## Output Format

- A single integer: the minimum number of operations to clear the entire series.

## Constraints

- \(1 \le |series| \le 500\)
- `series` contains only lowercase English letters (`a`–`z`).

## Examples

### Example 1

**Input**
```
abaca
```

**Output**
```
3
```

**Explanation.** Delete `b` and `c` first (two operations), leaving `aaa`, which is deleted in one more operation.

### Example 2

**Input**
```
aabbaa
```

**Output**
```
2
```

**Explanation.** Delete `bb`, then the remaining `aaaa` in one operation.

### Example 3

**Input**
```
a
```

**Output**
```
1
```
