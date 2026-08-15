A software system assigns processing tasks based on available memory segments. For a given total capacity **N**, the system must allocate resources for every unique factor of **N**. 

You are given the capacity **N** and an array `nums` of distinct integers representing the sizes of currently available memory segments. For each unique factor of **N**, the system selects the largest available memory segment that is strictly smaller than the factor. This selected segment size is called the *lower bound* of the factor. 

**For example, if the factor is 3 and the available segments are `{1, 2, 3, 4}`, the selected segment is 2 because 2 is the greatest element strictly smaller than 3.**

Your task is to calculate the sum of these selected segment sizes (lower bounds) for all unique factors of **N**.
The integer 0 is guaranteed to be present in the array `nums`.

### Input Format

- The first line contains the integer **N**.
- The second line contains an integer **m** denoting the length of the array `nums`.
- The third line contains **m** space-separated integers denoting the elements of `nums`.

### Constraints

- 2 <= **N** <= 10^9
- 1 <= **m** <= 10^5
- All elements in `nums` are distinct and lie in the range [0, 10^5].
- `nums` is guaranteed to contain the integer 0.

### Output Format

- Return an integer denoting the sum of the lower bounds for all unique factors of **N**.

### Examples

**Example 1**
```
Input:
30
6
0 5 10 15 20 25

Output:
45
```
*Explanation:*
For N=30, the unique factors are 2, 3, 5, 6, 10, 15, and 30.
- For factor 2, the greatest integer strictly smaller in `nums` is 0.
- For factor 3, the greatest integer strictly smaller in `nums` is 0.
- For factor 5, the greatest integer strictly smaller in `nums` is 0.
- For factor 6, the greatest integer strictly smaller in `nums` is 5.
- For factor 10, the greatest integer strictly smaller in `nums` is 5.
- For factor 15, the greatest integer strictly smaller in `nums` is 10.
- For factor 30, the greatest integer strictly smaller in `nums` is 25.
The sum is 0 + 0 + 0 + 5 + 5 + 10 + 25 = 45.

**Example 2**
```
Input:
13
5
7 0 20 12 13

Output:
12
```
*Explanation:*
For N=13, the unique factors are 1 and 13.
- For factor 1, the greatest integer strictly smaller is 0.
- For factor 13, the greatest integer strictly smaller is 12.
The sum is 0 + 12 = 12.
