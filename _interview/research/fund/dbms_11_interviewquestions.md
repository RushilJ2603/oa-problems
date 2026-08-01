# 11. SQL Interview & OA Question Bank

This section contains classic SQL questions that appear repeatedly in technical interviews and online assessments (OAs) at companies like Amazon, Google, Meta, and top startups. Each problem is presented with the question, the schema, the solution, and an explanation of *why* this approach works. Problems are organized from foundational to advanced.

---

## 11.1 Foundational — SELECT, WHERE, Aggregates

### Q1: Find employees who earn more than their manager
**Schema:** `employees (emp_id, name, salary, manager_id)`

```sql
SELECT e.name AS employee, e.salary AS emp_salary,
       m.name AS manager,  m.salary AS mgr_salary
FROM employees e
INNER JOIN employees m ON e.manager_id = m.emp_id
WHERE e.salary > m.salary;
```
**Why:** This is a classic **Self Join**. The same `employees` table is aliased as both `e` (the employee) and `m` (the manager). The `JOIN` condition links each employee's row directly to their manager's row, allowing a direct comparison of their salaries in the `WHERE` clause.

---

### Q2: Find departments with more than 5 employees
**Schema:** `employees (emp_id, name, dept_id)`, `departments (id, dept_name)`

```sql
SELECT d.dept_name, COUNT(e.emp_id) AS headcount
FROM departments d
LEFT JOIN employees e ON d.id = e.dept_id
GROUP BY d.dept_name
HAVING COUNT(e.emp_id) > 5
ORDER BY headcount DESC;
```
**Why:** `HAVING` filters *after* aggregation, unlike `WHERE` which filters individual rows *before* grouping. We use a `LEFT JOIN` in case a department exists but has zero employees (though the `> 5` condition makes an `INNER JOIN` functionally identical here).

---

### Q3: Find customers who have never placed an order
**Schema:** `customers (id, name)`, `orders (id, customer_id, order_date)`

```sql
-- Approach 1: LEFT JOIN + IS NULL (often the fastest execution plan)
SELECT c.name
FROM customers c
LEFT JOIN orders o ON c.id = o.customer_id
WHERE o.id IS NULL;

-- Approach 2: NOT EXISTS (cleaner semantics, strictly NULL-safe)
SELECT c.name
FROM customers c
WHERE NOT EXISTS (SELECT 1 FROM orders o WHERE o.customer_id = c.id);
```
**Why:** Both approaches are valid PostgreSQL idioms. Approach 1 attempts to join every customer to an order, and the `WHERE o.id IS NULL` filters out any customer where a match was found. Approach 2 explicitly asks the database to check for the absence of rows, which is highly readable and immune to `NULL` comparison bugs that plague the `NOT IN` operator.

---

### Q4: Find duplicate rows in a table
**Schema:** `contacts (id, email, name)`

```sql
-- Find which emails are duplicated
SELECT email, COUNT(*) AS cnt
FROM contacts
GROUP BY email
HAVING COUNT(*) > 1;

-- Find the actual duplicate rows with all their data
SELECT * FROM contacts
WHERE email IN (
    SELECT email FROM contacts GROUP BY email HAVING COUNT(*) > 1
);
```
**Why:** Aggregating by the column you suspect has duplicates (`email`) and filtering with `HAVING COUNT(*) > 1` immediately identifies the offending values. You can then use those values in a subquery to pull the full rows.

---

## 11.2 Intermediate — Joins, Subqueries, CASE

### Q5: Second Highest Salary (Classic)
**Schema:** `employees (emp_id, name, salary)`

```sql
-- Approach 1: Window Function (Extensible to Nth highest)
SELECT salary AS second_highest FROM (
    SELECT salary, DENSE_RANK() OVER (ORDER BY salary DESC) AS rnk
    FROM employees
) ranked
WHERE rnk = 2;

-- Approach 2: Subquery with MAX (Simple, but rigid)
SELECT MAX(salary) AS second_highest
FROM employees
WHERE salary < (SELECT MAX(salary) FROM employees);
```
**Why:** The `DENSE_RANK()` window function approach is superior because it handles ties flawlessly and scales easily if the interviewer changes the question to "5th highest". The `MAX()` subquery approach is clever but only works for the 2nd highest. (Note: Avoid using `LIMIT 1 OFFSET 1` for this problem, as it will skip the wrong row if two people tie for the highest salary).

---

### Q6: Nth Highest Salary per Department
**Schema:** `employees (emp_id, name, salary, dept_id)`

