# Online Auction Sniper Detector

An online auction platform is hunting for "snipers" — users who dump many bids into a short burst near the end of a listing.

A window of length `W` seconds ending at a bid is **suspicious for a user** when that user placed at least `K` bids inside it (including the bid that closes the window).

Bids arrive in strictly increasing timestamp order. After every bid you must report:

1. Whether the current bid's own user is sniping in the window ending at this bid (`1` or `0`).
2. The smallest user id that is currently sniping in that same window, or `-1` if nobody qualifies.

## Input Format

```
N W K
t1 u1
t2 u2
...
tN uN
```

- `N` — number of bids
- `W` — window length in seconds
- `K` — sniping threshold
- each bid is a timestamp `t_i` and user id `u_i`
- timestamps are strictly increasing

## Output Format

Print `N` lines. Line `i` contains:

```
flag smallest_sniper
```

## Constraints

- `1 ≤ N ≤ 200000`
- `1 ≤ W ≤ 10^9`
- `2 ≤ K ≤ N`
- `0 ≤ t_i ≤ 10^9` (strictly increasing)
- `1 ≤ u_i ≤ 10^9`

## Examples

### Example 1

Input:
```
6 10 3
0 1
2 1
3 2
8 1
12 1
15 2
```

Output:
```
0 -1
0 -1
0 -1
1 1
1 1
0 -1
```

### Example 2

Input:
```
6 5 2
0 5
1 3
2 5
3 3
4 5
5 3
```

Output:
```
0 -1
0 -1
1 5
1 3
1 3
1 3
```
