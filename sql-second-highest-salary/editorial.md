# Second Highest Salary

## The question is not "find the second row"

Two things make this harder than it looks, and both are about what happens when the answer does not
exist.

**1. Distinct, not second-largest-row.** With salaries `300, 300, 200`, the second *row* by salary is
another `300`. The second distinct *salary* is `200`. `ORDER BY salary DESC LIMIT 1 OFFSET 1` without
`DISTINCT` returns 300 and is wrong — `tests/edge/04.in` is exactly that table.

**2. "No answer" must still be a row.** This is the part that fails most submissions. A plain

```sql
SELECT DISTINCT salary FROM employee ORDER BY salary DESC LIMIT 1 OFFSET 1;
```

is correct whenever a second salary exists and returns **zero rows** when it does not. The problem
demands one row containing `NULL`. Zero rows and one NULL row are different result sets, and the
judge compares result sets.

The fix is to wrap it in a **scalar subquery**:

```sql
SELECT (
    SELECT DISTINCT salary FROM employee ORDER BY salary DESC LIMIT 1 OFFSET 1
) AS second_highest;
```

The outer `SELECT` has no `FROM`, so it always produces exactly one row, and a scalar subquery that
matches nothing evaluates to `NULL`. That single construction handles the empty table, the
one-row table and the all-identical table at once — no `CASE`, no `IFNULL`, no special-casing.

## Alternatives worth knowing

```sql
-- MAX of everything strictly below the MAX. Aggregates over an empty set return NULL, so this
-- gets the empty case right for free too.
SELECT MAX(salary) AS second_highest
FROM employee
WHERE salary < (SELECT MAX(salary) FROM employee);
```

```sql
-- Window function. DENSE_RANK (not RANK) is required: RANK skips ranks after ties, so with
-- 300, 300, 200 the value 200 gets rank 3 and the query returns nothing.
SELECT MAX(CASE WHEN rk = 2 THEN salary END) AS second_highest
FROM (SELECT salary, DENSE_RANK() OVER (ORDER BY salary DESC) rk FROM employee);
```

The `MAX(salary) WHERE salary < MAX(salary)` version is the one to reach for in an interview: it is
short, it needs no window support, and its empty-set behaviour is the correct behaviour rather than
a special case you had to remember.

## The traps, and the tests that catch them

| Trap | Test |
| --- | --- |
| Forgetting `DISTINCT` | `edge/04` — `300, 300, 200` |
| Returning zero rows instead of `NULL` | `edge/01` (empty), `edge/02` (one row), `edge/03` (all equal) |
| `RANK` instead of `DENSE_RANK` | `edge/04`, `edge/08` |
| Assuming salaries are positive | `edge/06`, `edge/07` (negatives and zero) |
