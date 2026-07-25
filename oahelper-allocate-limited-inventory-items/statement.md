# Allocate Limited Inventory Items

During a flash sale, shoppers submit requests for a scarce product. Each request is a 4-tuple

`[customerId, quantity, bidAmount, timestamp]`.

There are `totalInventory` identical items to hand out. Allocation follows these rules, in order:

1. Process bid amounts from **highest to lowest**.
2. Within the same bid amount, serve customers in **round-robin** ordered by **earliest timestamp** (break remaining ties by input order). Each round gives **exactly one** item to each still-hungry customer in that bid group, cycling until the group is fully satisfied or inventory runs out.
3. A customer who receives at least one item is considered fulfilled for the answer; customers who receive **zero** items are reported.

Return every customer ID that received no items, sorted in ascending order. If everyone got at least one item, print an empty line.

## Input Format

- Line 1: integer `n` — number of requests.
- Line 2: integer `4` — number of fields per request (always 4).
- Next `n` lines: `customerId quantity bidAmount timestamp`.
- Last line: integer `totalInventory`.

## Output Format

Space-separated customer IDs with zero items, sorted ascending. Print a blank line if the list is empty.

## Constraints

- `1 <= n < 10^4`
- `1 <= customerId, quantity, bidAmount, timestamp, totalInventory < 10^8`

## Examples

### Example 1

**Input**

```
3
4
1 2 5 0
2 1 4 2
3 5 4 6
3
```

**Output**

```
3
```

**Explanation**

Customer `1` (bid 5) takes 2 items; one remains. Customers `2` and `3` share bid 4; earlier timestamp `2` takes the last item. Customer `3` gets nothing.

### Example 2

**Input**

```
4
4
101 3 10 15
102 2 8 20
103 5 8 25
104 4 5 30
8
```

**Output**

```
104
```

**Explanation**

`101` takes 3. Remaining 5 items are round-robined between `102` and `103` (same bid 8): `102` gets 2, `103` gets 3. `104` gets nothing.

### Example 3

**Input**

```
4
4
1 5 5 0
2 7 8 1
3 7 5 1
4 10 3 3
18
```

**Output**

```
4
```

**Explanation**

The three higher bids request 19 items in total against 18 available, so the lowest bidder (`4`) receives nothing.
