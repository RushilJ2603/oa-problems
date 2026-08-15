A coding competition organized to recruit software developers includes a problem involving the bitwise-OR operation.

The score of a sequence is defined as the result of the bitwise-OR operation on its elements. Given an array `arr` of length `n`, identify all possible distinct scores that can be obtained by selecting any **strictly increasing subsequence** from the array. Return the results sorted in ascending order.

**Note:** A subsequence is a sequence that can be derived from the given sequence by deleting zero or more elements without altering the order of the remaining elements. The empty subsequence is considered to be strictly increasing and has a score of 0.

### Input Format
The first line contains an integer `n`, the length of the array.
The next `n` lines each contain an integer representing `arr[i]`.

### Output Format
Output the distinct score values, one per line, sorted in ascending order.

### Constraints
- $1 \le n \le 10^4$
- $1 \le arr[i] < 1024$

### Example 1
**Input:**
```
4
3
2
4
6
```
**Output:**
```
0
2
3
4
6
7
```
**Explanation:**
Some strictly increasing subsequences that have distinct score values are:
- Empty subsequence; score = 0
- `[2]`; score = 2
- `[3]`; score = 3
- `[4]`; score = 4
- `[2, 4]`; score = 6
- `[3, 4]`; score = 7

### Example 2
**Input:**
```
4
3
5
5
1
```
**Output:**
```
0
1
3
5
7
```
**Explanation:**
Strictly increasing subsequences that have distinct score values are:
- Empty subsequence; score = 0
- `[1]`; score = 1
- `[3]`; score = 3
- `[5]`; score = 5
- `[3, 5]`; score = 7
