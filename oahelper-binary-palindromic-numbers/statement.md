# Binary Palindromic Numbers

A **binary palindromic number** is a number whose binary representation reads the same forwards and
backwards. The binary representation uses the minimum number of bits — there are no leading zeros.

Given a number `N`, you may repeatedly apply either operation:

- increase the number by `1`;
- decrease the number by `1`.

Find the **minimum number of operations** needed to turn `N` into a binary palindromic number.

## Input

- The first line contains an integer `T` — the number of test cases.
- Each of the next `T` lines contains a single integer `N`.

## Output

For each test case, print one line containing the minimum number of operations.

## Constraints

- `1 <= T <= 10^5`
- `1 <= N <= 2 * 10^9`

## Example

**Input**
```
6
2
3
4
1
10
12
```

**Output**
```
1
0
1
0
1
3
```

**Explanation**

- `N = 2` is `10` in binary, not a palindrome. Going down reaches `1` (`1`) in one operation; going
  up reaches `3` (`11`) in one operation. The answer is `1`.
- `N = 3` is `11`, already a palindrome, so `0`.
- `N = 4` is `100`. Down to `3` (`11`) is one operation; up to `5` (`101`) is one operation. Answer
  `1`.
- `N = 1` is `1`, already a palindrome, so `0`.
- `N = 10` is `1010`. Down to `9` (`1001`) is one operation. Answer `1`.
- `N = 12` is `1100`. The nearest palindromes are `9` (`1001`) three below and `15` (`1111`) three
  above, so the answer is `3`.
