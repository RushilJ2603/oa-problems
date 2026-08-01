# 6. Data Control & Transaction Control (DCL/TCL)

Database security and concurrency are managed through Data Control Language (DCL) and Transaction Control Language (TCL). Understanding these two languages is essential for writing applications that secure sensitive information and do not corrupt data under heavy, simultaneous load.

## 6.1 Data Control Language (DCL) and Roles

Data Control Language (DCL) commands manage permissions and access rights. A database is rarely accessed by a single almighty administrator. In a real system, multiple users, backend application servers, and reporting tools all connect simultaneously. DCL ensures that each connection has exactly the permissions it needs, and nothing more.

In PostgreSQL, permissions are managed via a **Role**. A role is an entity that can own database objects and have database privileges (the right to perform a specific action, like reading or inserting). A role can act as a specific user (if given a password to log in) or as a group (a collection of permissions that multiple users can inherit).

### GRANT

The `GRANT` command issues specific privileges on a database object to a role.

```sql
-- Grant specific privileges on a single table
GRANT SELECT, INSERT, UPDATE ON employees TO application_role;

-- Grant highly destructive privileges to an admin role
GRANT DELETE ON employees TO admin_role;

-- Grant all available privileges on a table
GRANT ALL PRIVILEGES ON employees TO admin_role;

-- Column-level precision: Grant access to specific columns only.
-- Useful for hiding sensitive data like salaries.
GRANT SELECT (first_name, last_name, email), UPDATE (email) ON employees TO support_role;

-- Schema-level grant: Grant read access on every existing table in a schema (folder).
GRANT SELECT ON ALL TABLES IN SCHEMA public TO readonly_role;

-- Grant with the ability for the recipient to re-grant the privilege to others.
GRANT SELECT ON employees TO lead_analyst WITH GRANT OPTION;

-- Grant execute permission to allow a role to run a stored function.
GRANT EXECUTE ON FUNCTION calculate_bonus(INT) TO hr_role;
```

### REVOKE

The `REVOKE` command retracts privileges that were previously granted.

```sql
-- Revoke specific privileges
REVOKE INSERT, UPDATE ON employees FROM application_role;

-- Revoke all privileges
REVOKE ALL PRIVILEGES ON employees FROM admin_role;

-- Revoke only the ability to re-grant, keeping the underlying privilege intact.
REVOKE GRANT OPTION FOR SELECT ON employees FROM lead_analyst;

-- Cascade revoke: If lead_analyst used their GRANT OPTION to give the 
-- privilege to a junior analyst, CASCADE revokes it from the junior analyst as well.
REVOKE SELECT ON employees FROM lead_analyst CASCADE;
```

### Role Management and Row-Level Security

```sql
-- Create a user role (can log into the database)
CREATE ROLE reporting_user WITH LOGIN PASSWORD 'secure_pass_123';

-- Create a group role (cannot log in directly, acts as a permissions container)
CREATE ROLE analyst_group NOLOGIN;

-- Assign the group role to the user, granting them all analyst privileges
GRANT analyst_group TO reporting_user;

-- Drop (delete) a role entirely
DROP ROLE IF EXISTS analyst_group;
```

PostgreSQL also supports **Row-Level Security (RLS)**. While standard `GRANT` commands filter which *tables* or *columns* a user can see, RLS filters which *rows* a user can see.

```sql
-- Enable RLS on the table
ALTER TABLE employees ENABLE ROW LEVEL SECURITY;

-- Create a policy so users can only see rows belonging to their own department
CREATE POLICY emp_department_policy ON employees
    FOR SELECT
    USING (dept_id = current_setting('app.current_dept')::INT);
```

## 6.2 Transaction Control & ACID Properties

A transaction is a logical unit of work that contains one or more SQL statements. A database must guarantee that a transaction executes completely and safely, even if a power cord is pulled mid-execution, or if two servers try to modify the same data at the exact same millisecond. 

To maintain data integrity, relational databases guarantee the **ACID** properties:

