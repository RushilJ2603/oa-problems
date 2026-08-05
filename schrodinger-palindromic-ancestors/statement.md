A tree has `n` nodes labelled `0` to `n-1`, and is rooted at node `0`. Every node carries one
lowercase English letter.

The edges are given as two arrays, `treeFrom` and `treeTo`, of length `n-1`: the `i`-th edge joins
`treeFrom[i]` and `treeTo[i]`. **The pair is an unordered edge** — it is not guaranteed that the
first endpoint is the parent, and reading it either way describes the same tree. The tree is rooted
at node `0`.

For a query node `u`, walk from `u` up towards the root. For every node `v` on that walk (including
`u` itself and including node `0`), look at the letters written on the nodes of the path from `u` to
`v`. If those letters can be **rearranged into a palindrome**, the query scores one point.

Print the total score for each query.

> A multiset of letters can be rearranged into a palindrome exactly when at most one letter occurs
> an odd number of times.

Read the input from STDIN and print the output to STDOUT. Do not print anything else.

**Input Format:**
- The first line contains an integer `n`, the number of nodes.
- The second line contains `n-1` integers — the array `treeFrom`. (When `n = 1` this line is empty.)
- The third line contains `n-1` integers — the array `treeTo`. (When `n = 1` this line is empty.)
- The fourth line contains a string of `n` lowercase letters; its `i`-th character is the letter on
  node `i`.
- The fifth line contains an integer `q`, the number of queries.
- The next `q` lines each contain one integer — a query node.

**Output Format:** `q` lines. The `i`-th line is the score of the `i`-th query.

**Constraints:**
- `1 <= n <= 200000`
- `1 <= q <= 200000`
- `0 <= treeFrom[i], treeTo[i] <= n-1`, and the `n-1` edges form a tree
- every query node is in `[0, n-1]`
- letters are lowercase English letters (`a`–`z`)

**Sample Input 1:**
```
4
0 0 2
1 2 3
zabb
1
3
```
**Sample Output 1:**
```
3
```
**Explanation 1:** Node `0` (letter `z`) has children `1` (letter `a`) and `2` (letter `b`), and
node `2` has child `3` (letter `b`). Walking up from node `3`:

- `v = 3`: the path is just `b` — a palindrome.
- `v = 2`: the path is `b`, `b` — `bb` is a palindrome.
- `v = 0`: the path is `b`, `b`, `z` — rearranged, `bzb` is a palindrome.

All three score, so the answer is `3`.

**Sample Input 2:**
```
4
1 2 3
0 0 2
zabb
4
0
1
2
3
```
**Sample Output 2:**
```
1
1
1
3
```
**Explanation 2:** The same tree, with every edge written the other way round — the pairs are
unordered, so the tree and the answers are unchanged. Node `1` scores only for itself: the path from
`1` to `0` spells `az`, which has two letters occurring an odd number of times and cannot be
rearranged into a palindrome.
