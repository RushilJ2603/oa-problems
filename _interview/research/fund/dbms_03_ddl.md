# 3. Data Definition Language (DDL)

Data Definition Language (DDL) encompasses the SQL commands used to define, modify, and destroy the structural blueprint of your database objects (tables, views, indexes, schemas) rather than the data itself [1]. Because DDL operations define the schema (the formal structure and rules of the database), they are the foundation upon which all other database operations rest.

## 3.1 CREATE TABLE and Constraints

The `CREATE TABLE` statement is the foundation of every database. It creates a new, empty table in the current database. However, simply defining columns and their data types is rarely enough. A relational database guarantees data integrity by enforcing rules on what data is allowed. These rules are called constraints.

Every constraint must be understood not just as syntax, but as an active guardian of data quality. If an `INSERT` or `UPDATE` operation violates a constraint, the database rejects the operation entirely (a failure case to protect the integrity of the system).

### The Full Anatomy of CREATE TABLE

Here is the exhaustive anatomy of a table creation, using PostgreSQL syntax:

```sql
CREATE [TEMPORARY | TEMP] TABLE [IF NOT EXISTS] schema_name.table_name (
    -- Column definitions: name, type, and optional inline constraints
    column_name  data_type  [column_constraints],
    ...
    -- Table-level constraints (declared after all columns)
    [table_constraints]
);
```

### Column Constraints (Inline)

Constraints can be defined inline on a specific column. This is shorthand and applies the rule directly to that single column.

*   `PRIMARY KEY`: Uniquely identifies each row in a table. It is mathematically equivalent to combining a `UNIQUE` constraint and a `NOT NULL` constraint. A table can have at most one primary key.
*   `NOT NULL`: Ensures that the column must always contain a value. An attempt to insert an empty (null) value breaks the rule and fails.
*   `UNIQUE`: Guarantees that no two rows can share the same value in this column. (Unlike the primary key, a table can have multiple unique columns, and a unique column can often accept multiple null values since null is not equal to null).
*   `CHECK`: Enforces a specific logical condition that must evaluate to true for the row to be accepted (for example, ensuring a salary is positive).
*   `REFERENCES`: An inline foreign key. It dictates that the value in this column must exist in a specific column of another table.
*   `DEFAULT`: Not strictly a validation constraint, but a fallback rule. If an insert operation does not provide a value for this column, the database automatically inserts the specified default value.

```sql
CREATE TABLE employees (
    emp_id      INT           PRIMARY KEY,                  -- PK inline
    email       VARCHAR(255)  NOT NULL UNIQUE,              -- Two constraints applied
    first_name  VARCHAR(100)  NOT NULL,
    last_name   VARCHAR(100)  NOT NULL,
    salary      DECIMAL(10,2) NOT NULL CHECK (salary > 0),  -- Validation rule
    dept_id     INT           REFERENCES departments(id),   -- FK inline shorthand
    status      VARCHAR(20)   DEFAULT 'active',             -- Fallback value
    hire_date   DATE          DEFAULT CURRENT_DATE,
    bio         TEXT,                                       -- Nullable by default
    created_at  TIMESTAMP     DEFAULT CURRENT_TIMESTAMP
);
```

### Table-Level Constraints

When a constraint needs to span multiple columns, or if you simply prefer to give constraints explicit names for easier debugging, you define them at the table level after all columns are listed.

```sql
CREATE TABLE order_items (
    order_id    INT NOT NULL,
    product_id  INT NOT NULL,
    quantity    INT NOT NULL,
    unit_price  DECIMAL(10,2) NOT NULL,

    -- Composite Primary Key: The combination of both columns must be unique.
    CONSTRAINT pk_order_items   PRIMARY KEY (order_id, product_id),

    -- Named Foreign Keys
    CONSTRAINT fk_order         FOREIGN KEY (order_id)
                                REFERENCES orders(id)
                                ON DELETE CASCADE,

    CONSTRAINT fk_product       FOREIGN KEY (product_id)
                                REFERENCES products(id)
                                ON DELETE RESTRICT,

    -- Named CHECK constraint referencing a single column
    CONSTRAINT chk_quantity     CHECK (quantity > 0 AND quantity <= 10000),

    -- Named UNIQUE constraint spanning multiple columns
    CONSTRAINT uq_order_product UNIQUE (order_id, product_id)
);
```