*   **Atomicity:** The "all-or-nothing" rule. If a transaction contains five `UPDATE` statements, and the fifth one fails, the database automatically undoes the first four. A transaction cannot partially complete.
*   **Consistency:** The transaction must transition the database from one valid state to another valid state. All constraints (like `NOT NULL` or `CHECK`) must be honored. If a transaction attempts to violate a constraint, it is rejected entirely.
*   **Isolation:** Concurrent transactions execute as if they are the only transaction running on the system. They must not interfere with each other's intermediate, uncommitted states. (We will explore this heavily in Section 6.3).
*   **Durability:** Once the database engine confirms a transaction is committed, the changes are permanent. They are written to non-volatile storage and will survive a hard crash or power failure.

### TCL Commands (Transaction Control Language)

You manage transactions explicitly using TCL commands.

```sql
-- Begin a new transaction block
BEGIN;

-- Commit the transaction, permanently saving all changes to disk
COMMIT;

-- Rollback the transaction, instantly undoing all changes made since BEGIN
ROLLBACK;
```

You can also create a **Savepoint** within a transaction. This allows you to partially roll back to a specific checkpoint without abandoning the entire transaction.

```sql
BEGIN;
UPDATE accounts SET balance = balance - 1000 WHERE id = 1;

-- Create a checkpoint
SAVEPOINT before_risky_update;
UPDATE accounts SET balance = balance + 1000 WHERE id = 2;

-- If the second update hits a constraint error (e.g., balance exceeded limit):
ROLLBACK TO SAVEPOINT before_risky_update;

-- The first update (id = 1) is preserved. We can now try something else or commit.
COMMIT;
```

### Practical Transaction Example: A Bank Transfer

A classic example of atomicity is transferring money. It fundamentally requires two steps: subtracting from Account A, and adding to Account B. If the database crashes between the two steps, money vanishes. A transaction prevents this.

```sql
BEGIN;

-- Step 1: Debit from account A
UPDATE accounts SET balance = balance - 500.00
WHERE account_id = 'A' AND balance >= 500.00;

-- Step 2: Credit to account B
UPDATE accounts SET balance = balance + 500.00
WHERE account_id = 'B';

-- Step 3: Permanently apply both changes
COMMIT;
-- If the server loses power during Step 2, the database restarts, 
-- sees an uncommitted transaction, and completely reverses Step 1.
```

## 6.3 The Isolation Trap: Read Phenomena

Concurrency is fundamentally unintuitive. If 100 users try to read and write the exact same rows simultaneously, the database must use locks to prevent chaos. However, locking every row for every query halts performance to a crawl. You can tune the trade-off between strict accuracy and high performance using **Isolation Levels**. To tune them safely, you must understand the bugs—known as read phenomena—that loose isolation levels allow.

::: heavy
**Heavy Concept: Read Phenomena & Isolation Levels**
**Analogy:** Imagine a shared Google Doc being edited by your coworker.

- **Dirty Read:** You read a paragraph your coworker just typed. Based on that paragraph, you make a decision. But your coworker hasn't hit 'Save' yet, and they suddenly hit `Ctrl+Z` to erase it. You just acted on information that technically never existed in the permanent record.
- **Non-Repeatable Read:** You read the title of the document. You look away to check your notes. You look back, and the title is entirely different because your coworker just saved a change. Your read cannot be repeated.
- **Phantom Read:** You count the number of bullet points in a list (there are 5). You look away. You look back and recount, and now there are 6, because a coworker just inserted a brand new bullet point.

**Concrete Example (Watch a Non-Repeatable Read happen):** 
You are building an accounting app to sum a user's net worth. The user has a Checking account ($500) and a Savings account ($500). Total: $1000.
*Time 1:* Your app (Transaction 1) starts querying. It reads Checking: $500.
*Time 2:* Before your app reads Savings, a scheduled bill payment (Transaction 2) fires. It transfers $100 from Checking to Savings. Checking is now $400, Savings is $600. Transaction 2 commits.
*Time 3:* Your app (Transaction 1) resumes and reads Savings. It sees the new, committed value: $600.
*Time 4:* Your app sums the values it read: $500 (Checking, read at Time 1) + $600 (Savings, read at Time 3) = **$1100**.
*Failure case:* Money was double-counted. The database state was entirely valid, but because the isolation level allowed a row to change *between* your reads, your transaction calculated an impossible reality. This breaks when absolute point-in-time consistency across multiple rows is required.

