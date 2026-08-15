A disk stores hierarchical data in an undirected tree with `tree_nodes` nodes numbered from $0$ to $tree\_nodes - 1$, rooted at node 0. Each node has a character value represented by an array named `arr`, where `arr[i]` is the character on the $i$-th node.

You are given an array `queries` of length $m$. For each query `queries[i]`, determine how many nodes $v$ (including `queries[i]`) exist on the path from `queries[i]` to the root, such that the letters on the nodes from `queries[i]` to $v$ can be arranged to form a palindrome.

Return an integer array of size $m$ with the answer to each query.

Note: A palindrome is a string that reads the same backward as forward. Examples of palindromes include "z", "aaa", "aba", and "abccba".

### Input Format
The first line contains two integers `tree_nodes` and `e` (the number of edges, which is `tree_nodes - 1`).
The next `e` lines each contain two integers $u$ and $v$ representing an edge between node $u$ and node $v$.
The next line contains an integer $C$, the number of characters (which equals `tree_nodes`).
The next $C$ lines each contain a single character, where the $i$-th line is the character for node $i$.
The next line contains an integer $m$, the number of queries.
The next $m$ lines each contain a single integer representing a query node.

### Output Format
Print $m$ lines. The $i$-th line should contain the answer for the $i$-th query.

### Constraints
- $1 \le tree\_nodes \le 10^5$
- $1 \le m \le 10^5$
- `arr` consists of lowercase English letters only.
- $0 \le tree\_from[i], tree\_to[i], queries[i] < tree\_nodes$

### Examples

**Example 1**

Input:
```
4 3
0 1
0 2
1 3
4
a
b
a
a
2
1
2
```

Output:
```
1
2
```

Explanation:
Consider for `queries[0] = 1`:
- $v = 1$. We can form the palindrome "b".
- $v = 0$. We cannot form a palindrome from characters 'a' and 'b' only.

Consider for `queries[1] = 2`:
- $v = 2$. We can form the palindrome "a".
- $v = 0$. We can form the palindrome "aa".

Hence, the answer is `[1, 2]`.

**Example 2**

Input:
```
7 6
0 1
1 2
2 3
2 4
4 5
4 6
7
a
b
c
a
c
b
c
3
6
5
3
```

Output:
```
3
4
1
```

Explanation:
Consider for `queries[0] = 6`:
- $v = 6$. We can form the palindrome "c".
- $v = 4$. We can form the palindrome "cc".
- $v = 2$. We can form the palindrome "ccc".
- For $v = 0$, we cannot form any palindrome.

Consider for `queries[1] = 5`:
- $v = 5$. We can form the palindrome "b".
- $v = 2$. We can form the palindrome "cbc".
- $v = 1$. We can form the palindrome "bccb".
- $v = 0$. We can form the palindrome "cbabc".

Consider for `queries[2] = 3`:
- $v = 3$. We can form the palindrome "a".

Hence, the answer is `[3, 4, 1]`.
