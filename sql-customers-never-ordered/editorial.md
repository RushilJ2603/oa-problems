# Customers Who Never Ordered

## The obvious answer is a trap

Almost everyone writes this first:

```sql
SELECT name FROM customers
WHERE id NOT IN (SELECT customer_id FROM orders);   -- WRONG
```

It is correct right up until one order has a NULL `customer_id` — and then it returns **nothing at
all**, for every input, forever.

The reason is three-valued logic. `x NOT IN (a, b, NULL)` expands to
`x <> a AND x <> b AND x <> NULL`. That last term is never TRUE and never FALSE; it is **UNKNOWN**.
`TRUE AND UNKNOWN` is UNKNOWN, and `WHERE` keeps only rows that are TRUE. So the moment a single NULL
appears in the subquery, no row can ever qualify.

Note the asymmetry, because this is what makes the bug survive review: `IN` with a NULL still works
fine. Only the negated form collapses. `tests/edge/04.in` is the minimal case — two customers, one
real order, one unassigned order — and it takes the `NOT IN` version from "right" to "empty".

## Two answers that are actually correct

**LEFT JOIN + IS NULL** (the reference). Keep every customer, attach their orders, then keep the rows
where nothing attached:

```sql
SELECT c.name
FROM customers c
LEFT JOIN orders o ON o.customer_id = c.id
WHERE o.id IS NULL;
```

Test `o.id`, not `o.customer_id`. `orders.id` is the primary key and can never be NULL in a matched
row, so `o.id IS NULL` means precisely "no row matched". Testing `o.customer_id IS NULL` would also
be true for a matched row whose `customer_id` was NULL — except such a row can never match anyway, so
it happens to work here; relying on that is how the habit gets carried to a schema where it breaks.

**NOT EXISTS** — the one to say in an interview:

```sql
SELECT c.name
FROM customers c
WHERE NOT EXISTS (SELECT 1 FROM orders o WHERE o.customer_id = c.id);
```

`EXISTS` asks whether any row satisfies the correlated predicate. `o.customer_id = c.id` is UNKNOWN
for a NULL `customer_id`, which is not TRUE, so that row simply does not count as a match — exactly
the semantics wanted. `NOT EXISTS` is NULL-safe by construction, which is why it is the idiom to
default to for anti-joins.

## Watch the duplicate-row question

`LEFT JOIN` multiplies a customer by their number of orders. That is invisible here because every
multiplied row has a non-NULL `o.id` and gets filtered out, so a customer with 30 orders contributes
zero rows and a customer with none contributes exactly one (`tests/edge/08.in`). But if the task were
"customers who ordered", the same join would return that customer 30 times and you would need
`DISTINCT`. Knowing *why* it is not needed here is the point.

## The traps, and the tests that catch them

| Trap | Test |
| --- | --- |
| `NOT IN` with a NULL in the subquery | `edge/04`, `edge/05` |
| Assuming every `customer_id` exists in `customers` | `edge/06` (orphan order) |
| Collapsing duplicate names with `DISTINCT` | `edge/07` (two customers named Ann) |
| Emitting a customer once per order | `edge/08` |
| Breaking on `'` inside a TEXT value | `edge/10` (`O'Brien`) |
