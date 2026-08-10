# Top Selling Products

You have been assigned to evaluate a company's sales performance. The company has two tables,
`Sales` and `Products`.

`Sales` records individual transactions:

| Column | Type |
|---|---|
| `SaleID` | INTEGER |
| `ProductID` | INTEGER |
| `QuantitySold` | INTEGER |
| `SaleDate` | DATE |

`Products` holds the details of each product:

| Column | Type |
|---|---|
| `ProductID` | INTEGER |
| `ProductName` | VARCHAR(50) |
| `Price` | DECIMAL(10,2) |

Write an SQL query that reports, for each product **sold more than 100 times**, its name and its
total sales amount.

- A product is *sold more than 100 times* when the **total quantity** across all of its sales — the
  sum of `QuantitySold` — is strictly greater than `100`. It is the quantity that counts, not the
  number of transactions.
- The **total sales amount** is the quantity sold multiplied by the product's price, added up over
  all of that product's sales.

## Output format

Two columns, in this order:

| Column | Type |
|---|---|
| `ProductName` | VARCHAR(50) |
| `TotalSalesAmount` | DECIMAL(10,2) |

Rows are ordered by `TotalSalesAmount` **descending**. `TotalSalesAmount` is a `DECIMAL(10,2)`, so
round it to **2 decimal places**.

## Constraints

- `1 <=` number of rows in `Products` `<= 200`; `ProductID` and `ProductName` are unique.
- `0 <=` number of rows in `Sales` `<= 1000`.
- `0 <= QuantitySold <= 1000`.
- `0.01 <= Price <= 999.99`, always with exactly two decimal places.
- Every `Sales.ProductID` exists in `Products`. A product may have no sales at all.
- Every `TotalSalesAmount` fits in `DECIMAL(10,2)`, and no two reported products have the same
  `TotalSalesAmount` — so the descending order is unambiguous.

## Example 1

**Input**

`Sales`

| SaleID | ProductID | QuantitySold | SaleDate |
|---|---|---|---|
| 1 | 1 | 50 | 2024-01-01 |
| 2 | 1 | 60 | 2024-01-02 |
| 3 | 2 | 40 | 2024-01-03 |

`Products`

| ProductID | ProductName | Price |
|---|---|---|
| 1 | Widget A | 20.00 |
| 2 | Widget B | 15.10 |

**Output**

| ProductName | TotalSalesAmount |
|---|---|
| Widget A | 2200.00 |

**Explanation:** Widget A sold `50 + 60 = 110` units, which is more than `100`, for a total of
`110 × 20.00 = 2200.00`. Widget B sold only `40` units in a single transaction and is left out —
note that Widget A qualifies on **two** transactions, so the test is on the summed quantity and not
on the transaction count.

## Example 2

**Input**

`Sales`

| SaleID | ProductID | QuantitySold | SaleDate |
|---|---|---|---|
| 4 | 3 | 20 | 2024-02-01 |
| 5 | 4 | 10 | 2024-02-02 |
| 6 | 4 | 100 | 2024-02-03 |

`Products`

| ProductID | ProductName | Price |
|---|---|---|
| 3 | Widget C | 30.50 |
| 4 | Widget D | 25.25 |

**Output**

| ProductName | TotalSalesAmount |
|---|---|
| Widget D | 2777.50 |

**Explanation:** Widget D sold `10 + 100 = 110` units, for `110 × 25.25 = 2777.50`. Widget C sold
`20` and is left out.
