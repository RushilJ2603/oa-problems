# Top Selling Products

```sql
SELECT p.ProductName,
       ROUND(SUM(s.QuantitySold * p.Price), 2) AS TotalSalesAmount
FROM Sales s
JOIN Products p ON p.ProductID = s.ProductID
GROUP BY p.ProductID, p.ProductName
HAVING SUM(s.QuantitySold) > 100
ORDER BY TotalSalesAmount DESC;
```

Six lines. Every one of them is a place people lose the question.

## "Sold more than 100 times" is about units, not rows

This is the trap the problem is built on, and the sample gives it away if you read it carefully.
Widget A has **two** sale rows — 50 and 60 — and it *does* qualify. So the test is

```sql
HAVING SUM(s.QuantitySold) > 100      -- not COUNT(*) > 100
```

`COUNT(*)` counts transactions. With two transactions Widget A would fail, and the sample output
would be empty. `edge/02` runs the trap in the other direction: 150 transactions of quantity `0`, so
`COUNT(*) = 150` but nothing was actually sold, and the product must **not** appear.

## HAVING, not WHERE

`WHERE` is evaluated before rows are grouped, so it sees one sale at a time and cannot know a
product's total. `WHERE SUM(...) > 100` is an error in most engines and quietly wrong in the rest;
`WHERE QuantitySold > 100` is a different question entirely (it asks for a *single* sale over 100,
which would drop Widget A and keep a product that sold 101 once and nothing else). The filter is on
an aggregate of the group, so it belongs in `HAVING`.

## Strictly greater

`> 100`, not `>= 100`. `edge/01` is three products selling exactly 99, exactly 100 and exactly 101
units — only the last one is reported, and a `>=` reports two.

## The join direction decides what happens to products that never sold

Starting from `Sales` and joining to `Products` means a product with no sales never enters the
result, which is what you want. If you start from `Products` and `LEFT JOIN Sales`, those products
survive the join with `NULL` quantities. They still get filtered out here, because `SUM` over no
rows is `NULL` and `NULL > 100` is `NULL` (not true) — but that is luck rather than intent, and a
`COALESCE(SUM(...), 0)` in the wrong place turns it into a row of zeros. `edge/03` and `edge/05`
(no sales at all) are there to catch that.

## Money

`Price` is `DECIMAL(10,2)`, and this judge runs SQLite, where that is a floating-point `REAL`. Two
consequences:

- **Round the output to two decimals.** `ROUND(x, 2)` is what makes the result a `DECIMAL(10,2)`
  rather than whatever a double happened to accumulate.
- `SUM(QuantitySold * Price)` and `SUM(QuantitySold) * Price` are both correct here, because `Price`
  is constant within a group. That is not generally true — if the price varied per sale, only the
  first form would be right.

The answer is compared numerically, so `2200`, `2200.0` and `2200.00` all match. What does not match
is a value rounded to the wrong number of places: `edge/07` has a total of `1.01`, which
`ROUND(x, 1)` turns into `1.0`.

## Ordering

`ORDER BY TotalSalesAmount DESC` — the alias is usable in `ORDER BY` because that clause is
evaluated after the select list. Since this problem's output is graded **as an ordered list**,
getting `ASC` or omitting the clause fails every test with more than one qualifying product.

The statement guarantees no two reported products share a total, which is what makes a single
ordering key sufficient. Without that guarantee the question would be under-specified and would need
a tie-break column — worth noticing, because real OA statements often forget to say it.

## Complexity

One pass over `Sales` with a hash or sort-based grouping: `O(S log S)` at worst, where `S` is the
number of sale rows. An index on `Sales(ProductID)` is what a real engine would use to avoid the
sort.
