# Department Top Earners

Two tables:

**`departments`**

| Column | Type | Notes |
| --- | --- | --- |
| `id` | INTEGER | primary key |
| `name` | TEXT | never NULL |

**`employees`**

| Column | Type | Notes |
| --- | --- | --- |
| `id` | INTEGER | primary key |
| `name` | TEXT | never NULL |
| `salary` | INTEGER | may be zero or negative |
| `department_id` | INTEGER | **may be NULL**, and may name a department that does not exist |

An employee is a **top earner** in their department if their salary is one of the **three highest
distinct salaries** in that department.

Report every top earner. Employees whose `department_id` is NULL or does not appear in
`departments` are not in any department and are never reported.

## Output

Three columns, in this order: **department name, employee name, salary**.

Ordered by **department name ascending**, then **salary descending**, then **employee name
ascending**. This ordering is part of the answer.

## Rules

- Only the query's **result set** is graded. Column names are ignored; column count and order are not.
- Your submission must be a **single read-only `SELECT`**.

## Example

**`departments`**

| id | name |
| --- | --- |
| 1 | IT |
| 2 | Sales |

**`employees`**

| id | name | salary | department_id |
| --- | --- | --- | --- |
| 1 | Joe | 85000 | 1 |
| 2 | Henry | 80000 | 2 |
| 3 | Sam | 60000 | 2 |
| 4 | Max | 90000 | 1 |
| 5 | Janet | 69000 | 1 |
| 6 | Randy | 85000 | 1 |
| 7 | Will | 70000 | 1 |

**Output**

| department | employee | salary |
| --- | --- | --- |
| IT | Max | 90000 |
| IT | Joe | 85000 |
| IT | Randy | 85000 |
| IT | Will | 70000 |
| Sales | Henry | 80000 |
| Sales | Sam | 60000 |

IT's three highest distinct salaries are 90000, 85000 and 70000. **Two** employees earn 85000 and
both are reported, so IT contributes four rows — "top three salaries" is not "top three people".
Janet at 69000 is fourth and is excluded.
