# 5. Advanced Querying & Syntaxes

When you move beyond basic data retrieval, you enter the territory of complex analytical queries. This section covers Subqueries, Common Table Expressions (CTEs), Window Functions, a catalog of essential built-in functions, and data pivoting.

## 5.1 Subqueries (Correlated vs. Non-Correlated)

A subquery is simply a query nested inside another query. The database engine handles them very differently depending on whether the inner query references data from the outer query.

::: heavy
**Heavy Concept: Correlated Subqueries**

**Analogy:** A *non-correlated subquery* is like asking the HR department for a printed list of valid department IDs once, and then checking your employee files against it. A *correlated subquery* is like picking up an employee file, calling HR to calculate the average salary specifically for *that employee's department*, putting the phone down, picking up the next file, and calling HR again.

**Concrete Example:** Find employees who make more than their own department's average salary.

```sql
SELECT name, salary, dept_id 
FROM employees outer_emp
WHERE salary > (
    SELECT AVG(salary) 
    FROM employees inner_emp 
    WHERE inner_emp.dept_id = outer_emp.dept_id
);
```

**Plain English, step by step:**

1. The database starts evaluating the outer query and looks at the first employee row (e.g., Alice in Sales, `dept_id = 1`).
2. It evaluates the `WHERE` clause and encounters the subquery.
3. Because the inner query references `outer_emp.dept_id`, it is **correlated**. The engine substitutes Alice's `dept_id` into the subquery.
4. The inner query runs, computing the average salary strictly for Sales (`dept_id = 1`).
5. The outer query compares Alice's salary to this computed average.
6. The engine moves to the next employee row and **repeats the entire process**.

**Technical Statement:** A correlated subquery establishes a row-by-row dependency. The inner query cannot be evaluated independently; it must conceptually execute once for every candidate row evaluated by the outer query [1].

**The Trap:** Because of this row-by-row execution, running a correlated subquery on a table with 10 million rows means the engine might execute the inner query 10 million times. Performance will grind to a halt. When performance matters, a correlated subquery should usually be rewritten using a `JOIN` or a Window Function.
:::

### Subquery Placement

Subqueries can appear in almost any clause:

```sql
-- Non-correlated subquery in WHERE (executes once)
SELECT * FROM employees 
WHERE salary > (SELECT AVG(salary) FROM employees);

-- Subquery in FROM (acts as a temporary "derived table")
SELECT dept_id, avg_sal 
FROM (
    SELECT dept_id, AVG(salary) AS avg_sal 
    FROM employees 
    GROUP BY dept_id
) AS dept_stats
WHERE avg_sal > 70000;

-- Subquery in SELECT (must be a "scalar subquery" returning exactly 1 row and 1 column)
SELECT name, salary,
    (SELECT AVG(salary) FROM employees) AS company_avg
FROM employees;
```

### `EXISTS` vs `IN`

When checking for the existence of related records, `EXISTS` checks if a subquery returns *any* rows and short-circuits (stops searching) as soon as it finds one, whereas `IN` checks value membership against a fully generated list.

```sql
-- IN: generates the list of IDs first, then checks membership
SELECT * FROM orders 
WHERE customer_id IN (SELECT id FROM customers WHERE region = 'US');

-- EXISTS: highly efficient with correlated subqueries; stops at the first match
SELECT * FROM orders o
WHERE EXISTS (
    SELECT 1 FROM customers c 
    WHERE c.id = o.customer_id AND c.region = 'US'
);
```

::: trap
**Trap: `NOT IN` with `NULL` values**
If you write `WHERE id NOT IN (SELECT parent_id FROM items)`, and even *one* `parent_id` in the subquery returns `NULL`, the entire `NOT IN` clause evaluates to `UNKNOWN` (which acts as `FALSE` for filtering). The query will mysteriously return zero rows. Always use `NOT EXISTS` when there is a risk of `NULL` values in the subquery result.
:::

## 5.2 Common Table Expressions (CTEs)

A Common Table Expression (defined via the `WITH` keyword) acts as a temporary, named result set that exists only for the duration of the query. It allows you to replace deeply nested subqueries with clean, top-to-bottom readable code.

```sql
WITH active_employees AS (
    SELECT * FROM employees WHERE status = 'active'
),
dept_stats AS (
    SELECT dept_id, AVG(salary) AS avg_sal 
    FROM active_employees 
    GROUP BY dept_id
)
SELECT ae.name, ds.avg_sal
FROM active_employees ae
JOIN dept_stats ds ON ae.dept_id = ds.dept_id;
```

