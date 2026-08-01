# 7. Query Optimization & Execution Under the Hood

When you write a SQL query, you are describing *what* data you want, not *how* to get it. The database engine's job is to figure out the "how." Understanding this lifecycle separates developers who guess at performance from those who engineer it.

## 7.1 The Query Lifecycle

Every SQL query passes through three main phases before returning data:

1. **Parser:** Checks the syntax and semantics. Are the keywords correct? Do the tables and columns actually exist? Does the user have permission to see them?
2. **Optimizer:** The brain of the database. It generates multiple possible "Execution Plans" (strategies for retrieving the data) and picks the one it estimates will be fastest.
3. **Executor:** The engine that runs the chosen execution plan. It interacts with the storage engine to fetch physical blocks of data from memory or disk, following the exact steps the optimizer laid out.

## 7.2 Reading Execution Plans

To see the optimizer's chosen plan in PostgreSQL, you use the `EXPLAIN` command. 

```sql
-- Shows the estimated plan WITHOUT executing the query.
EXPLAIN SELECT * FROM employees WHERE dept_id = 3;

-- Actually EXECUTES the query and shows real timing + row counts.
EXPLAIN ANALYZE SELECT * FROM employees WHERE dept_id = 3;

-- Maximum detail: includes buffer (memory/disk) hits and outputs as JSON.
EXPLAIN (ANALYZE, BUFFERS, FORMAT JSON) SELECT * FROM employees WHERE dept_id = 3;
```

::: heavy
**Heavy Concept: Execution Plan Operators**
**Analogy:** Imagine being told to find every employee in the marketing department and match them with their office floor. You could walk to every single desk in the company and ask (Table Scan), or you could look up "Marketing" in the company directory and only visit those desks (Index Scan). Once you have the names, you could look up each person one by one in the floor directory (Nested Loop), or you could memorize the floor directory first and just check your memory (Hash Join).

**Plain English:** An execution plan is a tree of "operators." Data flows from the bottom (leaf nodes) up to the top. Each operator represents a specific physical algorithm the executor uses to retrieve or combine data. 
:::

**Scan Operators (How data is read from tables/indexes):**

- **Seq Scan (Sequential Scan):** The executor physically reads every single page of the table from disk to memory, checking every row against the `WHERE` clause. This is necessary if you need most of the table, but devastatingly slow if you only need a few rows from a massive table.
- **Index Scan:** The executor traverses a B-Tree index structure to find the exact locations of the requested rows, then visits the main table (the heap) to retrieve the rest of the row data. 
- **Index Only Scan:** The executor finds the data it needs purely within the index structure and does not need to visit the main table at all. This is the fastest possible retrieval method, provided the index "covers" all columns requested in the `SELECT` clause.
- **Bitmap Index Scan & Bitmap Heap Scan:** When reading many rows from an index, visiting the table for each row individually causes random I/O. Instead, Postgres first scans the index to build a "bitmap" (a list of memory blocks where the matching rows live) via a *Bitmap Index Scan*. Then, a *Bitmap Heap Scan* visits those physical blocks sequentially. This is highly efficient for range queries or when combining multiple indexes (e.g., `WHERE status = 'active' OR dept_id = 3`).

**Join Operators (How two datasets are combined):**

- **Nested Loop:** For every single row in the first (outer) dataset, the executor scans the second (inner) dataset to find matches. Excellent when the outer set is very small and the inner set has an index on the join column.
- **Hash Join:** The executor takes the smaller of the two datasets and builds an in-memory hash table keyed by the join column. It then scans the larger dataset one row at a time, probing the hash table for matches. The go-to method for joining large, unsorted datasets.
- **Merge Join:** If both datasets are already sorted by the join column (perhaps because they were read via an Index Scan), the executor steps through both sets simultaneously, merging them together. Excellent for massive datasets that are already ordered.

## 7.3 The Cost-Based Optimizer (CBO)

Historically, databases used Rule-Based Optimizers (e.g., "if an index exists, always use it"). Today, PostgreSQL and all major RDBMS use a **Cost-Based Optimizer (CBO)**.

::: heavy
**Heavy Concept: Cost-Based Optimizer & Statistics**
**Analogy:** You need to drive from New York to Boston. A Rule-Based GPS says "Always take the highway because highways are faster." A Cost-Based GPS checks the live traffic data (statistics) and says "The highway is jammed with 10 miles of stopped cars; today, the backroads will cost 30 fewer minutes."

**Example:** You query `SELECT * FROM users WHERE status = 'active'`. If 99% of users are 'active', using an index requires reading the index *and* the table, which is slower than just reading the table directly. The CBO calculates this and chooses a Seq Scan. If only 1% are 'active', the CBO calculates that an Index Scan is cheaper.

**Plain English:** The CBO calculates a mathematical "cost" for every possible execution plan by estimating CPU cycles, memory usage, and disk I/O. To make accurate estimates, it relies entirely on **Statistics**—metadata about your tables. Statistics include the total row count, the number of distinct values in each column, and data distribution histograms.

**The Trap: Stale Statistics**
A common production disaster is a query that ran in 1 second yesterday suddenly taking 5 minutes today, even though the query didn't change. 
*Failure case:* This breaks when you do a massive data load (e.g., inserting 10 million rows) but the database statistics have not been updated. The CBO still thinks the table has 1,000 rows. It chooses a Nested Loop join (great for small tables) instead of a Hash Join, resulting in billions of CPU cycles. 

