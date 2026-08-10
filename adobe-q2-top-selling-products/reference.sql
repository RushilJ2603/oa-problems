-- The filter is on an AGGREGATE of the group (the summed quantity), so it belongs in HAVING, not in
-- WHERE: WHERE runs before the rows are grouped and can only see one sale at a time.
-- SUM(QuantitySold) > 100, not COUNT(*) > 100 — "sold more than 100 times" is about units, and a
-- product can clear it in two transactions (Widget A) or fail it across a hundred (quantity 0).
SELECT p.ProductName,
       ROUND(SUM(s.QuantitySold * p.Price), 2) AS TotalSalesAmount
FROM Sales s
JOIN Products p ON p.ProductID = s.ProductID
GROUP BY p.ProductID, p.ProductName
HAVING SUM(s.QuantitySold) > 100
ORDER BY TotalSalesAmount DESC;
