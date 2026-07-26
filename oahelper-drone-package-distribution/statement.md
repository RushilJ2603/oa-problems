# Drone Package Distribution

A warehouse dispatches packages by drone. Packages sit in a fixed priority queue and **must** be delivered in that order — you may only choose how to split the queue into consecutive loads.

Each load leaves the warehouse, visits the delivery zones of its packages **in order**, then returns to the warehouse. Moving between two different consecutive zones inside one load costs one trip; leaving the warehouse and returning each cost one trip. So a load of packages with `z` zone-changes among consecutive packages costs `z + 2` trips.

A load may contain at most `maxPackages` packages and total weight at most `maxWeight`. Every package weight is at most `maxWeight`, so a singleton load is always valid.

Compute the **minimum** total number of trips needed to deliver every package.

## Input

- Line 1: integer `N` — number of packages
- Next `N` lines: `zone_i weight_i` for package `i` in queue order
- Next line: `totalZones`
- Next line: `maxPackages`
- Next line: `maxWeight`

## Output

A single integer — the minimum number of trips.

## Constraints

- \(1 \le N \le 10^5\)
- \(1 \le\) `totalZones`, `maxPackages`, `maxWeight` \(\le 10^5\)
- \(1 \le\) `zone_i` \(\le\) `totalZones`
- \(1 \le\) `weight_i` \(\le\) `maxWeight`

## Examples

### Example 1

```
3
1 1
2 1
1 1
2
3
3
```

```
4
```

All three packages fit in one load. Zones go `1 → 2 → 1` (two changes), plus leave and return: \(2 + 2 = 4\).

### Example 2

```
1
1 1
1
1
1
```

```
2
```

One package: leave, deliver, return.
