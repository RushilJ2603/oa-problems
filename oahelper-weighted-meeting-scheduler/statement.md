# Weighted Meeting Scheduler

You are a freelance consultant with a packed calendar of potential client meetings. Each meeting has a start time, an end time, and a payment. You can attend only one meeting at a time — two meetings may both be taken only if they do not overlap. A meeting that ends at time `t` may be followed immediately by another that starts at time `t` (back-to-back is allowed).

Choose a subset of meetings that maximizes your total payment.

## Input Format

- The first line contains a single integer `N` — the number of meetings.
- Each of the next `N` lines contains three integers `S`, `E`, `P` — start time, end time, and payment of one meeting.

## Output Format

Print a single integer — the maximum total payment.

## Constraints

- \(1 \le N \le 10^5\)
- \(0 \le S[i] < E[i] \le 10^9\)
- \(1 \le P[i] \le 10^6\)

## Examples

### Example 1

**Input:**
```
4
1 3 50
2 5 60
4 6 70
6 8 80
```

**Output:**
```
200
```

**Explanation:** Take meetings `[1,3]` (50), `[4,6]` (70), and `[6,8]` (80). Total `200`. Back-to-back at time 6 is allowed.

### Example 2

**Input:**
```
3
1 4 100
2 3 50
3 5 60
```

**Output:**
```
110
```

**Explanation:** Take `[2,3]` and `[3,5]` for `110`, which beats taking `[1,4]` alone (`100`).

### Example 3

**Input:**
```
2
1 2 10
1 2 20
```

**Output:**
```
20
```

**Explanation:** Both meetings overlap completely; take the higher-paying one.
