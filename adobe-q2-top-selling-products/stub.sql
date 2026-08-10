-- Report ProductName and TotalSalesAmount for every product whose TOTAL QuantitySold exceeds 100.
-- TotalSalesAmount = sum of QuantitySold * Price over that product's sales, rounded to 2 decimals.
-- Ordered by TotalSalesAmount descending.
-- WRITE YOUR CODE HERE
SELECT p.ProductName, 0.00 AS TotalSalesAmount
FROM Products p
WHERE 0;
