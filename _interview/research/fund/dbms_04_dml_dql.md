# 4. Data Manipulation & Querying (DML & DQL)

Data Manipulation Language (DML) modifies the data within the structure (inserting, updating, deleting), while Data Query Language (DQL) retrieves it (selecting). This section is the largest because `SELECT` is the most complex and versatile statement in SQL.

## 4.1 The Logical Execution Order

To survive an interview grilling, you must know the difference between the *syntax order* (how you type the query) and the *logical execution order* (how the database engine actually processes it).

::: heavy
**Heavy Concept: The Logical Execution Order**
**Analogy:** Imagine processing a massive stack of employee files to find the top 3 highest-paid departments. You wouldn't sort all 10,000 files first. You'd group them into department piles, calculate the total for each pile, throw out the small piles, and *then* sort the remaining handful.

The database does the exact same thing. It processes clauses in this strict order:

1. **`FROM` / `JOIN`**: Identify and combine the source tables.
2. **`WHERE`**: Filter individual rows out immediately.
3. **`GROUP BY`**: Collect remaining rows into aggregate buckets.
4. **`HAVING`**: Filter the buckets (aggregate conditions).
5. **`SELECT`**: Evaluate the columns, aliases, and math to return.
6. **`DISTINCT`**: Remove duplicate rows from the result.
7. **`ORDER BY`**: Sort the final result set.
8. **`LIMIT` / `OFFSET`**: Truncate the output for pagination.

**The Trap:** A classic beginner error is referencing a column alias (created in `SELECT`) inside the `WHERE` or `GROUP BY` clause. 
*Failure case:* `SELECT (salary + bonus) AS total_comp FROM employees WHERE total_comp > 100000;` This breaks because the engine evaluates the `WHERE` clause (step 2) *before* the `SELECT` clause (step 5) even creates the `total_comp` alias. You must repeat the math in the `WHERE` clause.
:::

## 4.2 SELECT — Full Anatomy

The `SELECT` statement is the primary way to ask the database a question. It dictates exactly which columns to return, how to derive new values, and how to format the output.

```sql
SELECT [ALL | DISTINCT]
    column1, column2,                        -- explicit columns
    expression AS alias,                     -- computed column with alias
    aggregate_function(column) AS alias      -- aggregation
FROM table1
    [JOIN table2 ON condition]               -- joins
WHERE condition                              -- row-level filter
GROUP BY column1, column2                    -- aggregation buckets
HAVING aggregate_condition                   -- group-level filter
ORDER BY column1 [ASC | DESC] [NULLS FIRST | NULLS LAST]
LIMIT n OFFSET m;                            -- pagination
```

*Why it matters here:* You rarely want every column from a table. Explicitly naming columns reduces network traffic and memory usage, making your queries significantly faster than using `SELECT *`.

## 4.3 WHERE Clause — Complete Operator Catalog

The `WHERE` clause acts as a sieve, examining every row from the source tables and discarding those that evaluate to false. 

```sql
-- Comparison operators
WHERE salary = 50000                         -- equals
WHERE salary <> 50000                        -- not equals (also !=)
WHERE salary > 50000                         -- greater than
WHERE salary >= 50000                        -- greater than or equal
WHERE salary < 50000                         -- less than
WHERE salary <= 50000                        -- less than or equal

-- BETWEEN (inclusive range)
WHERE salary BETWEEN 40000 AND 60000
-- Equivalent to: WHERE salary >= 40000 AND salary <= 60000

-- IN (membership in a list or subquery)
WHERE dept_id IN (1, 2, 3)
WHERE dept_id IN (SELECT id FROM departments WHERE region = 'US')

-- LIKE (pattern matching)
WHERE name LIKE 'J%'                         -- starts with J
WHERE name LIKE '%son'                       -- ends with son
WHERE name LIKE '_a%'                        -- second character is 'a'
WHERE name LIKE '%\_test%' ESCAPE '\'        -- literal underscore
WHERE email LIKE '%@gmail.com'

-- ILIKE (case-insensitive LIKE — Postgres only)
WHERE name ILIKE 'john%'

-- SIMILAR TO (regex-like — Postgres)
WHERE name SIMILAR TO '(John|Jane)%'

-- IS NULL / IS NOT NULL
WHERE manager_id IS NULL                     
WHERE manager_id IS NOT NULL

-- IS DISTINCT FROM (NULL-safe equality — Postgres)
WHERE a IS DISTINCT FROM b                   -- treats NULL = NULL as FALSE (they are not distinct)

-- ANY / ALL (compare against a set)
WHERE salary > ANY (SELECT salary FROM employees WHERE dept_id = 3)
WHERE salary > ALL (SELECT salary FROM employees WHERE dept_id = 3)

-- Logical operators
WHERE salary > 50000 AND dept_id = 3
WHERE salary > 50000 OR dept_id = 3
WHERE NOT (salary > 50000)
```