### Referential Actions for Foreign Keys (ON DELETE / ON UPDATE)

When a foreign key connects a child table to a parent table, the database must enforce consistency. But what happens if you attempt to delete or update the parent row? A referential action dictates the database's automatic response.

::: heavy
**Heavy Concept: Referential Actions**
**Analogy:** Imagine a library where every Book (child) must belong to a registered Branch (parent). If the city decides to demolish a Branch, what happens to the Books?

- `CASCADE`: You throw all the books in the incinerator along with the branch. (Delete the parent, automatically delete the children).
- `RESTRICT`: The demolition crew arrives, sees books inside, and refuses to tear down the building. (Block the deletion of the parent entirely).
- `SET NULL`: You remove the branch's name from the books, leaving them in a pile without a home. (The parent is deleted, the child's reference becomes blank).

**Concrete Example:** An `orders` table references a `customers` table. If you delete customer #100, and the action is `RESTRICT`, the database returns an error: "Cannot delete customer #100, they have existing orders." If the action is `CASCADE`, customer #100 is deleted, and every order belonging to customer #100 is silently and automatically deleted as well.

**Plain English:** A referential action is a contingency plan. By appending `ON DELETE` or `ON UPDATE` to a foreign key, you instruct the database engine on how to handle modifications to the parent record to prevent orphaned child records.

**Technical (PostgreSQL Options):**
| Action | Behavior |
|---|---|
| `RESTRICT` | Blocks the parent delete/update immediately if any child rows exist. (Default behavior). |
| `NO ACTION` | Similar to `RESTRICT`, but deferred. The check happens at the end of the transaction, allowing intermediate steps. |
| `CASCADE` | Automatically deletes (or updates) the matching child rows to follow the parent. |
| `SET NULL` | Sets the foreign key column in all matching child rows to `NULL`. |
| `SET DEFAULT` | Sets the foreign key column in all matching child rows to their defined `DEFAULT` value. |

**The Trap:** Overusing `CASCADE` can lead to catastrophic data loss. A junior developer deletes a single company record, not realizing that `ON DELETE CASCADE` is set on departments, employees, and audit logs. The entire organization's data vanishes in milliseconds. Use `RESTRICT` by default for critical data.
:::

### Auto-Incrementing Primary Keys (PostgreSQL)

You rarely want to manually generate sequential ID numbers. PostgreSQL provides mechanisms to handle this automatically. The modern SQL-standard approach is the `IDENTITY` column.

```sql
-- Modern standard: GENERATED ALWAYS AS IDENTITY
CREATE TABLE users (
    id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    name VARCHAR(100)
);

-- Legacy PostgreSQL approach (still very common): SERIAL
CREATE TABLE products (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100)
);
```

The `GENERATED ALWAYS` clause strictly prevents users from manually inserting their own values into the ID column, whereas `SERIAL` technically allows a manual override (which can cause sequence desynchronization).

### Generated / Computed Columns

Sometimes a column's value should always be a direct mathematical calculation of other columns in the same row. A generated column automates this. In PostgreSQL, these are always `STORED` (physically written to disk).

```sql
CREATE TABLE line_items (
    id          INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    price       DECIMAL(10,2),
    tax_rate    DECIMAL(4,2),
    total_price DECIMAL(10,2) GENERATED ALWAYS AS (price * (1 + tax_rate)) STORED
);
```

### Temporary Tables

A temporary table is a scratchpad. It behaves like a normal table but exists only for the duration of your current database session. Once you disconnect, the database automatically destroys the table and all its data.

```sql
CREATE TEMPORARY TABLE temp_scoring (
    user_id INT, 
    score DECIMAL(5,2)
);
```
*Failure case:* If you attempt to access `temp_scoring` from a different database connection or terminal window, it will not exist.

### CREATE TABLE ... AS (CTAS)

You can create a new table and instantly populate it with the results of a `SELECT` query. This is called a CTAS operation. It is heavily used in analytics to snapshot complex queries into physical tables.

```sql
CREATE TABLE high_earners AS
    SELECT emp_id, first_name, last_name, salary 
    FROM employees 
    WHERE salary > 100000;
```

## 3.2 CREATE VIEW

A View is a stored query that behaves exactly like a virtual table. It stores the SQL instructions to fetch data, but it does not store the data itself.

