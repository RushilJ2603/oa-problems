Amazon Web Services has $n$ servers. The cache optimization power of the $i$-th server is $\text{power}[i]$. 

The cache optimization power of a group of contiguous servers (from index $l$ to $r$, inclusive) is defined as:

$$\text{Power}[l, r] = \left(\min_{l \le i \le r} \text{power}[i]\right) \times \left(\sum_{i=l}^r \text{power}[i]\right)$$

Find the sum of $\text{Power}[l, r]$ for all possible contiguous groups of servers (i.e. all possible pairs $(l, r)$ such that $0 \le l \le r < n$). Since the answer can be very large, return it modulo $10^9 + 7$.

### Input Format
The first line contains an integer $n$, the number of servers.
The following $n$ lines each contain an integer representing $\text{power}[i]$.

### Output Format
Print a single integer, the total cache optimization power of all contiguous groups modulo $10^9 + 7$.

### Constraints
- $1 \le n \le 10^5$
- $1 \le \text{power}[i] \le 10^9$

### Example 1
**Input**
```
4
2
3
2
1
```

**Output**
```
69
```

### Example 2
**Input**
```
3
2
1
3
```

**Output**
```
27
```