::: trap
**Trap: NULL Semantics in WHERE Clauses**
In SQL, `NULL` does not mean "empty string" or "zero"; it means "unknown." Because you cannot compare two unknown values, `WHERE manager_id = NULL` will *never* return true—it evaluates to `NULL` (unknown), which acts like false in a `WHERE` filter. You must use `IS NULL`.

*Failure case:* Using `NOT IN` with a subquery that contains a `NULL`. `WHERE dept_id NOT IN (1, 2, NULL)` evaluates to unknown for every row, returning zero results. Always filter out NULLs from the subquery when using `NOT IN`.
:::

## 4.4 INSERT — All Variants

The `INSERT` statement adds new rows to a table. You specify the target columns and the corresponding values. If you omit a column, the database fills it with its default value (or `NULL` if no default exists).

```sql
-- Single row insert
INSERT INTO employees (name, salary, dept_id)
VALUES ('Alice', 75000, 3);

-- Multi-row insert
INSERT INTO employees (name, salary, dept_id)
VALUES ('Bob', 80000, 2),
       ('Charlie', 65000, 1),
       ('Diana', 90000, 3);

-- INSERT ... SELECT (copy data from another table/query)
INSERT INTO high_earners (emp_id, name, salary)
SELECT emp_id, name, salary FROM employees WHERE salary > 100000;

-- INSERT ... RETURNING (get back the inserted data — Postgres)
INSERT INTO employees (name, salary)
VALUES ('Eve', 95000)
RETURNING emp_id, name;  -- Returns the auto-generated emp_id

-- Default values
INSERT INTO employees (name) VALUES ('Frank');  -- other columns get DEFAULTs or NULL
INSERT INTO logs DEFAULT VALUES;                -- all columns get defaults
```

::: heavy
**Heavy Concept: UPSERT (ON CONFLICT)**
**Analogy:** Imagine handing a new employee roster to payroll. If the employee doesn't exist yet, you add them. If they *do* already exist, you don't create a duplicate profile; instead, you update their existing salary.

PostgreSQL provides the `ON CONFLICT` clause to handle this gracefully in one atomic step, preventing race conditions where two identical inserts happen simultaneously.

**Example:**
```sql
INSERT INTO products (sku, name, price)
VALUES ('ABC123', 'Widget', 9.99)
ON CONFLICT (sku) DO UPDATE SET price = EXCLUDED.price;
```
Here, `EXCLUDED` is a special PostgreSQL table alias that holds the row we *tried* to insert. If 'ABC123' already exists (violating the unique constraint on `sku`), we catch the conflict and update the price with the proposed new value.

**Alternative rejected:** Doing a `SELECT` to check for existence, followed by an `INSERT` or `UPDATE` from application code. This is a classic race condition; another process might insert the row in the millisecond between your `SELECT` and `INSERT`. `ON CONFLICT` is thread-safe and atomic.
:::

## 4.5 UPDATE — All Variants

The `UPDATE` statement modifies existing rows. It evaluates a `WHERE` clause to find target rows, then applies the `SET` expressions.

```sql
-- Basic update
UPDATE employees SET salary = 80000 WHERE emp_id = 42;

-- Update multiple columns
UPDATE employees
SET salary = salary * 1.10, status = 'promoted', updated_at = CURRENT_TIMESTAMP
WHERE dept_id = 3 AND performance_rating >= 4;

-- UPDATE with a subquery
UPDATE employees
SET salary = (SELECT AVG(salary) FROM employees WHERE dept_id = 3)
WHERE emp_id = 42;

-- UPDATE ... FROM (join-based update — Postgres)
UPDATE employees e
SET salary = d.base_salary
FROM departments d
WHERE e.dept_id = d.id AND d.name = 'Engineering';

-- UPDATE ... RETURNING (Postgres)
UPDATE employees SET salary = salary * 1.10
WHERE dept_id = 3
RETURNING emp_id, name, salary;
```

::: trap
**Trap: Forgetting the WHERE Clause**
Running `UPDATE employees SET salary = 0;` without a `WHERE` clause sets *every single employee's* salary to zero. There is no "undo" button outside of a transaction. Always write the `WHERE` clause first, or wrap critical updates in a transaction with a `ROLLBACK` ready.
:::

