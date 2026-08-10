-- DENSE_RANK, not RANK: "top three salaries" means three distinct salary VALUES, and RANK skips
-- numbers after a tie (1,1,3) so a genuine third-highest salary would be excluded.
SELECT d.name, e.name, e.salary
FROM (
    SELECT name, salary, department_id,
           DENSE_RANK() OVER (PARTITION BY department_id ORDER BY salary DESC) AS rk
    FROM employees
) e
JOIN departments d ON d.id = e.department_id
WHERE e.rk <= 3
ORDER BY d.name ASC, e.salary DESC, e.name ASC;