```sql
-- Find the 3rd highest salary in each department
SELECT dept_id, name, salary FROM (
    SELECT dept_id, name, salary,
           DENSE_RANK() OVER (PARTITION BY dept_id ORDER BY salary DESC) AS rnk
    FROM employees
) ranked
WHERE rnk = 3;
```
**Why:** `PARTITION BY dept_id` creates an independent ranking window for each department. `DENSE_RANK()` ensures that if two people tie for 1st place, the next person is ranked 2nd (unlike `RANK()`, which would skip to 3rd).

---

### Q7: Top N records per group
**Schema:** `orders (id, customer_id, total, order_date)`

```sql
-- Top 3 most expensive orders per customer
SELECT customer_id, id, total, order_date FROM (
    SELECT *, ROW_NUMBER() OVER (PARTITION BY customer_id ORDER BY total DESC) AS rn
    FROM orders
) ranked
WHERE rn <= 3;
```
**Why:** We use `ROW_NUMBER()` (instead of `RANK()` or `DENSE_RANK()`) because we want exactly 3 rows returned per customer, even if there are identical order totals that would cause ties in a ranking function.

---

### Q8: Pivot — Rows to Columns
**Schema:** `sales (product, quarter, revenue)`

```sql
-- Convert quarterly rows into columns
SELECT product,
    SUM(CASE WHEN quarter = 'Q1' THEN revenue ELSE 0 END) AS Q1,
    SUM(CASE WHEN quarter = 'Q2' THEN revenue ELSE 0 END) AS Q2,
    SUM(CASE WHEN quarter = 'Q3' THEN revenue ELSE 0 END) AS Q3,
    SUM(CASE WHEN quarter = 'Q4' THEN revenue ELSE 0 END) AS Q4,
    SUM(revenue) AS total
FROM sales
GROUP BY product;
```
**Why:** This `SUM(CASE ...)` pattern is the standard SQL way to pivot data without relying on vendor-specific pivot extensions. It evaluates each row, places the revenue in the correct column based on the quarter, and aggregates them up to the product level.

---

### Q9: Year-over-Year Growth
**Schema:** `revenue (year, month, amount)`

```sql
SELECT year, month, amount,
       LAG(amount) OVER (PARTITION BY month ORDER BY year) AS prev_year_amount,
       ROUND(
           (amount - LAG(amount) OVER (PARTITION BY month ORDER BY year)) * 100.0
           / NULLIF(LAG(amount) OVER (PARTITION BY month ORDER BY year), 0),
       2) AS yoy_growth_pct
FROM revenue
ORDER BY month, year;
```
**Why:** `LAG()` looks "backwards" to fetch a value from a previous row within the same window (partitioned by month, ordered by year, so it looks at the same month in the prior year). `NULLIF` is a crucial safety check to prevent a division-by-zero crash if the previous year had exactly `0` revenue.

---

### Q10: Consecutive Days Login (Gaps and Islands)
**Schema:** `logins (user_id, login_date)` (one row per login per day)

```sql
-- Find users who logged in for 3+ consecutive days
WITH numbered AS (
    SELECT user_id, login_date,
           login_date - ROW_NUMBER() OVER (PARTITION BY user_id ORDER BY login_date) * INTERVAL '1 day' AS grp
    FROM logins
)
SELECT user_id, MIN(login_date) AS streak_start, MAX(login_date) AS streak_end,
       COUNT(*) AS streak_days
FROM numbered
GROUP BY user_id, grp
HAVING COUNT(*) >= 3
ORDER BY user_id, streak_start;
```
**Why:** This is the classic **Gaps and Islands** technique. If a user logs in on the 1st, 2nd, and 3rd of the month, `ROW_NUMBER()` generates 1, 2, and 3. Subtracting the row number (as an interval of days) from the actual date results in the exact same base date for all consecutive days. This base date (`grp`) acts as a unique identifier for that "island" of activity.

---

## 11.3 Advanced — Window Functions, CTEs, Complex Logic

### Q11: Running Total and Moving Average
**Schema:** `transactions (id, account_id, txn_date, amount)`

```sql
SELECT account_id, txn_date, amount,
    SUM(amount) OVER (PARTITION BY account_id ORDER BY txn_date
                      ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS running_total,
    AVG(amount) OVER (PARTITION BY account_id ORDER BY txn_date
                      ROWS BETWEEN 6 PRECEDING AND CURRENT ROW) AS moving_avg_7day
FROM transactions
ORDER BY account_id, txn_date;
```
**Why:** The `ROWS BETWEEN` framing clause defines the explicit boundaries of the window. `UNBOUNDED PRECEDING` includes everything from the start of the partition up to the current row (a running sum). `6 PRECEDING` defines a rolling 7-day window (the current day + the 6 days prior).