::: heavy
**Heavy Concept: Recursive CTEs**

**Analogy:** A recursive CTE is like a `while` loop in traditional programming that keeps adding results to a list. It starts with a base case, then continuously uses its own previous output to find the next batch of data, stopping only when a loop iteration finds absolutely nothing new.

**Concrete Example:** Building an organizational chart from a self-referencing `employees` table (where each employee has a `manager_id`).

```sql
WITH RECURSIVE OrgChart AS (
    -- 1. The Anchor Member
    SELECT emp_id, name, manager_id, 1 AS depth
    FROM employees 
    WHERE manager_id IS NULL
    
    UNION ALL
    
    -- 2. The Recursive Member
    SELECT e.emp_id, e.name, e.manager_id, o.depth + 1
    FROM employees e
    INNER JOIN OrgChart o ON e.manager_id = o.emp_id
)
SELECT * FROM OrgChart ORDER BY depth;
```

**Watch it happen step by step:**

1. **Anchor Execution:** The database runs the query *before* the `UNION ALL`. This finds the CEO (no manager). Output: `[CEO]`. This is our working set.
2. **Recursive Iteration 1:** The database runs the query *after* the `UNION ALL`. Crucially, when the query references `OrgChart`, it substitutes the *working set from the previous step*. It joins the `[CEO]` against the employees table to find the CEO's direct reports. Output: `[VPs]`. This becomes the new working set, appending to the final output.
3. **Recursive Iteration 2:** It runs the recursive query again, this time substituting `[VPs]` for `OrgChart`. It finds the VP's direct reports. Output: `[Directors]`.
4. **Termination:** It repeats this until an iteration returns zero rows (e.g., when it queries for the direct reports of entry-level staff and finds none). The final result is the combined output of the anchor and all iterations [2].

**Technical Statement:** A recursive CTE requires the `RECURSIVE` modifier. It must contain a non-recursive base query (anchor) and a recursive query, combined by `UNION` or `UNION ALL`. The recursive self-reference applies strictly to the rows produced by the immediately preceding iteration.
:::

## 5.3 Window Functions

Window functions perform calculations across a set of rows related to the current row, but they fundamentally differ from standard aggregation. 

::: heavy
**Heavy Concept: The Window Function Mental Model**

**Analogy:** Standard `GROUP BY` aggregation is a meat grinder: you put in 100 rows, and 1 aggregated sausage comes out. A Window Function is a magnifying glass: you look at 100 individual rows, but the glass also shows you the average of their neighbors, without destroying the rows themselves.

**Concrete Example:** 
```sql
SELECT name, dept_id, salary,
    AVG(salary) OVER (PARTITION BY dept_id) AS dept_avg
FROM employees;
```

**Plain English, step by step:**

1. The query processes the `employees` table.
2. Unlike a `GROUP BY`, **no rows are collapsed**. Every single employee row remains intact in the output.
3. The `OVER` clause defines a "window" (a specific grouping) for the function to look at. Here, `PARTITION BY dept_id` means the window consists of all employees sharing the current row's department.
4. For each row, the `AVG()` function calculates the average salary of that specific window, and attaches the result as a new column. 

**Technical Statement:** A window function performs an aggregate-like calculation over a frame of rows, but retains the identity of every input row in the result set [3]. The `OVER()` clause dictates what rows the function is allowed to "see" when computing the value for the current row.
:::

### Anatomy of the `OVER` Clause

The `OVER` clause can contain three sub-clauses to control the window:

1. **`PARTITION BY`**: Divides the result set into independent groups. The function's calculation resets every time the partition boundary is crossed.
2. **`ORDER BY`**: Defines the logical sequence of rows within each partition. This is mandatory for ranking functions and running totals.
3. **Frame Clause**: Defines a sliding boundary within the partition (e.g., "the 3 rows before this one").

### 1. Ranking Functions

Ranking functions assign a sequential position to rows within a partition.

```sql
SELECT name, dept_id, salary,
    ROW_NUMBER() OVER (PARTITION BY dept_id ORDER BY salary DESC) AS row_num,
    RANK()       OVER (PARTITION BY dept_id ORDER BY salary DESC) AS rnk,
    DENSE_RANK() OVER (PARTITION BY dept_id ORDER BY salary DESC) AS dense_rnk
FROM employees;
```

