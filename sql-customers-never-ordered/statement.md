# Customers Who Never Ordered

Two tables:

**`customers`**

| Column | Type | Notes |
| --- | --- | --- |
| `id` | INTEGER | primary key |
| `name` | TEXT | never NULL; **names are not unique** |

**`orders`**

| Column | Type | Notes |
| --- | --- | --- |
| `id` | INTEGER | primary key |
| `customer_id` | INTEGER | **may be NULL** — an order that was never assigned to a customer. It may also hold an id that is not in `customers`. |

Report the `name` of every customer who has **never placed an order**.

## Output

One column: the customer's name. **One row per customer** — if two different customers share a name
and neither has ordered, that name appears twice.

Row order does not matter.

## Rules

- Only the query's **result set** is graded. Column names are ignored; column count is not.
- Your submission must be a **single read-only `SELECT`**.

## Example

**`customers`**

| id | name |
| --- | --- |
| 1 | Joe |
| 2 | Henry |
| 3 | Sam |
| 4 | Max |

**`orders`**

| id | customer_id |
| --- | --- |
| 1 | 3 |
| 2 | 1 |

**Output**

| name |
| --- |
| Henry |
| Max |

Joe (id 1) and Sam (id 3) both appear in `orders`, so only Henry and Max are reported.