## 4.6 DELETE — All Variants

The `DELETE` statement removes entire rows. You cannot delete a specific column (that requires an `UPDATE SET column = NULL`). 

```sql
-- Basic delete
DELETE FROM employees WHERE emp_id = 42;

-- Delete with subquery
DELETE FROM employees
WHERE dept_id IN (SELECT id FROM departments WHERE status = 'closed');

-- Delete with USING (Postgres)
DELETE FROM employees e
USING departments d
WHERE e.dept_id = d.id AND d.status = 'closed';

-- DELETE ... RETURNING (Postgres)
DELETE FROM employees WHERE status = 'terminated'
RETURNING emp_id, name;  -- returns deleted rows for logging

-- Delete all rows (row-by-row, fully logged — compare with TRUNCATE)
DELETE FROM logs;
```

## 4.7 The MERGE Statement (UPSERT)

Starting in PostgreSQL 15, SQL-standard `MERGE` is supported. While `INSERT ... ON CONFLICT` is great for simple UPSERTs on a single table, `MERGE` is designed for complex data synchronization between entire tables.

::: heavy
**Heavy Concept: MERGE**
**Analogy:** Reconciling a daily sales feed into a master inventory sheet. For each line in the daily feed, you check the master sheet. If the product matches, you subtract the sold quantity. If the product is entirely new in the feed, you add a new line to the master sheet.

`MERGE` combines `INSERT`, `UPDATE`, and `DELETE` into a single unified statement based on a join condition.

**Example:**
```sql
MERGE INTO inventory AS target
USING daily_feed AS source
ON target.product_id = source.product_id
WHEN MATCHED THEN
    UPDATE SET quantity = target.quantity + source.quantity, updated_at = CURRENT_TIMESTAMP
WHEN NOT MATCHED THEN
    INSERT (product_id, quantity) VALUES (source.product_id, source.quantity);
```

*Plain-English breakdown:*

1. `MERGE INTO target USING source`: We define the table to modify (`inventory`) and the data to pull from (`daily_feed`).
2. `ON ...`: We specify the common identifier to match records (the `product_id`).
3. `WHEN MATCHED THEN UPDATE`: If a match is found, we update the existing row in `inventory`.
4. `WHEN NOT MATCHED THEN INSERT`: If the `daily_feed` has a product not present in `inventory`, we insert it.

*Question to sit with:* Why would you use `MERGE` over `ON CONFLICT`? `MERGE` can update or delete rows when they *don't* match, allowing full synchronization, whereas `ON CONFLICT` only reacts to unique constraint violations during insertion.
:::

## 4.8 The Relational JOIN — All Types with Examples

Relational databases store facts in isolated tables to avoid duplication (normalization). To answer real-world questions, you must stitch these tables back together.

::: heavy
**Heavy Concept: The Relational JOIN**
**Analogy:** Imagine looking up an employee in a phonebook, seeing their department ID is "3", then walking over to a separate department directory, looking up "3", and writing down "Engineering" next to the employee's name. A JOIN automates this cross-referencing.

**Example:** 
Assume two tables: `employees (emp_id, name, dept_id)` and `departments (id, dept_name)`.

**INNER JOIN:** Keep only rows where the lookup succeeds in both tables.
```sql
SELECT e.name, d.dept_name
FROM employees e
INNER JOIN departments d ON e.dept_id = d.id;
```
If an employee has no `dept_id`, or a department has no employees, they are dropped from the result.

**LEFT JOIN (Outer):** Keep every row from the left table (employees). If the lookup fails, fill the right side with `NULL`s.
```sql
SELECT e.name, d.dept_name
FROM employees e
LEFT JOIN departments d ON e.dept_id = d.id;
```
*Why here:* Essential for finding missing data, like "find all employees who have not been assigned a department yet."

**RIGHT JOIN (Outer):** The mirror of LEFT JOIN. Keeps every row from the right table (departments).
```sql
SELECT e.name, d.dept_name
FROM employees e
RIGHT JOIN departments d ON e.dept_id = d.id;
```

**FULL JOIN (Outer):** Keep everything. If the lookup succeeds, join them. If it fails on either side, fill the missing half with `NULL`s.
```sql
SELECT e.name, d.dept_name
FROM employees e
FULL OUTER JOIN departments d ON e.dept_id = d.id;
```