When you query a view, the database engine transparently executes the underlying stored query, fetches the live data from the base tables, and returns the result.

**Why use views?**

1. **Simplicity:** Hide complex `JOIN` logic behind a simple interface.
2. **Security:** Restrict user access to a subset of rows or columns. You can grant someone the right to read a view that excludes salary columns, without granting them access to the raw employee table.

```sql
CREATE OR REPLACE VIEW active_employees AS
    SELECT emp_id, first_name, last_name, dept_id
    FROM employees
    WHERE status = 'active';

-- Querying the view is identical to querying a table
SELECT * FROM active_employees WHERE dept_id = 3;
```

### Updatable Views

In specific, simple scenarios, a view is updatable. If the view maps directly, one-to-one, back to a single underlying base table (with no aggregations like `GROUP BY`, no `JOIN`s, and no `DISTINCT` clauses), PostgreSQL allows you to run an `UPDATE` or `INSERT` against the view. The database engine will intelligently pass the modification down to the underlying table.

```sql
-- This UPDATE is passed through the view to modify the underlying `employees` table:
UPDATE active_employees SET last_name = 'Doe' WHERE emp_id = 42;
```

### Materialized Views

Unlike regular views, a Materialized View physically runs the query and stores the resulting data snapshot on disk. Because the data is pre-computed, querying a materialized view is incredibly fast.

**The Trade-off:** The data in a materialized view becomes stale immediately. When the base tables change, the materialized view does not automatically update. You must manually command the database to refresh the snapshot.

```sql
CREATE MATERIALIZED VIEW monthly_sales AS
    SELECT DATE_TRUNC('month', order_date) AS month, SUM(total) AS revenue
    FROM orders 
    GROUP BY 1;

-- This requires a manual refresh to see new orders:
REFRESH MATERIALIZED VIEW CONCURRENTLY monthly_sales;
```

## 3.3 CREATE INDEX

An index is a hidden data structure (usually a B-Tree) that the database builds alongside your table. Without an index, finding a specific row requires the database engine to scan every single row in the table from top to bottom (a sequential scan). With an index, the database traverses the tree structure to find the exact location of the data in milliseconds.

::: keypoint
Indexes are defined using DDL, but their impact is entirely on the performance of Data Manipulation Language (DML) queries. Every time you insert, update, or delete a row in the table, the database must also update the index. Therefore, over-indexing a table speeds up reading but severely slows down writing.
:::

```sql
-- Standard B-Tree index (default in PostgreSQL)
CREATE INDEX idx_emp_name ON employees (last_name);

-- Unique index (physically enforces uniqueness, identical to a UNIQUE constraint)
CREATE UNIQUE INDEX idx_emp_email ON employees (email);

-- Composite index (an index spanning multiple columns)
-- Column order matters heavily for how the query optimizer uses it.
CREATE INDEX idx_emp_dept_salary ON employees (dept_id, salary DESC);

-- Partial index (PostgreSQL feature to index only a subset of rows)
-- This saves massive amounts of disk space if you only ever search for active staff.
CREATE INDEX idx_active_emp ON employees (last_name) WHERE status = 'active';

-- Drop an index
DROP INDEX IF EXISTS idx_emp_name;
```

## 3.4 ALTER TABLE

The `ALTER TABLE` command modifies the structure of an existing table without dropping it. This allows you to evolve your schema while preserving the data inside.

```sql
-- Add a new column
ALTER TABLE employees ADD COLUMN middle_name VARCHAR(100);

-- Drop an existing column (destroys the data in that column)
ALTER TABLE employees DROP COLUMN middle_name;

-- Rename a column
ALTER TABLE employees RENAME COLUMN first_name TO given_name;

-- Change a column's data type
ALTER TABLE employees ALTER COLUMN salary TYPE NUMERIC(12,2);

-- Add a new constraint to an existing table
ALTER TABLE employees ADD CONSTRAINT chk_salary CHECK (salary > 0);

-- Drop a constraint
ALTER TABLE employees DROP CONSTRAINT chk_salary;

-- Set or Drop a column default value
ALTER TABLE employees ALTER COLUMN status SET DEFAULT 'active';
ALTER TABLE employees ALTER COLUMN status DROP DEFAULT;

-- Enforce or Remove NOT NULL rules
ALTER TABLE employees ALTER COLUMN email SET NOT NULL;
ALTER TABLE employees ALTER COLUMN bio DROP NOT NULL;

-- Rename the table itself
ALTER TABLE employees RENAME TO staff;
```

