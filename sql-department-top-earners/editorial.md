# Department Top Earners

## "Top three salaries" is not "top three rows"

Everything here follows from one sentence in the statement: three highest **distinct salaries**, not
three highest-paid people. In the example, IT has two employees on 85000 and both are reported, so
the department returns four rows. Any solution built on `LIMIT 3` returns three and is wrong.

That also rules out the tempting per-group `LIMIT`, which SQL does not offer anyway — you cannot
write `LIMIT 3` "per department" without a lateral join or a correlated subquery.

## DENSE_RANK, and why not RANK

```sql
SELECT d.name, e.name, e.salary
FROM (
    SELECT name, salary, department_id,
           DENSE_RANK() OVER (PARTITION BY department_id ORDER BY salary DESC) AS rk
    FROM employees
) e
JOIN departments d ON d.id = e.department_id
WHERE e.rk <= 3
ORDER BY d.name ASC, e.salary DESC, e.name ASC;
```

`PARTITION BY department_id` restarts the ranking for each department; `ORDER BY salary DESC` ranks
highest first. The choice of ranking function is the whole question:

| Salaries | `RANK()` | `DENSE_RANK()` | `ROW_NUMBER()` |
| --- | --- | --- | --- |
| 9, 9, 8, 7 | 1, 1, **3**, 4 | 1, 1, **2**, 3 | 1, 2, 3, 4 |

With `RANK`, the tie at 9 consumes rank 2, so 8 lands at rank 3 and **7 is excluded** — even though
7 is the third distinct salary. With `ROW_NUMBER`, the second 9 gets rank 2 and one of the two
top earners is silently dropped. Only `DENSE_RANK` counts *distinct values*, which is exactly what
the problem asks for. `tests/edge/05.in` is that table.

## Why the join is an INNER join

An employee with a NULL `department_id`, or one pointing at a department that no longer exists, is
not in any department and must not be reported. `JOIN` drops them; `LEFT JOIN` would keep them with a
NULL department name and produce phantom rows. `tests/edge/10.in` contains one of each.

Rank *before* joining, as the reference does. Ranking after a join still works here, but it makes the
window depend on the join's row multiplicity — a habit that breaks the moment the join is not
one-to-many in the direction you assumed.

## Without window functions

Worth knowing, because plenty of interviews still ask for it:

```sql
SELECT d.name, e.name, e.salary
FROM employees e
JOIN departments d ON d.id = e.department_id
WHERE (SELECT COUNT(DISTINCT e2.salary)
       FROM employees e2
       WHERE e2.department_id = e.department_id AND e2.salary > e.salary) < 3
ORDER BY d.name ASC, e.salary DESC, e.name ASC;
```

"Fewer than three distinct salaries above mine" is the definition of top-three, stated directly.
`COUNT(DISTINCT …)` is doing the same work `DENSE_RANK` does. It is `O(n²)` per department, which is
fine at these sizes and is the answer to give if the interviewer bans window functions.

## The ordering is graded

Unlike most SQL problems here, this one specifies an order, so it is judged with row order
significant. Two details:

- Sort by department **name**, not `department_id` — `tests/edge/08.in` has department `B` with id 1
  and `A` with id 2, so sorting by id produces the wrong order.
- The final `name ASC` tie-break matters whenever two people in a department share a salary
  (`tests/edge/09.in`), otherwise the answer is not deterministic.

## The traps, and the tests that catch them

| Trap | Test |
| --- | --- |
| `LIMIT 3` / `ROW_NUMBER` instead of `DENSE_RANK` | `edge/05`, `sample/02` |
| `RANK` skipping the third distinct salary | `edge/05` |
| Reporting NULL / orphan departments | `edge/10` |
| Ordering by department id instead of name | `edge/08` |
| Missing the name tie-break | `edge/09` |
| Assuming salaries are positive | `edge/11` |
| Departments with fewer than 3 distinct salaries | `edge/01`, `edge/02`, `edge/03` |
