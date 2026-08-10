-- LEFT JOIN keeps every customer, then "the order side is NULL" selects exactly the ones the join
-- found nothing for. Written this way it is immune to NULLs in orders.customer_id, which is the
-- trap that breaks the NOT IN version.
SELECT c.name
FROM customers c
LEFT JOIN orders o ON o.customer_id = c.id
WHERE o.id IS NULL;
