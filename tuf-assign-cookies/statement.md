# Assign Cookies

A teacher distributes cookies to students; each student receives **at most one** cookie.

You are given two arrays `student` and `cookie`. `student[i]` is the minimum cookie size the
i-th student will accept; `cookie[j]` is the size of the j-th cookie. Cookie `j` can be given to
student `i` iff `cookie[j] >= student[i]`. Maximise the number of students who receive a cookie
and print that maximum.

## Input
- Line 1: integer `n` — number of students.
- Line 2: `n` integers — `student[0..n-1]`.
- Line 3: integer `m` — number of cookies.
- Line 4: `m` integers — `cookie[0..m-1]` (this line is empty when `m = 0`).

## Output
A single integer: the maximum number of students that can be served.

## Constraints
- `1 <= n <= 3*10^4`
- `0 <= m <= 3*10^4`
- `1 <= student[i], cookie[j] <= 2^31 - 1`

## Examples
```
Input:
3
1 2 3
2
1 1
Output:
1
```
```
Input:
2
1 2
3
1 2 3
Output:
2
```