**CROSS JOIN:** Create every possible combination (a Cartesian product). 
```sql
SELECT e.name, d.dept_name
FROM employees e
CROSS JOIN departments d;
```
100 employees × 5 departments = 500 rows. Usually useless on its own, but powerful when combined with a lateral join.

**SELF JOIN:** A table joining to itself.
```sql
SELECT e.name AS employee, m.name AS manager
FROM employees e
LEFT JOIN employees m ON e.manager_id = m.emp_id;
```
*Why here:* Crucial for hierarchical data, like organizational charts or parent-child category trees.

**LATERAL JOIN (Postgres):** A loop disguised as a join.
```sql
SELECT d.dept_name, top_emp.name, top_emp.salary
FROM departments d
CROSS JOIN LATERAL (
    SELECT name, salary FROM employees
    WHERE dept_id = d.id ORDER BY salary DESC LIMIT 3
) AS top_emp;
```
Normally, a subquery in a `FROM` clause cannot reference the tables joined before it. `LATERAL` breaks this rule. For *every* department row, it re-runs the subquery, allowing you to fetch the "top 3 earners per department".
:::

::: trap
**Trap: Implicit Cartesian Products**
Writing `SELECT * FROM A, B;` without a `WHERE` clause implicitly performs a `CROSS JOIN`. In production, this can accidentally generate billions of rows, crashing the database server through memory exhaustion. Always use explicit `JOIN ... ON ...` syntax.
:::

## 4.9 Aggregate Functions

Aggregations collapse multiple rows into a single scalar value.

```sql
SELECT
    COUNT(*)                AS total_rows,        -- counts all rows (incl. NULLs)
    COUNT(salary)           AS non_null_salaries, -- counts non-NULL values
    COUNT(DISTINCT dept_id) AS unique_depts,
    SUM(salary)             AS total_payroll,
    AVG(salary)             AS avg_salary,
    MIN(salary)             AS lowest_salary,
    MAX(salary)             AS highest_salary,
    -- String aggregation (concatenate names)
    STRING_AGG(name, ', ' ORDER BY name) AS all_names,
    -- Array aggregation (Postgres)
    ARRAY_AGG(DISTINCT dept_id) AS dept_list
FROM employees;
```

*The `COUNT(*)` vs `COUNT(column)` trap:* `COUNT(*)` counts the number of *rows* in the table, regardless of what they contain. `COUNT(column)` specifically counts how many *non-NULL* values exist in that specific column. If an employee has a `NULL` salary, they are counted by `COUNT(*)` but ignored by `COUNT(salary)`.

## 4.10 GROUP BY — Advanced Grouping

When you need aggregations per category rather than across the whole table, use `GROUP BY`.

::: heavy
**Heavy Concept: WHERE vs HAVING**
Both filter data, but at completely different stages of execution.

**WHERE** filters *raw rows* before they are grouped.
**HAVING** filters *buckets* after they have been aggregated.

**Example:** Find departments with an average salary over $70,000, excluding the CEO from the calculation.
```sql
SELECT dept_id, AVG(salary) AS avg_sal
FROM employees
WHERE job_title != 'CEO'           -- Filters out the CEO (raw row)
GROUP BY dept_id                   -- Creates department buckets
HAVING AVG(salary) > 70000;        -- Filters the final buckets
```
*Failure case:* `WHERE AVG(salary) > 70000;` This throws an error because at the time the `WHERE` clause runs (Step 2), the database hasn't computed any averages yet (Step 5).
:::

::: heavy
**Heavy Concept: ROLLUP, CUBE, and GROUPING SETS**
**Analogy:** Creating subtotals in a pivot table. Instead of writing three separate queries (one for detail, one for subtotals, one for the grand total) and gluing them together, you ask the database to do the math in one pass.

**GROUP BY ROLLUP (Hierarchical Subtotals):**
```sql
SELECT dept_id, job_title, SUM(salary) AS total
FROM employees
GROUP BY ROLLUP (dept_id, job_title);
```
Produces: 

1. Detail: (dept, title)
2. Subtotal: (dept, NULL) -> Total per department
3. Grand Total: (NULL, NULL) -> Total everywhere

**GROUP BY CUBE (All Subtotal Combinations):**
```sql
SELECT dept_id, job_title, SUM(salary) AS total
FROM employees
GROUP BY CUBE (dept_id, job_title);
```
Produces everything `ROLLUP` does, plus subtotals by `job_title` across all departments.