**Question to sit with:** If a table is extremely small (e.g., 50 rows), will the CBO ever choose an Index Scan over a Sequential Scan? Why or why not?
:::

In PostgreSQL, the `ANALYZE` command updates these statistics. The autovacuum daemon usually runs this automatically in the background, but manual runs are required immediately after bulk data changes.

```sql
-- Update statistics for a specific table
ANALYZE employees;

-- Update statistics for the entire database
ANALYZE;
```

## 7.4 SARGable Queries (The Index Killer)

When tuning a slow query, developers often add an index, only to find the query is *still* slow. This is usually because the query is not **SARGable**.

::: heavy
**Heavy Concept: SARGability (Search ARGument-ABLE)**
**Analogy:** Looking for someone named "Smith" in a phone book. If I ask "Find Smith," you jump straight to the 'S' section and use the alphabetized nature of the book to find the exact page. If I ask "Find everyone whose last name has exactly 5 letters," the alphabetical order doesn't help you at all. You have to read every single name in the book from page 1 to 1000, counting the letters.

**Example:** Consider `WHERE UPPER(name) = 'JOHN'`. The index on `name` stores names in their original case ('John', 'jOhN', 'JOHN'). The database cannot know which of those entries will equal 'JOHN' after the `UPPER()` function is applied without actually applying the function to every row in the index.

**Plain English:** A query is SARGable if the database engine can effectively use an index to jump straight to the data. If you wrap an indexed column in a function, perform arithmetic on it, or use a leading wildcard, the database must evaluate that expression for every single row, rendering the index useless and forcing a Seq Scan.

**Technical:** To utilize a B-Tree index, the search argument must be an operator that matches the index's sort order (e.g., `=`, `>`, `<`). 

**Alternative rejected:** You could fetch all rows into your application memory (e.g., in Python or Java) and filter the data there using flexible code. But this sacrifices database-level indexing entirely, incurs massive network transfer costs, and shifts the CPU burden to the app server.
:::

### SARGable vs Non-SARGable — Examples

| Non-SARGable (Bad) | SARGable (Good) | Why |
|---|---|---|
| `WHERE EXTRACT(YEAR FROM order_date) = 2025` | `WHERE order_date >= '2025-01-01' AND order_date < '2026-01-01'` | Function on column hides the value |
| `WHERE salary + 1000 > 50000` | `WHERE salary > 49000` | Arithmetic on column hides the value |
| `WHERE LEFT(name, 3) = 'Joh'` | `WHERE name LIKE 'Joh%'` | Function on column |
| `WHERE name LIKE '%son'` | Cannot be SARGable (leading wildcard) | Alphabetical sort is useless if the first letter is unknown |
| `WHERE id::TEXT = '42'` | `WHERE id = 42` | Type casting forces evaluation |

In PostgreSQL, you can fix some non-SARGable queries by creating an **Expression Index** that pre-computes the function:

```sql
-- The index stores the uppercase version of the name
CREATE INDEX idx_upper_name ON employees (UPPER(name));

-- Now this query IS SARGable, because it matches the indexed expression exactly:
SELECT * FROM employees WHERE UPPER(name) = 'JOHN';
```

## 7.5 Common Performance Anti-Patterns

```sql
-- Anti-pattern 1: SELECT * (fetches all columns)
-- This defeats Index Only Scans because the index likely doesn't cover every column.
SELECT * FROM employees;             -- Bad
SELECT name, salary FROM employees;  -- Good: only fetch what you need

-- Anti-pattern 2: Correlated subquery (runs inner query per row)
-- For every employee, the database executes the orders count query. (N+1 queries)
SELECT name, (SELECT COUNT(*) FROM orders WHERE orders.emp_id = e.id) 
FROM employees e;                    -- Bad
-- Rewrite as a JOIN so the optimizer can use Hash or Merge joins:
SELECT e.name, COUNT(o.id) FROM employees e
LEFT JOIN orders o ON o.emp_id = e.id GROUP BY e.name;

-- Anti-pattern 3: DISTINCT to hide a bad JOIN
-- Masks duplicate rows resulting from an incorrect one-to-many join relationship.
SELECT DISTINCT e.name FROM employees e
JOIN orders o ON o.emp_id = e.id;    -- Bad
-- Fix the JOIN logic or use an EXISTS clause instead of using DISTINCT as a band-aid.

-- Anti-pattern 4: ORDER BY + LIMIT without an index
-- Without an index on created_at, the database must sort ALL rows in memory, then return 10.
SELECT * FROM logs ORDER BY created_at DESC LIMIT 10;
-- Fix: CREATE INDEX idx_logs_created ON logs (created_at DESC);
```

### References
1. Using EXPLAIN - PostgreSQL Docs - https://www.postgresql.org/docs/current/using-explain.html
2. Planner Statistics - PostgreSQL Docs - https://www.postgresql.org/docs/current/planner-stats.html
3. SARGable queries - SQL Authority - https://blog.sqlauthority.com/
4. Index Tuning - Brent Ozar - https://www.brentozar.com/
