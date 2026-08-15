# Consistent Data

A sequence containing only `0`s and `1`s is called a **consistent sequence** if no adjacent values in the sequence are the same. For example, `(0, 1, 0, 1, 0, 1)` is a consistent sequence while `(0, 1, 1)` is not.

You are given an integer $N$ that represents the size of a consistent sequence starting with `0`.

Find the number of consistent subsequences of the given sequence modulo $10^9 + 7$.

**Note:** A subsequence is a sequence that can be derived from the given sequence by deleting zero or more elements without changing the order of the remaining elements.

### Input Format
- The first line contains an integer $N$ representing the sequence's size.

### Output Format
- Print the number of consistent subsequences modulo $10^9 + 7$.

### Constraints
- $1 \le N \le 10^6$

### Examples

**Example 1**
```
Input:
3

Output:
6
```
*Explanation:* The sequence of size 3 starting with `0` is `010`. The 6 consistent subsequences are `0`, `1`, `0` (the second one), `01`, `10`, and `010`.

**Example 2**
```
Input:
1

Output:
1
```
*Explanation:* The sequence is `0`. There is only 1 non-empty consistent subsequence: `0`.
