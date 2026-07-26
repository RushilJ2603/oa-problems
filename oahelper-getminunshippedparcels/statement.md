# Minimum Unshipped Parcels

An Amazon fulfilment centre has **n** parcels queued for dispatch. The **i**-th parcel weighs **weights[i]**. On any single trip the truck may carry exactly one parcel, and only if that parcel's weight is **strictly less than** the truck's present capacity **max_wt**. Wear and tear means the capacity **max_wt** falls by **1** immediately after every completed trip.

You may choose the order in which parcels are dispatched. Find the **minimum** number of parcels that can never be shipped, no matter how you order the trips.

Shipping stops once every remaining parcel weighs at least the current capacity (future capacities only get smaller).

## Input Format

- The first line contains an integer **n** — the number of parcels.
- The next **n** lines each contain one integer **weights[i]**.
- The last line contains an integer **max_wt** — the truck's initial capacity.

## Output Format

Print a single integer — the minimum number of parcels that cannot be shipped.

## Constraints

- \(1 \le n \le 10^5\)
- \(1 \le weights[i] \le 10^9\)
- \(1 \le max\_wt \le 10^9\)

## Examples

### Example 1

**Input**
```
5
5
3
1
9
7
4
```

**Output**
```
3
```

**Explanation**

Capacity starts at 4 and drops by 1 after each trip. Ship weight 3 first (capacity becomes 3), then weight 1 (capacity becomes 2). Nothing remaining is strictly lighter than 2, so 3 parcels stay behind.

### Example 2

**Input**
```
3
1
6
8
1
```

**Output**
```
3
```

**Explanation**

No parcel weighs strictly less than `max_wt = 1`, so none can be shipped.

### Example 3

**Input**
```
5
7
1
7
4
4
6
```

**Output**
```
2
```

**Explanation**

An optimal order ships three parcels before capacity becomes too small; 2 parcels remain unshipped.