**Plain English:** The SQL standard defines four Isolation Levels. As you move up the ladder, the database engine enforces stricter locking, preventing more phenomena, but severely slowing down simultaneous users.

**Technical (The Four Levels):**

1. **Read Uncommitted:** The database does zero locking. Allows Dirty Reads, Non-Repeatable Reads, and Phantom Reads. Extremely fast, but offers virtually no data integrity. (PostgreSQL safely treats this identically to `Read Committed`).
2. **Read Committed:** (The default in PostgreSQL). Prevents Dirty Reads. You only read committed data. However, as the bank example showed, if a separate transaction modifies a row while your transaction is running, a second read of that row yields a different result (Non-Repeatable Read).
3. **Repeatable Read:** Prevents Dirty and Non-Repeatable reads. If you read a row, the database engine guarantees that if you read it again in the same transaction, it will be identical. It achieves this by taking a snapshot. However, standard SQL says a separate transaction could still `INSERT` a brand new row that matches your query conditions (Phantom Read).
4. **Serializable:** The strictest level. The database guarantees that if transactions run concurrently, the result will be identical to as if they were forced to run sequentially, one-by-one in a queue. Prevents all phenomena, but causes massive lock contention, causing transactions to wait or fail entirely.
:::

### Isolation Level Summary Table

| Isolation Level | Dirty Read | Non-Repeatable Read | Phantom Read | Performance |
|---|---|---|---|---|
| **Read Uncommitted** | Possible | Possible | Possible | Fastest |
| **Read Committed** (Default) | Prevented | Possible | Possible | Fast |
| **Repeatable Read** | Prevented | Prevented | Possible (Prevented in Postgres*) | Moderate |
| **Serializable** | Prevented | Prevented | Prevented | Slowest |

*\*Note: PostgreSQL's implementation of Repeatable Read is highly advanced and actually prevents Phantom Reads as well, though the SQL standard allows them.*

### Explicit Row Locking (`SELECT ... FOR UPDATE`)

Instead of changing the global isolation level to Serializable, which slows down the entire system, you can use explicit row-level locking. By adding `FOR UPDATE` to a `SELECT` query, you command the database to lock the specific rows you just read, preventing any other transaction from modifying them until your transaction commits.

```sql
BEGIN;

-- Lock the specific row for Account 'A'. 
-- Any other transaction trying to modify Account 'A', or lock it, will PAUSE and WAIT.
SELECT balance FROM accounts WHERE account_id = 'A' FOR UPDATE;

-- Safe to perform calculations here without fear of another transaction interfering
UPDATE accounts SET balance = balance - 500 WHERE account_id = 'A';

COMMIT;
-- The lock is released upon COMMIT. Waiting transactions can now proceed.
```

Advanced locking options for high-concurrency systems:
```sql
-- FOR UPDATE NOWAIT: Instead of waiting indefinitely for another transaction 
-- to release its lock, the database immediately throws an error so your app can retry.
SELECT * FROM accounts WHERE account_id = 'A' FOR UPDATE NOWAIT;

-- FOR UPDATE SKIP LOCKED: Extremely useful for job queues. 
-- It queries for rows, but simply skips over any rows that are currently locked 
-- by other workers, ensuring no two workers process the same job, without waiting.
SELECT * FROM background_tasks 
WHERE status = 'pending'
ORDER BY created_at LIMIT 1
FOR UPDATE SKIP LOCKED;
```

### References
1. Transaction Isolation Levels - PostgreSQL Docs - https://www.postgresql.org/docs/current/transaction-iso.html
2. Row-Level Security - PostgreSQL Docs - https://www.postgresql.org/docs/current/ddl-rowsecurity.html
3. Explicit Locking - PostgreSQL Docs - https://www.postgresql.org/docs/current/explicit-locking.html
