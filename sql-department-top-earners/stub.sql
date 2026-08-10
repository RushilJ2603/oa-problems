-- For each department, report every employee earning one of the top 3 DISTINCT salaries there.
-- Output columns: department name, employee name, salary.
-- Ordered by department name ASC, then salary DESC, then employee name ASC.
-- WRITE YOUR CODE HERE
SELECT d.name, e.name, e.salary FROM employees e JOIN departments d ON d.id = e.department_id WHERE 0;
