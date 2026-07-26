# Balanced Security Groups

A private cloud network has `n` servers. The protection level required by the `i`-th server is given by `security[i]`. You must split the servers into security groups under two rules:

1. Every server placed in the **same** group must require the **same** protection level.
2. The number of servers in any two groups may differ by **at most 1**. Globally, there must exist some integer `s` such that every group has size exactly `s` or `s + 1`.

Return the **minimum** number of groups needed to cover all servers while respecting both rules.

## Input Format

- The first line contains an integer `n`, the number of servers.
- Each of the next `n` lines contains an integer `security[i]`.

## Output Format

Print a single integer: the minimum number of groups required.

## Constraints

- \(1 \le n \le 10^5\)
- \(1 \le security[i] \le 10^5\)

## Examples

### Example 1

**Input**
```
5
1
7
7
7
1
```

**Output**
```
2
```

**Explanation**

Frequencies are grade `1` twice and grade `7` three times. One optimal grouping uses base size `s = 2`:

- Group 1: 3 servers of grade 7
- Group 2: 2 servers of grade 1

This uses 2 groups, and no valid plan uses fewer.

### Example 2

**Input**
```
11
2
3
3
2
2
3
2
2
2
2
3
```

**Output**
```
3
```

**Explanation**

There are 7 servers of grade `2` and 4 of grade `3`. With base size `s = 3`:

- Group 1: 4 servers of grade 2
- Group 2: 3 servers of grade 2
- Group 3: 4 servers of grade 3

Total: 3 groups.
