# Flash Sale Revenue Maximization

Amazon is running a flash sale for a hot product supplied by several warehouses. Warehouse \(i\) starts with `supplierStock[i]` units on hand.

Pricing works as follows:

- You sell **one unit at a time**.
- When you sell a unit from a warehouse that currently has \(s\) units left, you earn **exactly \(s\)** in revenue, and that warehouse's stock becomes \(s - 1\).
- A warehouse with \(0\) stock cannot sell any more units.

You must fulfill exactly **orders** sales. Choose which warehouses to sell from (adaptively) to **maximize total revenue**.

It is guaranteed that `orders` never exceeds the total stock across all warehouses.

## Input

- The first line contains an integer **n** — the number of suppliers.
- Each of the next **n** lines contains one integer `supplierStock[i]`.
- The last line contains an integer **orders** — the number of units to sell.

## Output

Print a single integer — the maximum achievable revenue.

## Constraints

- \(1 \le n \le 10^5\)
- \(1 \le \text{supplierStock}[i] \le 10^5\)
- \(1 \le \text{orders} \le \sum \text{supplierStock}[i]\)
- The answer fits in a signed 64-bit integer

## Examples

### Example 1

**Input**
```
2
2
5
4
```

**Output**
```
14
```

**Explanation.** Optimal sales earn \(5 + 4 + 3 + 2 = 14\).

### Example 2

**Input**
```
5
2
8
4
10
6
20
```

**Output**
```
110
```

**Explanation.** Selling down toward a common floor of remaining stock yields revenue \(110\).