**Tie-breaking behavior (e.g., for salaries [100k, 100k, 90k]):**

- `ROW_NUMBER()`: Assigns strictly sequential integers (1, 2, 3). Ties are broken arbitrarily.
- `RANK()`: Assigns the same rank to ties, but leaves a gap afterward (1, 1, 3).
- `DENSE_RANK()`: Assigns the same rank to ties, with no gap afterward (1, 1, 2).

### 2. Navigation (Offset) Functions

These functions pull values from other rows relative to the current row's position.

```sql
SELECT name, salary, hire_date,
    -- Pull the salary from the previous row
    LAG(salary, 1) OVER (ORDER BY hire_date) AS prev_salary,
    -- Pull the salary from the next row
    LEAD(salary, 1) OVER (ORDER BY hire_date) AS next_salary,
    -- Get the first value in the window
    FIRST_VALUE(name) OVER (PARTITION BY dept_id ORDER BY salary DESC) AS top_earner
FROM employees;
```

::: trap
**Trap: LAST_VALUE default frame**
`LAST_VALUE()` seems like it should return the absolute last row of the partition. However, if you use an `ORDER BY`, the default frame ends at the `CURRENT ROW`. Therefore, `LAST_VALUE()` will just return the current row's value! You must explicitly set the frame to `ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING` to see the true final row.
:::

### 3. Aggregate Window Functions and Frames

When you pair an aggregate function (like `SUM`) with an `ORDER BY` inside the `OVER` clause, it defaults to a **running total**.

```sql
SELECT name, hire_date, salary,
    -- Running total (cumulative sum) of salaries over time
    SUM(salary) OVER (ORDER BY hire_date) AS cumulative_salary
FROM employees;
```

This works because adding `ORDER BY` implicitly changes the window's *frame*. 

- Without `ORDER BY`, the frame is the entire partition.
- With `ORDER BY`, the default frame becomes `ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW` (from the beginning of the partition up to the current row).

You can explicitly set frames for sliding calculations:
```sql
SELECT name, hire_date, salary,
    -- Moving average of the current row and the 2 preceding rows
    AVG(salary) OVER (
        ORDER BY hire_date
        ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
    ) AS moving_avg_3
FROM employees;
```

## 5.4 Built-in Functions (PostgreSQL)

PostgreSQL provides a massive standard library of data-manipulation functions [4]. Here are the core functions required for daily analysis.

### String Functions

String functions manipulate text (`VARCHAR` / `TEXT`) data.

- **`LENGTH(string)`**: Returns the number of characters in a string.
- **`SUBSTRING(string FROM start FOR count)`**: Extracts a portion of a string. `SUBSTRING('PostgreSQL' FROM 1 FOR 4)` returns `'Post'`.
- **`POSITION(substring IN string)`**: Returns the 1-based integer index of a substring, or 0 if not found.
- **`TRIM(string)`**: Removes spaces from both the beginning and end of a string.
- **`REPLACE(string, target, replacement)`**: Replaces all occurrences of the target substring with the replacement.
- **`UPPER(string)` / `LOWER(string)`**: Converts case.
- **Concatenation (`||`)**: Joins strings together. `'Hello' || ' ' || 'World'` yields `'Hello World'`.
- **`REPEAT(string, count)`**: Repeats a string the specified number of times.

Postgres also heavily supports Regular Expressions. The `~` operator tests for a regex match (`'abc' ~ '[a-z]+'` returns true), and `REGEXP_REPLACE()` allows regex-based substitutions.

### Date and Time Functions

Date functions handle timestamps, dates, and intervals.

- **`CURRENT_DATE` / `CURRENT_TIMESTAMP`**: Returns the current system date or timestamp. (Note: These do not use parentheses).
- **`EXTRACT(field FROM source)`**: Pulls a sub-field (like year, month, or day) from a timestamp. `EXTRACT(YEAR FROM hire_date)` returns the year as an integer.
- **`DATE_TRUNC(precision, source)`**: Truncates a timestamp down to a specific precision, zeroing out everything smaller. `DATE_TRUNC('month', CURRENT_TIMESTAMP)` returns the first day of the current month at midnight.
- **Interval Arithmetic**: You can directly add or subtract time using the `INTERVAL` keyword. `CURRENT_DATE + INTERVAL '30 days'` computes a date 30 days in the future.
- **`AGE(timestamp, timestamp)`**: Returns a human-readable interval representing the difference between two timestamps (e.g., `'2 years 3 mons'`).
- **`TO_CHAR(timestamp, format)`**: Formats a date into a specific string layout. `TO_CHAR(hire_date, 'YYYY-MM-DD')` outputs `'2025-06-27'`.
- **`TO_DATE(string, format)`**: Parses a text string back into a date object.

