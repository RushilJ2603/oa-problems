# Meeting Room Allocation

You run the booking desk at a busy conference center with **exactly R** meeting rooms. Today **N** teams have submitted booking requests. Each request is a triple *(start, end, priority)*: the meeting occupies a room on the half-open interval of times, and higher priority means a more important client.

A room frees up **exactly** at its current meeting's end time. That means a meeting that starts at time *t* may reuse a room whose previous meeting ended at *t*.

The desk processes requests in **increasing start time**. When two requests share the same start time, the one with **higher priority** is processed first (ties broken by original input order). For each request, the system:

1. Drops every active meeting whose end time is **≤** the new start time (those rooms are free).
2. If fewer than **R** meetings are still active, the new meeting is **accepted**.
3. Otherwise it may **replace** the active meeting with the smallest priority — but only when the new priority is **strictly larger**.

Whenever a meeting is accepted, its priority is added to a running total. When a replacement happens, the old priority is subtracted and the new one is added. Meetings that simply finish on time keep their contribution in the total.

Compute the final total priority after every request has been considered.

## Input Format

- Line 1: integer **N** — number of meeting requests.
- Line 2: integer **R** — number of rooms.
- Next **N** lines: three integers **start end priority** for each meeting.

## Output Format

Print a single integer — the final total priority of accepted meetings.

## Constraints

- \(1 \le N \le 10^5\)
- \(1 \le R \le N\)
- \(1 \le \text{start}, \text{end}, \text{priority} \le 10^9\)
- It is guaranteed that \(\text{start} < \text{end}\) for every meeting.

## Examples

### Example 1

**Input:**
```
3
1
1 5 10
2 6 20
6 10 30
```

**Output:**
```
50
```

With one room, `(1,5,10)` is accepted first. At time 2 the higher-priority `(2,6,20)` replaces it. At time 6 the room frees and `(6,10,30)` is accepted. Accepted priorities: 20 and 30 → **50**.

### Example 2

**Input:**
```
2
2
1 10 100
1 10 100
```

**Output:**
```
200
```

Two rooms are enough for both simultaneous meetings, so both priorities count: **200**.
