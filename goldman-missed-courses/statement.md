# Missed Courses

There are `numCourses` courses, numbered `0` to `numCourses - 1`, taught in sequence. On day `i`
the professor teaches course `i % numCourses`. A student is absent every day from `firstDay` to
`lastDay`, inclusive. How many **distinct** courses did the student miss?

## Input
A single line with three integers: `numCourses`, `firstDay`, `lastDay`.

## Output
A single integer: the number of distinct courses missed.

## Constraints
- `1 <= numCourses <= 10^9`
- `0 <= firstDay <= lastDay <= 10^18`

## Examples
```
Input:
3 1 4
Output:
3
```
Days 1..4 teach courses 1, 2, 0, 1 -> distinct {0,1,2} = 3.
```
Input:
5 2 3
Output:
2
```
