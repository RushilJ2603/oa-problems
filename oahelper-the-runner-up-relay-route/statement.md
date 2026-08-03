# The Runner-Up Relay Route

Every spring, the trail-running guild of Fennwick charters a great relay between the clubhouse at station `1` and the summit lodge at station `n`. The `n` stations are joined by `m` two-way trails, trail `i` linking stations `u_i` and `v_i` with a running time of `w_i` seconds, and the trail map keeps every station reachable from every other.

A relay route starts at station `1`, ends at station `n`, and may pass through any stations and trails along the way — runners are even allowed to double back and reuse a trail or revisit a station if they wish. The total time of a route is the sum of the running times of every trail crossing made, counted once per crossing.

The guild's champion already holds the record for the fastest possible total time. To keep the rivalry alive, the vice-champion wants to chase a different mark: the smallest total time that is **strictly greater** than the fastest possible time.

Given the trail map, find that runner-up time — the **second-smallest distinct** total time over all possible relay routes from station `1` to station `n`.

## Input Format

- The first line contains a single integer `n`, the number of stations.
- The second line contains a single integer `m`, the number of trails.
- Each of the next `m` lines contains three integers `u_i`, `v_i` and `w_i` describing a trail.

## Output Format

Print a single integer — the second-smallest distinct total route time in seconds.

## Constraints

- \(3 \le n \le 100000\)
- \(n - 1 \le m \le 200000\)
- \(1 \le u_i, v_i \le n\), \(u_i \ne v_i\)
- \(2 \le w_i \le 1000000000\)
- The trail network is connected; multiple trails may join the same pair of stations.
- Routes may revisit stations and reuse trails; a runner-up time always exists.
- All values are integers.

## Examples

### Example 1

**Input**
```
4
4
1 2 3
2 4 4
1 3 2
3 4 6
```

**Output**
```
8
```

Routes from station 1 to station 4:

- `1 → 2 → 4`: \(3 + 4 = 7\)
- `1 → 3 → 4`: \(2 + 6 = 8\)
- Doubling-back routes cost 13 or more

The fastest time is 7; the runner-up is 8.

### Example 2

**Input**
```
3
2
1 2 2
2 3 2
```

**Output**
```
8
```

The only simple route costs 4. Going `1 → 2 → 1 → 2 → 3` costs 8, which is the runner-up.

### Example 3

**Input**
```
3
3
1 2 5
2 3 7
1 3 13
```

**Output**
```
13
```

### Example 4

**Input**
```
3
3
1 2 4
1 2 4
2 3 5
```

**Output**
```
17
```

### Example 5

**Input**
```
4
4
1 2 2
2 3 2
3 4 2
1 4 6
```

**Output**
```
10
```