### Math Functions

- **`ABS(numeric)`**: Absolute value.
- **`ROUND(numeric, decimal_places)`**: Rounds a number to the specified decimal places.
- **`TRUNC(numeric, decimal_places)`**: Truncates a number (cuts it off without rounding). `TRUNC(3.99, 0)` is 3.
- **`CEIL(numeric)` / `FLOOR(numeric)`**: Rounds up / rounds down to the nearest whole integer.
- **`MOD(x, y)`**: Returns the remainder of division (modulo).
- **`POWER(base, exponent)`**: Exponentiation.
- **`RANDOM()`**: Generates a random float between 0.0 and 1.0.

### Conditional Functions

- **`COALESCE(val1, val2, ...)`**: Evaluates arguments in order and returns the **first non-null** value. Crucial for defaulting nulls: `COALESCE(bonus, 0)` returns 0 if the bonus is null.
- **`NULLIF(val1, val2)`**: Returns `NULL` if `val1` equals `val2`; otherwise returns `val1`. Useful for preventing divide-by-zero errors: `total / NULLIF(count, 0)`.
- **`GREATEST(val1, val2, ...)` / `LEAST(...)`**: Returns the largest or smallest value from a list of expressions.

## 5.5 Conditional Aggregation (Pivot / Crosstab)

A "pivot" or "crosstab" transforms row-based data into columnar data. For example, turning a column of `quarter` labels (Q1, Q2, Q3) into actual physical columns in the result set.

Unlike some other databases, PostgreSQL does not have a native `PIVOT` keyword. Instead, the standard and most flexible way to pivot data in Postgres is **Conditional Aggregation**.

This technique combines an aggregate function (like `SUM`) with conditional logic. While you can use the standard `CASE` statement, PostgreSQL provides a dedicated, elegant `FILTER` clause specifically for this purpose.

::: keypoint
**Why this works:** The aggregate function evaluates every row in the group, but the `FILTER` clause (or `CASE` statement) ensures that only rows matching the specific column criteria are actually fed into the sum.
:::

```sql
-- Standard SQL approach using CASE (portable)
SELECT dept_name,
    SUM(CASE WHEN quarter = 'Q1' THEN revenue ELSE 0 END) AS "Q1_Rev",
    SUM(CASE WHEN quarter = 'Q2' THEN revenue ELSE 0 END) AS "Q2_Rev",
    SUM(CASE WHEN quarter = 'Q3' THEN revenue ELSE 0 END) AS "Q3_Rev",
    SUM(CASE WHEN quarter = 'Q4' THEN revenue ELSE 0 END) AS "Q4_Rev"
FROM sales
GROUP BY dept_name;

-- Modern PostgreSQL approach using FILTER (Cleaner)
SELECT dept_name,
    SUM(revenue) FILTER (WHERE quarter = 'Q1') AS "Q1_Rev",
    SUM(revenue) FILTER (WHERE quarter = 'Q2') AS "Q2_Rev",
    SUM(revenue) FILTER (WHERE quarter = 'Q3') AS "Q3_Rev",
    SUM(revenue) FILTER (WHERE quarter = 'Q4') AS "Q4_Rev"
FROM sales
GROUP BY dept_name;
```

*Note: PostgreSQL also offers a `crosstab()` function via the `tablefunc` extension, which can pivot dynamically without hardcoding columns, but it requires installing the extension and writing the source query as a text string. Conditional aggregation remains the standard everyday approach.*

### References
1. PostgreSQL Documentation: Subqueries - https://www.postgresql.org/docs/current/functions-subquery.html
2. PostgreSQL Documentation: WITH Queries (CTEs) - https://www.postgresql.org/docs/current/queries-with.html
3. PostgreSQL Documentation: Window Functions - https://www.postgresql.org/docs/current/tutorial-window.html
4. PostgreSQL Documentation: Functions and Operators - https://www.postgresql.org/docs/current/functions.html
