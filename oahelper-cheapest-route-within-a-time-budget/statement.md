# Cheapest Route Within a Time Budget

A logistics company operates in a country with `n` cities numbered `0` through `n - 1`, connected by `m` two-way highways. Highway `i` joins cities `u_i` and `v_i` and takes `t_i` minutes to drive in either direction.

Every city charges an entry fee. Driving into city `c` costs `fee[c]` rupees, and the fee is charged **every single time** the truck enters that city — including the very first city, where the truck starts.

A truck must travel from city `src` to city `dest` and it must arrive within `maxTime` minutes (arriving at exactly `maxTime` minutes is allowed). Among all routes that respect the deadline, report the minimum total fee. The route does not have to be simple — the truck may drive through the same city more than once, paying its fee again each time.

If no route reaches `dest` within the deadline, report `-1`.

### Input Format

- The first line contains three integers `n`, `m` and `maxTime`.
- The second line contains `n` integers — `fee[0], fee[1], ..., fee[n-1]`.
- Each of the next `m` lines contains three integers `u`, `v` and `t`, describing a two-way highway between `u` and `v` that takes `t` minutes.
- The last line contains two integers `src` and `dest`.

### Output Format

Print a single integer — the minimum total fee, or `-1` if the deadline cannot be met.

### Constraints

- `2 <= n <= 1000`
- `0 <= m <= 1000`
- `1 <= maxTime <= 1000`
- `1 <= fee[i] <= 1000`
- `0 <= u, v < n` and `u != v`
- `1 <= t <= 1000`
- `0 <= src, dest < n`

There may be more than one highway between the same pair of cities. `src` and `dest` may be equal, in which case the truck pays only `fee[src]` and uses 0 minutes.

### Example 1
**Input:**
```
6 6 30
5 1 2 20 20 3
0 1 10
1 2 10
2 5 10
0 3 1
3 4 10
4 5 15
0 5
```
**Output:**
```
11
```
**Explanation:**
The route `0 -> 1 -> 2 -> 5` takes 30 minutes, exactly meeting the deadline, and costs 5 + 1 + 2 + 3 = 11.

### Example 2
**Input:**
```
6 6 29
5 1 2 20 20 3
0 1 10
1 2 10
2 5 10
0 3 1
3 4 10
4 5 15
0 5
```
**Output:**
```
48
```
**Explanation:**
With only 29 minutes the cheap 30-minute route is no longer legal. The fastest legal route is `0 -> 3 -> 4 -> 5`, which takes 26 minutes and costs 5 + 20 + 20 + 3 = 48.

### Example 3
**Input:**
```
6 6 25
5 1 2 20 20 3
0 1 10
1 2 10
2 5 10
0 3 1
3 4 10
4 5 15
0 5
```
**Output:**
```
-1
```
**Explanation:**
No route from city 0 to city 5 finishes within 25 minutes.
