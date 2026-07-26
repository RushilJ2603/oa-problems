# House Cleaning Routes

A city cleaning firm receives orders for **N** houses on a grid. House *i* sits at integer coordinates *(x_i, y_i)*.

Each employee may clean houses that all share **one common row** (same *x*) **or** all share **one common column** (same *y*). An employee assigned a particular row (resp. column) covers every ordered house on that row (resp. column).

Your task is to choose a set of rows and columns so that every house lies on at least one chosen row or column, using as few employees as possible (each chosen row or column needs one employee).

Duplicate coordinates count as a single house.

## Input Format

- Line 1: integer **N** — number of orders.
- Next **N** lines: two integers *x_i* *y_i* — coordinates of house *i*.

## Output Format

A single integer — the minimum number of employees required.

## Constraints

- \(1 \le N \le 400\)
- \(0 \le x_i, y_i \le 10^9\)

## Examples

### Example 1

**Input**
```
4
0 0
1 0
2 1
2 2
```

**Output**
```
2
```

**Explanation**

One employee takes column `y = 0` covering `(0,0)` and `(1,0)`. Another takes row `x = 2` covering `(2,1)` and `(2,2)`.

### Example 2

**Input**
```
7
1 0
2 3
4 4
3 1
9 1
10 3
5 5
```

**Output**
```
5
```

**Explanation**

Five lines (rows/columns) are necessary and sufficient; for instance columns `y=1` and `y=3` each cover two houses, while `(1,0)`, `(4,4)`, and `(5,5)` each need their own line.