---

### Q12: Delete Duplicate Rows (Keep One Copy)
**Schema:** `contacts (id, email, name)` — `id` is a primary key, but `email` has duplicates.

```sql
WITH dupes AS (
    SELECT id,
           ROW_NUMBER() OVER (PARTITION BY email ORDER BY id ASC) AS rn
    FROM contacts
)
DELETE FROM contacts 
WHERE id IN (SELECT id FROM dupes WHERE rn > 1);
```
**Why:** The CTE uses `ROW_NUMBER()` to assign an ascending integer to each email group. By ordering by `id ASC`, the oldest record gets `rn = 1`. Any row with `rn > 1` is a duplicate. The outer `DELETE` targets those duplicates by their unique `id`. This avoids complex self-joins and works flawlessly in PostgreSQL.

---

### Q13: Median Salary
**Schema:** `employees (emp_id, salary)`

```sql
SELECT PERCENTILE_CONT(0.5) WITHIN GROUP (ORDER BY salary) AS median_salary
FROM employees;
```
**Why:** PostgreSQL natively supports ordered-set aggregate functions. `PERCENTILE_CONT(0.5)` computes the continuous 50th percentile (the exact median), automatically interpolating between two values if there is an even number of rows. This completely replaces the need for complex, manual row-counting logic.

---

### Q14: Department with Highest Average Salary
**Schema:** `employees (emp_id, name, salary, dept_id)`, `departments (id, dept_name)`

```sql
SELECT dept_name, avg_salary FROM (
    SELECT d.dept_name, AVG(e.salary) AS avg_salary,
           RANK() OVER (ORDER BY AVG(e.salary) DESC) AS rnk
    FROM employees e
    JOIN departments d ON e.dept_id = d.id
    GROUP BY d.dept_name
) ranked
WHERE rnk = 1;
```
**Why:** We aggregate the average salary and apply a window function (`RANK()`) in the same subquery. Grouping happens first, so the window function evaluates the aggregated `AVG(salary)` over all departments. Filtering `rnk = 1` in the outer query safely handles ties if two departments share the exact top average.

---

### Q15: Employees with Salary Above Department Average
**Schema:** `employees (emp_id, name, salary, dept_id)`

```sql
SELECT name, salary, dept_id, dept_avg FROM (
    SELECT name, salary, dept_id,
           AVG(salary) OVER (PARTITION BY dept_id) AS dept_avg
    FROM employees
) t
WHERE salary > dept_avg;
```
**Why:** Window functions compute values across rows without collapsing them (unlike `GROUP BY`). By using `AVG(salary) OVER (PARTITION BY dept_id)`, every employee row gets a column containing their department's average, allowing a direct row-level comparison in the outer query without needing a messy self-join.

---

### Q16: Find Managers with at Least 5 Direct Reports
**Schema:** `employees (emp_id, name, manager_id)`

```sql
SELECT m.name AS manager, COUNT(e.emp_id) AS direct_reports
FROM employees e
INNER JOIN employees m ON e.manager_id = m.emp_id
GROUP BY m.emp_id, m.name
HAVING COUNT(e.emp_id) >= 5;
```
**Why:** We perform a self-join where the `e` table represents the direct reports and the `m` table represents the managers. We group by the manager's ID and filter out any managers who have fewer than 5 rows linked to them.

---

### Q17: Cumulative Sum that Resets
**Schema:** `events (id, user_id, event_date, points)` — running sum must reset whenever points are negative.

```sql
WITH groups AS (
    SELECT *, SUM(CASE WHEN points < 0 THEN 1 ELSE 0 END)
              OVER (PARTITION BY user_id ORDER BY event_date) AS grp
    FROM events
)
SELECT user_id, event_date, points,
       SUM(points) OVER (PARTITION BY user_id, grp ORDER BY event_date) AS running_points
FROM groups;
```
**Why:** This is a two-step window function problem. First, we create an artificial grouping ID (`grp`) by taking a running sum of a boolean condition (is it negative?). Every time a negative value appears, the `grp` ID increments. Second, we partition our actual running total by both the `user_id` *and* this new `grp` ID, effectively resetting the sum at every boundary.

---

### Q18: Swap Odd and Even Rows
**Schema:** `seat (id, student)` — swap adjacent students: row 1↔2, 3↔4, etc.

