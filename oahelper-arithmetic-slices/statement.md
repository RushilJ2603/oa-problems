A company is tracking the daily average latency of its main server over a period of $n$ days. The latency on the $i$-th day is given as an integer in an array.

To analyze performance trends, the engineering team wants to identify **stable periods**. A stable period is defined as a contiguous sequence of **at least three days** where the day-to-day difference in latency is exactly the same.

Given an integer array `latencies` representing the daily latencies, return the total number of stable periods.

### Input Format
- A single line containing the array of latencies in the format `[x, y, z, ...]`.

### Output Format
- Print a single integer representing the total number of stable periods.

### Constraints
- $1 \le n \le 5000$
- $-1000 \le \text{latencies}[i] \le 1000$

### Examples

**Example 1:**
```
Input:
[1, 2, 3, 4]

Output:
3
```
*Explanation:* There are 3 stable periods: `[1, 2, 3]`, `[2, 3, 4]`, and `[1, 2, 3, 4]` itself. The daily difference is consistently 1.

**Example 2:**
```
Input:
[1]

Output:
0
```
*Explanation:* A stable period must have at least 3 days.

**Example 3:**
```
Input:
[1, 3, 5, 7, 9]

Output:
6
```
*Explanation:* The stable periods are `[1, 3, 5]`, `[3, 5, 7]`, `[5, 7, 9]`, `[1, 3, 5, 7]`, `[3, 5, 7, 9]`, and `[1, 3, 5, 7, 9]`.
