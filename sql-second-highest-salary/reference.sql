-- The scalar subquery is the point: it yields exactly one row even when there is no second
-- salary, and an empty scalar subquery evaluates to NULL rather than to no row at all.
SELECT (
    SELECT DISTINCT salary
    FROM employee
    ORDER BY salary DESC
    LIMIT 1 OFFSET 1
) AS second_highest;
