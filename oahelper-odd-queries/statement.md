# Odd queries

Given an array of integers **Arr**. You are asked **Q** queries of two types:

- `1 i v`: change the `i`-th element of **Arr** to `v`
- `2 l r`: Determine the count of distinct integers that appear an odd number of times in the range `l` to `r`

For every query of type 2, output the number of elements in the subarray from index `l` to `r` (inclusive) that have an odd frequency in that subarray.

**Note:** Assume 1-based indexing for the array elements and queries.

### Input Format

- The first line contains **T**, which represents the number of test cases.
- For each testcase:
  - The first line contains **N** denoting the size of array
  - The second line contains **Q** denoting the number of queries
  - The third line contains **N** space-separated integers denoting the elements of **Arr**.
  - Each of the next **Q** lines contains 3 space-separated integers, denoting the queries. The first integer is the type of the query (1 or 2).

### Output Format

For each test case in a new line, print the answer of each query of type 2 separated by space.

### Constraints

- $1 \le T \le 10$
- $2 \le N \le 10^5$
- $1 \le Q \le 10^5$
- $1 \le Arr[i], v \le 10^3$
- For query of type 1: $1 \le i \le N$
- For query of type 2: $1 \le l \le r \le N$
- The sum of $N$ and the sum of $Q$ over all test cases in one file will not exceed $10^5$.

### Example 1

**Input**
```
2
4
3
1 2 3 2
2 1 3
1 2 4
2 1 4
4
3
1 2 2 2
2 1 4
1 3 3
2 1 3
```

**Output**
```
3 4
2 3
```

**Explanation**
The first test case:
- Query 1: type 2, range [1, 3]. Subarray is [1, 2, 3]. Distinct integers with odd count are 1, 2, 3. The answer is 3.
- Query 2: type 1, set Arr[2] = 4. Arr becomes [1, 4, 3, 2].
- Query 3: type 2, range [1, 4]. Subarray is [1, 4, 3, 2]. Distinct integers with odd count are 1, 4, 3, 2. The answer is 4.

The second test case:
- Query 1: type 2, range [1, 4]. Subarray is [1, 2, 2, 2]. Odd count integers are 1, 2. Answer is 2.
- Query 2: type 1, set Arr[3] = 3. Arr becomes [1, 2, 3, 2].
- Query 3: type 2, range [1, 3]. Subarray is [1, 2, 3]. Odd count integers are 1, 2, 3. Answer is 3.
