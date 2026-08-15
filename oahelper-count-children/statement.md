# Count Children

You are given a binary tree where the root node has a value $N$.
The rule to generate the children of any node with value $p$ is as follows:
- The left child has value $p - 1$.
- The right child has value $p - 2$.

A child is only generated if its value is $\ge 1$. If the value is less than 1, that child does not exist.

For example, if $N = 4$, the tree generated is:
```
        4
       / \
      3   2
     / \ /
    2  1 1
   /
  1
```

Your task is to find the total number of times the value $i$ appears in the tree, where $1 \le i \le N$.
Because the answer can be extremely large, return it as a string representing the exact integer value.

### Input Format
The first line of input contains an integer $N$.
The second line of input contains an integer $i$.

### Output Format
Print the total number of occurrences of the node value $i$ as a single integer string.

### Constraints
- $1 \le N \le 10^{18}$
- $1 \le i \le N$
- $N - i \le 2000$

### Example 1
**Input:**
```
4
1
```

**Output:**
```
3
```

**Explanation:**
Looking at the tree generated from root 4, the value 1 appears 3 times.

### Example 2
**Input:**
```
10
9
```

**Output:**
```
1
```

**Explanation:**
The value 9 only appears as the left child of the root 10.
