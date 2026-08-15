## Maximum of Subarray Minimums

You are given an array `arr` of `n` integers and an integer `k`.

Consider every contiguous subarray of `arr` whose length is exactly `k`. There are `n - k + 1` such subarrays: the one starting at position `1`, the one starting at position `2`, and so on up to the one starting at position `n - k + 1`.

For each of these subarrays, take its **minimum** element. Among all of those minimums, report the **largest** one.

**Note:** A subarray is an array obtained by deleting several (possibly zero) elements from the beginning and several (possibly zero) elements from the end of the original array. Its elements are therefore consecutive in `arr` and keep their original order.

### Input Format

The first line contains a single integer `n` — the number of elements in `arr`.
Each of the next `n` lines contains a single integer — `arr[i]`, the `i`-th element of the array, in order.
The last line contains a single integer `k` — the required subarray length.

### Output Format

Print a single integer — the largest value among the minimums of all contiguous subarrays of `arr` of length exactly `k`.

### Constraints

- `1 <= n <= 10^6`
- `1 <= arr[i] <= 10^9`
- `1 <= k <= n`
- The answer is one of the array elements, so it always satisfies `1 <= answer <= 10^9` and fits in a signed 32-bit integer.
- Because `1 <= k <= n`, at least one subarray of length `k` always exists, so an answer always exists.

### Examples

**Example 1**

Input:
```
5
1
2
3
4
5
2
```

Output:
```
4
```

Explanation: With `k = 2` the subarrays are `[1, 2]`, `[2, 3]`, `[3, 4]` and `[4, 5]`. Their minimums are `1`, `2`, `3` and `4`. The largest of those minimums is `4`.

**Example 2**

Input:
```
5
1
2
3
1
2
1
```

Output:
```
3
```

Explanation: With `k = 1` every single element forms its own subarray, and the minimum of a one-element subarray is that element itself. The minimums are `1`, `2`, `3`, `1`, `2`, and the largest of them is `3`.

**Example 3**

Input:
```
3
1
1
1
2
```

Output:
```
1
```

Explanation: With `k = 2` the two subarrays are `[1, 1]` and `[1, 1]`. Both minimums are `1`, so the answer is `1`.

**Example 4**

Input:
```
6
5
1
9
9
1
5
2
```

Output:
```
9
```

Explanation: With `k = 2` the subarrays are `[5, 1]`, `[1, 9]`, `[9, 9]`, `[9, 1]` and `[1, 5]`, whose minimums are `1`, `1`, `9`, `1` and `1`. The largest is `9`, contributed by the single subarray in which both elements are large.