## 3.5 The Deletion Trap: TRUNCATE vs DROP vs DELETE

A universal concept—and frequent interview topic—is distinguishing the three ways to remove data in SQL. 

::: heavy
**Heavy Concept: TRUNCATE vs. DELETE vs. DROP**
**Analogy:** If your database table is a physical filing cabinet filled with paper folders:

- `DROP TABLE` means taking the entire cabinet to the dump and crushing it. The cabinet is gone, and the files are gone. The structure no longer exists.
- `DELETE FROM` means a clerk opens the cabinet, reads every single folder, removes them one by one, and painstakingly logs each removal in a ledger. The cabinet remains, the files are gone. Because of the ledger, this action is reversible if interrupted.
- `TRUNCATE TABLE` means turning the cabinet upside down and shaking all the folders into an incinerator. The cabinet remains, but the files are gone instantly. The logging is minimal.

**Concrete Example:** You have a `server_logs` table with 50 million rows. Running `DELETE FROM server_logs;` might take 10 minutes because the database engine writes 50 million individual deletion records to its internal transaction log. Running `TRUNCATE TABLE server_logs;` takes roughly five milliseconds.

**Plain English:** `TRUNCATE` is categorized as a DDL operation, not a DML operation like `DELETE`. It operates at the storage level, deallocating the physical data pages that store the table's rows rather than evaluating and deleting rows individually. 

**The Trap:** Because `TRUNCATE` bypasses row-by-row deletion, it **cannot activate `ON DELETE` triggers**. If your application relies on a trigger firing every time a row is deleted (perhaps to update an audit table), a `TRUNCATE` operation bypasses your audit system entirely.
*Note on Transactions:* In PostgreSQL, `TRUNCATE` **is** fully transactional. If you run `TRUNCATE` inside a transaction block and then issue a `ROLLBACK`, your data will be restored perfectly.
:::

```sql
-- DROP: Destroys the table structure and data entirely.
DROP TABLE IF EXISTS employees;
-- CASCADE drops objects that depend on this table (like views or foreign keys).
DROP TABLE IF EXISTS employees CASCADE;     

-- TRUNCATE: Instantly empties all rows, keeps the table structure.
TRUNCATE TABLE server_logs;
-- RESTART IDENTITY also resets any auto-incrementing sequences back to 1.
TRUNCATE TABLE server_logs RESTART IDENTITY;

-- DELETE: Row-by-row removal. It is fully logged and fires triggers.
DELETE FROM server_logs WHERE created_at < '2024-01-01';
```

## 3.6 Other DDL Objects in PostgreSQL

While tables are primary, PostgreSQL allows you to define other structural objects to organize and strictly type your data.

```sql
-- Create a Schema (a namespace or logical folder for tables)
CREATE SCHEMA IF NOT EXISTS analytics;
CREATE TABLE analytics.events (id INT, event_name TEXT);

-- Create a Sequence (an explicit standalone auto-increment generator)
CREATE SEQUENCE order_seq START WITH 1000 INCREMENT BY 1;
-- Fetching the next value advances the sequence globally.
SELECT NEXTVAL('order_seq');  -- Returns 1000, then 1001, etc.

-- Create a Domain (a reusable, customized data type with built-in constraints)
CREATE DOMAIN email_address AS VARCHAR(255) CHECK (VALUE ~ '^.+@.+\..+$');
-- Now you can use `email_address` as a data type in any table.
CREATE TABLE contacts (id INT, email email_address);

-- Create a Type (an explicit enumeration of allowed string values)
CREATE TYPE mood AS ENUM ('happy', 'sad', 'neutral');
CREATE TABLE diary (id INT, feeling mood);
```

### References
1. Data Definition Language (DDL) Overview - GeeksForGeeks - https://www.geeksforgeeks.org/sql-ddl-dql-dml-dcl-tcl-commands/
2. Difference between DELETE, DROP and TRUNCATE - StackOverflow - https://stackoverflow.com/questions/1169992/difference-between-truncate-delete-and-drop
3. PostgreSQL Official Documentation: Data Definition - PostgreSQL - https://www.postgresql.org/docs/current/ddl.html
