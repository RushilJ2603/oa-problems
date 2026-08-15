# Balanced Nodes in a Binary Tree

A binary tree made of $N$ nodes is given. A node in this tree is called a **Balanced Node** if the sum of one subtree (either left or right) of the node is even, and the sum of the other subtree is odd. Nodes having only one or no child nodes can never be Balanced Nodes.

The tree is represented as a series of relationships of each node to the Root node such as `L`, `R`, `LL`, `LR`, and so on, where each node is left (`L`) to Root, or left-left (`LL`) to Root, and so on.

Write a program to find all the Balanced Nodes in the tree, and output the sum of their values.

### Input Format

- The first line of input contains $N$, the number of nodes explicitly given.
- The second line of input contains the value of the Root node.
- The next $N-1$ lines of input contain a string $S$, and an integer $X$, separated by a single white space, where $X$ is the value of a node in the tree and $S$ is the relation (path) between the Root node and this node.

### Output Format

Output a single integer representing the sum of the values of all the Balanced Nodes in the tree.

### Constraints

- $3 \le N \le 100$
- $0 \le \text{Value of each node} \le 10^{12}$

### Examples

#### Example 1

**Input:**
```
9
11
L 23
R 44
LL 13
LR 9
RL 22
RR 7
RLL 6
RLR 15
```

**Output:**
```
33
```

**Explanation:**
The tree nodes with no children cannot be Balanced Nodes (13, 9, 6, 15, 7).
For node 11: Sum of left sub-tree = 23+13+9 = 45 (odd) and Sum of right sub-tree = 44+22+7+6+15 = 94 (even). 11 is a Balanced Node.
For node 23: Sum of left sub-tree = 13 (odd) and Sum of right sub-tree = 9 (odd). 23 is not a Balanced Node.
For node 44: Sum of left sub-tree = 22+6+15 = 43 (odd) and Sum of right sub-tree = 7 (odd). 44 is not a Balanced Node.
For node 22: Sum of left sub-tree = 6 (even) and Sum of right sub-tree = 15 (odd). 22 is a Balanced Node.
Sum of Balanced Nodes = 11+22 = 33.

#### Example 2

**Input:**
```
7
12
L 17
R 16
RL 4
RR 9
RLL 2
RLR 3
```

**Output:**
```
16
```

**Explanation:**
The Balanced Nodes are 12 and 4. The sum of their values is 12 + 4 = 16.