```sql
SELECT
    CASE
        WHEN id % 2 = 1 AND id = (SELECT MAX(id) FROM seat) THEN id
        WHEN id % 2 = 1 THEN id + 1
        ELSE id - 1
    END AS id,
    student
FROM seat
ORDER BY id;
```
**Why:** We use a `CASE` statement to dynamically alter the `id` values in the result set. Odd IDs become even (`+ 1`), and even IDs become odd (`- 1`). The first `WHEN` clause is a safety check: if the total number of students is odd, the very last student has no one to swap with, so their ID must remain unchanged.

---

### Q19: Tree Node Classification
**Schema:** `tree (id, p_id)` — `p_id` is the parent node ID; NULL means root.

```sql
SELECT id,
    CASE
        WHEN p_id IS NULL THEN 'Root'
        WHEN id IN (SELECT p_id FROM tree WHERE p_id IS NOT NULL) THEN 'Inner'
        ELSE 'Leaf'
    END AS type
FROM tree
ORDER BY id;
```
**Why:** A node is the Root if it has no parent. A node is an Inner node if it serves as a parent for at least one other node in the table. If it is neither, it is a Leaf. We use an `IN` subquery to check if the current node's `id` appears anywhere in the `p_id` column.

---

### Q20: Consecutive Numbers
**Schema:** `logs (id, num)` — find numbers that appear at least 3 times consecutively.

```sql
SELECT DISTINCT num AS ConsecutiveNums FROM (
    SELECT num,
           LAG(num, 1) OVER (ORDER BY id) AS prev,
           LEAD(num, 1) OVER (ORDER BY id) AS next
    FROM logs
) t
WHERE num = prev AND num = next;
```
**Why:** `LAG(num, 1)` fetches the previous row's number, and `LEAD(num, 1)` fetches the next row's number. If the current row's number perfectly matches both the previous and the next, it must be the middle of a 3-row consecutive streak. `DISTINCT` ensures we only return the number once, even if it appeared 4 or 5 times in a row.

---

## 11.4 Rapid-Fire Theory Questions (Verbal Interview)

**1. WHERE vs HAVING?** — `WHERE` filters rows before `GROUP BY` aggregates them; `HAVING` filters groups after aggregation.

**2. DELETE vs TRUNCATE vs DROP?** — `DELETE` removes row-by-row and can be rolled back. `TRUNCATE` rapidly deallocates the table's storage pages. `DROP` destroys the table schema entirely.

**3. CHAR vs VARCHAR?** — `CHAR` is fixed-length (pads with spaces). `VARCHAR` is variable-length (saves space).

**4. Primary Key vs Unique Key?** — A Primary Key guarantees uniqueness and `NOT NULL`, and a table can only have one. A Unique Key allows `NULL`s, and a table can have many.

**5. UNION vs UNION ALL?** — `UNION` deduplicates the combined results (slower). `UNION ALL` keeps all duplicates (faster).

**6. Clustered vs Non-Clustered Index?** — Clustered physically reorders the table data on disk (only 1 per table). Non-clustered is a separate b-tree pointer structure (many per table).

**7. Correlated vs Non-Correlated Subquery?** — A non-correlated subquery runs once. A correlated subquery references the outer query and must run row-by-row (often much slower).

**8. RANK vs DENSE_RANK vs ROW_NUMBER?** — Given ties: `ROW_NUMBER` assigns 1, 2, 3. `RANK` assigns 1, 1, 3 (leaves a gap). `DENSE_RANK` assigns 1, 1, 2 (no gap).

**9. What is a Deadlock?** — Two transactions each hold a lock that the other needs to proceed. Both wait forever until the database engine forcefully kills one.

**10. What makes a query non-SARGable?** — Applying functions to indexed columns in a `WHERE` clause (e.g., `WHERE YEAR(created_at) = 2026`), which forces a full table scan.

**11. ACID vs BASE?** — ACID guarantees strong consistency (SQL). BASE guarantees eventual consistency and high availability (NoSQL).

**12. What is normalization?** — Organizing tables to reduce data redundancy and anomalies (e.g., 1NF → 2NF → 3NF).

**13. What is denormalization?** — Intentionally adding redundancy back into normalized tables to improve read performance (avoiding expensive joins).

**14. What is a View?** — A stored query that acts as a virtual table. It stores no data itself (unless it is a Materialized View).

**15. What is an Index?** — A redundant, sorted data structure (usually a B-Tree) that speeds up reads at the cost of slightly slower writes and extra storage.

### References
1. Top SQL Interview Questions - GeeksForGeeks - https://www.geeksforgeeks.org/sql-interview-questions/
2. LeetCode SQL Problems - LeetCode - https://leetcode.com/problemset/database/
3. PostgreSQL Window Functions - PostgreSQL Documentation - https://www.postgresql.org/docs/current/tutorial-window.html