**GROUP BY GROUPING SETS (Explicit Subtotals):**
When you only want specific aggregations, skipping the noise.
```sql
SELECT dept_id, job_title, SUM(salary) AS total
FROM employees
GROUP BY GROUPING SETS (
    (dept_id, job_title),  -- detail
    ()                     -- grand total only (skips intermediate subtotals)
);
```
:::

## 4.11 CASE Expressions

The `CASE` expression acts as an inline `if/else` statement inside your SQL query. It returns a single value based on evaluated conditions.

```sql
-- Simple CASE (equality check on a single column)
SELECT name,
    CASE dept_id
        WHEN 1 THEN 'Engineering'
        WHEN 2 THEN 'Sales'
        WHEN 3 THEN 'Marketing'
        ELSE 'Other'
    END AS department_name
FROM employees;

-- Searched CASE (arbitrary boolean conditions)
SELECT name, salary,
    CASE
        WHEN salary >= 100000 THEN 'Senior'
        WHEN salary >= 60000  THEN 'Mid-Level'
        WHEN salary >= 30000  THEN 'Junior'
        ELSE 'Intern'
    END AS level
FROM employees;

-- CASE inside an aggregate (conditional aggregation)
SELECT dept_id,
    SUM(CASE WHEN salary > 70000 THEN 1 ELSE 0 END) AS high_earners,
    SUM(CASE WHEN salary <= 70000 THEN 1 ELSE 0 END) AS others
FROM employees
GROUP BY dept_id;
```

*Why it matters here:* Conditional aggregation (using `SUM(CASE WHEN...)`) allows you to pivot data, turning rows into columns without using complex proprietary `PIVOT` syntaxes.

## 4.12 NULL Handling Functions

Because `NULL` poisons calculations (e.g., `10 + NULL = NULL`), you frequently need to substitute a default value when a `NULL` is encountered.

```sql
-- COALESCE: Returns the first non-NULL argument in the list.
SELECT name, COALESCE(phone, email, 'No contact') AS contact 
FROM employees;

-- NULLIF: Returns NULL if the two arguments are equal.
SELECT revenue / NULLIF(cost, 0) AS margin 
FROM products;
```

*Why it matters here:* `NULLIF` is the standard trick to prevent division-by-zero errors. If `cost` is `0`, `NULLIF(cost, 0)` returns `NULL`. The division becomes `revenue / NULL`, which safely yields `NULL` instead of crashing the query.

## 4.13 Type Casting

Sometimes a value is interpreted as the wrong data type (e.g., reading a string from a CSV that should be a date). You must convert it manually.

```sql
-- CAST (Standard SQL)
SELECT CAST('2025-01-15' AS DATE);
SELECT CAST(salary AS VARCHAR(20)) FROM employees;
SELECT CAST('123.45' AS DECIMAL(10,2));

-- :: operator (Postgres shorthand, extremely common in practice)
SELECT '2025-01-15'::DATE;
SELECT salary::TEXT FROM employees;
```

## 4.14 Set Operations

Set operations combine the results of two or more independent `SELECT` queries into a single column structure. Both queries must output the exact same number of columns with compatible data types.

```sql
-- UNION: Append the results and remove duplicates.
SELECT name FROM employees WHERE dept_id = 1
UNION
SELECT name FROM contractors WHERE dept_id = 1;

-- UNION ALL: Append the results but keep duplicates.
SELECT name, 'employee' AS source FROM employees
UNION ALL
SELECT name, 'contractor' AS source FROM contractors;

-- INTERSECT: Only return rows that appear in BOTH query results.
SELECT email FROM employees
INTERSECT
SELECT email FROM newsletter_subscribers;

-- EXCEPT: Return rows that appear in the first query, but NOT the second.
SELECT email FROM employees
EXCEPT
SELECT email FROM unsubscribed;
```

*Alternative rejected:* Why use `UNION ALL` instead of `UNION`? `UNION` requires the database engine to sort the entire combined result set to find and eliminate duplicates, which is a massive performance hit. If you know the sets are already disjoint (e.g., active vs deleted users) or you don't care about duplicates, *always* use `UNION ALL`.

### References
1. SQL Logical Execution Order - SQL Authority - https://blog.sqlauthority.com
2. PostgreSQL: Documentation: MERGE - PostgreSQL Global Development Group - https://www.postgresql.org/docs/current/sql-merge.html
3. SQL Joins - DataCamp - https://www.datacamp.com/tutorial/sql-joins
4. SQL Set Operators - Wikipedia - https://en.wikipedia.org/wiki/Set_operations_(SQL)
