# Second Highest Salary

You are given a table `employee`:

| Column | Type | Notes |
| --- | --- | --- |
| `id` | INTEGER | primary key |
| `salary` | INTEGER | never NULL; may be zero or negative |

Write a query that reports the **second highest distinct salary**.

If there is no second distinct salary — the table is empty, has one row, or every row holds the same
salary — the query must still return **one row** containing `NULL`.

## Output

Exactly one row and one column: the second highest distinct salary, or `NULL`.

## Rules

- Only the query's **result set** is graded. Column names are ignored; column count and order are not.
- Your submission must be a **single read-only `SELECT`**.

## Example 1

**Input table** `employee`

| id | salary |
| --- | --- |
| 1 | 100 |
| 2 | 200 |
| 3 | 300 |

**Output**

| second_highest |
| --- |
| 200 |

## Example 2

**Input table** `employee`

| id | salary |
| --- | --- |
| 1 | 100 |

**Output**

| second_highest |
| --- |
| NULL |

There is no second distinct salary, so the answer is one row holding `NULL` — **not** zero rows.
